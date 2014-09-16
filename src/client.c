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
    long supplied;
    Atom win_type;

    XGetWindowAttributes(display, win, &attr);

    if (attr.override_redirect) return NULL;
    if (c = client_find(win)) return NULL;

    c = malloc(sizeof *c);
    c->next = head;
    head = c;

    c->win = win;

    c->name = ewmh_get_text(c, WM_NAME);
    c->geom.x = attr.x;
    c->geom.y = 16;
    c->geom.w = attr.width;
    c->geom.h = attr.height;

    XGetWMNormalHints(display, c->win, &c->size, &supplied);
    XGetTransientForHint(display, c->win, &c->trans);

    return c;
}

void client_remove(Client* c)
{
    Client* tmp;

    XGrabServer(display);

    if (head == c)
        head = c->next;
    else
        for (tmp = head; tmp && tmp->next; tmp = tmp->next)
            if (tmp->next == c)
                tmp->next = c->next;

    client_update_current(client_next(c));
    free(c);

    XUngrabServer(display);
}

void client_decorate(Client* c)
{
    XSetWindowBorderWidth(display, c->win, BORDER_WIDTH);
    if (c->focus)
        XSetWindowBorder(display, c->win, color_focus);
    else
        XSetWindowBorder(display, c->win, color_unfocus);
}

void client_map(Client *c)
{
    XGetWindowAttributes(display, c->win, &attr);

    if (attr.override_redirect) return;

    client_update_current(c);
    XMapWindow(display, c->win);
}

void client_update_current(Client* c)
{
    Client* tmp;

    if ((head == NULL) || (c == NULL)) return;

    current = c;

    for (tmp = head; tmp; tmp = tmp->next)
    {
        if (tmp == current)
        {
            tmp->focus = True;
            ewmh_send_message(tmp, WM_PROTOCOLS, WM_TAKE_FOCUS);
            ewmh_send_message(tmp, WM_PROTOCOLS, NET_ACTIVE_WINDOW);
            XChangeProperty(display, root, atom[NET_ACTIVE_WINDOW], XA_WINDOW, 32, PropModeReplace, (unsigned char*)&tmp->win, 1);
            XRaiseWindow(display, tmp->win);
        }
        else
            tmp->focus = False;
        client_decorate(tmp);
    }
}

Client* client_next(Client* c)
{
    if (!(c->next))
        return head;
    else
        return c->next;
}

Client* client_find(Window win)
{
    Client *c;
    for (c = head; c; c = c->next)
        if (c->win == win)
            return c;

    return NULL;
}

void client_print()
{
    Client* c;

    if (head == NULL)
    {
        wm_debug("No head");
        return;
    }

    printf("--- Clientlist ---\n");
    for (c = head; c; c = c->next)
    {
        if (c == current)
            printf("*");
        if (c->focus)
            printf("!");
        printf("Managed window %s [%d] @ %d:%d\n", c->name, c->win, c->geom.x, c->geom.y);
    }
    printf("------------------\n");
}
