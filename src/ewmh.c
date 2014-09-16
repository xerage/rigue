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
    XSetWindowAttributes sattr;
    unsigned int ndesk;
    unsigned int curdesk;
    unsigned int geometry[2];
    unsigned int viewport[2];
    unsigned int workarea[4];
    unsigned int active;

    /* Intern atoms */
	atom[WM_NAME] = XA_WM_NAME;
	atom[WM_PROTOCOLS] = ewmh_make_atom("WM_PROTOCOLS");
	atom[WM_DELETE_WINDOW] = ewmh_make_atom("WM_DELETE_WINDOW");
	atom[WM_STATE] = ewmh_make_atom("WM_STATE");
	atom[WM_TAKE_FOCUS] = ewmh_make_atom("WM_TAKE_FOCUS");
    atom[NET_SUPPORTED] = ewmh_make_atom("_NET_SUPPORTED");
    atom[NET_CLIENT_LIST] = ewmh_make_atom("_NET_CLIENT_LIST");
    atom[NET_CLIENT_LIST_STACKING] = ewmh_make_atom("_NET_CLIENT_LIST_STACKING");
    atom[NET_ACTIVE_WINDOW] = ewmh_make_atom("_NET_ACTIVE_WINDOW");
	atom[NET_WM_NAME] = ewmh_make_atom("_NET_WM_NAME");
    atom[NET_SUPPORTING_WM_CHECK] = ewmh_make_atom("_NET_SUPPORTING_WM_CHECK");
    atom[NET_WM_WINDOW_TYPE] = ewmh_make_atom("_NET_WM_WINDOW_TYPE");
    atom[NET_WM_STATE] = ewmh_make_atom("_NET_WM_STATE");
    atom[NET_MOVERESIZE_WINDOW] = ewmh_make_atom("_NET_MOVERESIZE_WINDOW");
    atom[NET_WM_MOVERESIZE] = ewmh_make_atom("_NET_WM_MOVERESIZE");
    atom[NET_CLOSE_WINDOW] = ewmh_make_atom("_NET_CLOSE_WINDOW");
    atom[NET_WM_PID] = ewmh_make_atom("_NET_WM_PID");
    atom[NET_WORKAREA] = ewmh_make_atom("_NET_WORKAREA");
    /* Desktop */
    atom[NET_NUMBER_OF_DESKTOPS] = ewmh_make_atom("_NET_NUMBER_OF_DESKTOPS");
    atom[NET_DESKTOP_GEOMETRY] = ewmh_make_atom("_NET_DESKTOP_GEOMETRY");
    atom[NET_CURRENT_DESKTOP] = ewmh_make_atom("_NET_CURRENT_DESKTOP");
    atom[NET_DESKTOP_VIEWPORT] = ewmh_make_atom("_NET_DESKTOP_VIEWPORT");

    /* Tell which atoms are supported*/
    XChangeProperty(display, root, atom[NET_SUPPORTED], XA_ATOM, 32, PropModeReplace, (unsigned char*)atom, ATOM_LAST);

    /* The supporting wm check */
    sattr.override_redirect = True;
    supportwin = XCreateWindow(display, root, 0, 0, 1, 1, 0,
            CopyFromParent, InputOnly, CopyFromParent, CWOverrideRedirect,
            &sattr);

    XChangeProperty(display, root, atom[NET_SUPPORTING_WM_CHECK], XA_WINDOW, 32, PropModeReplace, (unsigned char*)&supportwin, 1);
    XChangeProperty(display, supportwin, atom[NET_SUPPORTING_WM_CHECK], XA_WINDOW, 32, PropModeReplace, (unsigned char*)&supportwin, 1);

    /* Init atoms that shouldn't change */
    ndesk = 1;
    curdesk = 0;
    geometry[0] = display_w; geometry[1] = display_h;
    viewport[0] = 0; viewport[1] = 0;
    active = None;
    workarea[0] = 0; workarea[1] = 0;
    workarea[2] = display_w; workarea[3] = display_h;

    XChangeProperty(display, root, atom[NET_NUMBER_OF_DESKTOPS], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&ndesk, 1);
    XChangeProperty(display, root, atom[NET_DESKTOP_GEOMETRY], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&geometry, 2);
    XChangeProperty(display, root, atom[NET_DESKTOP_VIEWPORT], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&viewport, 2);
    XChangeProperty(display, root, atom[NET_CURRENT_DESKTOP], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&curdesk, 1);
    XChangeProperty(display, root, atom[NET_WORKAREA], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&workarea, 4);
    XChangeProperty(display, root, atom[NET_WM_NAME], XA_STRING,
            32, PropModeReplace, (unsigned char*)"rigue", 6);
    /*XChangeProperty(display, root, atom[NET_WM_PID], XA_CARDINAL,
            32, PropModeReplace, (unsigned char*)&pid, 1);*/

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
	ev.xclient.format = 32;
	ev.xclient.data.l[0] = atom[msg];
	ev.xclient.data.l[1] = CurrentTime;
	XSendEvent(display, c->win, False, NoEventMask, &ev);
	return 0;
}

void ewmh_set_client_list()
{
    unsigned int n_clients;
    Window* client_list;
    Window* stacked_client_list;
    Client* c;

    n_clients = 0;
    client_list = NULL;
    stacked_client_list = NULL;


    for (c = head; c; c = c->next)
        n_clients++;

    if (n_clients > 0)
    {
        unsigned int i;
        Window w1, w2;
        Window* wins;
        unsigned int win, n_wins;

        client_list = malloc(sizeof(Window) * n_clients);
        stacked_client_list = malloc(sizeof(Window) * n_clients);

        i = n_clients - 1;
        for (c = head; c; c = c->next)
        {
            client_list[i] = c->win;
            i--;
            if (i < 0) break;
        }

        i = 0;
        XQueryTree(display, root, &w1, &w2, &wins, &n_wins);
        for (win = 0; win < n_wins; win++)
        {
            c = client_find(wins[win]);
            if (!c) continue;
            stacked_client_list[i] = c->win;
            i++;
            if (i >= n_clients) break;
        }
        if (n_wins > 0) XFree(wins);
    }

    XChangeProperty(display, root, atom[NET_CLIENT_LIST], XA_WINDOW, 32,
            PropModeReplace, (unsigned char*)client_list, n_clients);
    XChangeProperty(display, root, atom[NET_CLIENT_LIST_STACKING], XA_WINDOW, 32,
            PropModeReplace, (unsigned char*)stacked_client_list, n_clients);

    if (n_clients > 0)
    {
        free(client_list);
        free(stacked_client_list);
    }
}
