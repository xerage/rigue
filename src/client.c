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

Client * client_new(Window win)
{
    Client *c;

    c = malloc(sizeof *c);
    c->next = head;
    head = c;

    c->win = win;

    XGetWindowAttributes(display, c->win, &attr);
    c->geom.x = attr.x;
    c->geom.y = attr.y;
    c->geom.w = attr.width;
    c->geom.h = attr.height;

    return c;
}

void client_remove(Client* c)
{
    Client* tmp;

    XGrabServer(display);
    XUngrabButton(display, AnyButton, AnyModifier, c->win);
    XUnmapWindow(display, c->win);

    if (head == c)
        head = c->next;
    else
        for (tmp = head; tmp && tmp->next; tmp = tmp->next)
            if (tmp->next == c)
                tmp->next = c->next;
    free(c);

    XUngrabServer(display);
}

void client_decorate(Client* c)
{
    XSetWindowBorderWidth(display, c->win, BORDER_WIDTH);
    XSetWindowBorder(display, c->win, color_focus);
}

void client_map(Client *c)
{
    XGetWindowAttributes(display, c->win, &attr);

    if (attr.override_redirect) return;

    client_decorate(c);
    XMapWindow(display, c->win);
}

Client* client_find(Window win)
{
    Client *c;
    for (c = head; c; c = c->next)
        if (c->win == win)
            return c;

    wm_debug("Client found");
    return NULL;
}
