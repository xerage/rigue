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

#define HANDLE(X) case X: X##Handler(); break

void EventHandler()
{
    switch (event.type) {
        HANDLE(KeyPress);
        HANDLE(ButtonPress);
        HANDLE(ButtonRelease);
        HANDLE(MotionNotify);
        HANDLE(MapRequest);
        HANDLE(UnmapNotify);
        HANDLE(ConfigureRequest);
        HANDLE(ClientMessage);
    }
}

/* Handler functions */
void KeyPressHandler()
{
    int i;
    KeySym keysym;

    keysym = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);

    for (i = 0; i < (sizeof(keys) / sizeof(*keys)); ++i)
    {
        if (keysym == keys[i].keysym && keys[i].mod == event.xkey.state)
            if (keys[i].function)
                keys[i].function();
    }
}

void ButtonPressHandler()
{
    if (event.xbutton.subwindow == None)
        return;

    XSetInputFocus(display, event.xbutton.subwindow, RevertToParent, CurrentTime);
    current = client_find(event.xbutton.subwindow);
    client_update_current(current);

    XGrabPointer(display, event.xbutton.subwindow, True, PointerMotionMask|ButtonReleaseMask,
            GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    XGetWindowAttributes(display, event.xbutton.subwindow, &attr);
    move_start = event.xbutton;
}

void ButtonReleaseHandler()
{
    XUngrabPointer(display, CurrentTime);

    if (event.xbutton.window == current->win)
    {
        XGetWindowAttributes(display, current->win, &attr);
        current->geom.x = attr.x; current->geom.y = attr.y;
        current->geom.w = attr.width; current->geom.h = attr.height;
    }
}

void MotionNotifyHandler()
{
    int xdiff, ydiff;
    Client* c;

    if ((c = client_find(event.xmotion.window)))
        current = c;

    while (XCheckTypedEvent(display, MotionNotify, &event));

    xdiff = event.xmotion.x_root - move_start.x_root;
    ydiff = event.xmotion.y_root - move_start.y_root;

    XMoveResizeWindow(display, event.xmotion.window,
            attr.x + (move_start.button == 1 ? xdiff : 0),
            attr.y + (move_start.button == 1 ? ydiff : 0),
            MAX(1, attr.width + (move_start.button == 3 ? xdiff : 0)),
            MAX(1, attr.height + (move_start.button == 3 ? ydiff : 0)));
}

void MapRequestHandler()
{
    Client* c;

    c = client_new(event.xmaprequest.window);
    client_map(c);
    ewmh_set_client_list();
}

void UnmapNotifyHandler()
{
    Client* c;

    wm_debug("Unmap event occured.");

    if ((c = client_find(event.xunmap.window)))
    {
        client_remove(c);
    }
    ewmh_set_client_list();
}

void DestroyNotifyHandler()
{
    Client* c;

    wm_debug("Destroy event occured.");

    if ((c = client_find(event.xdestroywindow.window)))
        client_remove(c);
}

void ConfigureRequestHandler()
{
    XWindowChanges wc;

    wc.x = event.xconfigurerequest.x;
    wc.y = event.xconfigurerequest.y;
    wc.width = event.xconfigurerequest.width;
    wc.height = event.xconfigurerequest.height;
    wc.border_width = 0;
    wc.sibling = event.xconfigurerequest.above;
    wc.stack_mode = event.xconfigurerequest.detail;
    XConfigureWindow(display, event.xconfigurerequest.window, event.xconfigurerequest.value_mask, &wc);
    XSync(display, False);
}

void ClientMessageHandler()
{
    Client* c;

    printf("atom: %x\n", event.xclient.message_type);

    c = client_find(event.xclient.window);

    if (event.xclient.message_type == atom[NET_ACTIVE_WINDOW])
        client_update_current(c);
    if (event.xclient.message_type == atom[NET_CLOSE_WINDOW])
        kill_client(c);
}
