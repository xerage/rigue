/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Gergely Szarka, 2014
 */
#include "rigue.h"

Atom ewmh_make_atom(const char *a) {
	return XInternAtom(display, a, False);
}

int ewmh_init() {
	atom[WM_NAME] = XA_WM_NAME;
	atom[WM_PROTOCOLS] = ewmh_make_atom("WM_PROTOCOLS");
	atom[WM_DELETE_WINDOW] = ewmh_make_atom("WM_DELETE_WINDOW");
	atom[WM_STATE] = ewmh_make_atom("WM_STATE");
	atom[WM_TAKE_FOCUS] = ewmh_make_atom("WM_TAKE_FOCUS");
    atom[NET_SUPPORTED] = ewmh_make_atom("_NET_SUPPORTED");
    atom[NET_SUPPORTING_WM_CHECK] = ewmh_make_atom("_NET_SUPPORTING_WM_CHECK");
    atom[NET_WM_PID] = ewmh_make_atom("_NET_WM_PID");
	atom[NET_WM_NAME] = ewmh_make_atom("_NET_WM_NAME");
	return 0;
}

Atom ewmh_get_atom(Client* c, int type) {
	int i;
	unsigned long ul;
	unsigned char *uc = NULL;
	Atom aa, at = None;
	if (!XGetWindowProperty(display, c->win, atom[type], 0L, sizeof(at),
			False, XA_ATOM, &aa, &i, &ul, &ul, &uc) == Success && uc)
		return at;
	at = *(Atom *)uc;
	XFree(uc);
	return at;
}

char* ewmh_get_text(Client* c, int type) {
	char **strs = NULL, *ret = NULL;
	int n;
	XTextProperty text;
	XGetTextProperty(display, c->win, &text, atom[type]);
	if (!text.nitems) return NULL;
	if (text.encoding == XA_STRING) ret = strdup(text.value);
	else if (XmbTextPropertyToTextList(display, &text, &strs, &n)>=Success) {
		ret = strdup(*strs);
		XFreeStringList(strs);
	}
	XFree(text.value);
	return ret;
}


int ewmh_send_message(Client* c, int type, int msg) {
	XEvent ev;
	ev.type = ClientMessage;
	ev.xclient.window = c->win;
	ev.xclient.message_type = atom[type];
	/*ev.xclient.message_type = XInternAtom(dpy, "WM_PROTOCOLS", True);*/
	ev.xclient.format = 32;
	ev.xclient.data.l[0] = atom[msg];
	/*ev.xclient.data.l[0] = XInternAtom(dpy, "WM_DELETE_WINDOW", True);*/
	ev.xclient.data.l[1] = CurrentTime;
	XSendEvent(display, c->win, False, NoEventMask, &ev);
	return 0;
}
