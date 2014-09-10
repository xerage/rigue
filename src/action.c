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

void kill_client()
{
    wm_debug("Killing client");
    if ((head == NULL) || (current == NULL) || (current->win == root)) return;
    /*XUnmapWindow(display, current->win);
    XKillClient(display, current->win);*/
    ewmh_send_message(current, WM_PROTOCOLS, WM_DELETE_WINDOW);
    client_remove(current);
}

void move_client(Client* c, int x, int y)
{
    c->geom.x = x;
    c->geom.y = y;
    XMoveWindow(display, c->win, x, y);
}

Bool client_under()
{
    Client* c;

    for (c = head; c; c = c->next)
    {
        if (c != current)
        {
            if (current->geom.y - 1 > (c->geom.y + c->geom.h))
                return True;
            else
                return False;
        }
    }
    return False;
}

/* Move window in direction*/
void snap_up()
{
    while (client_under())
        current->geom.y--;

    move_client(current, current->geom.x, current->geom.y);
}

void snap_right()
{
    move_client(current, display_w - current->geom.w, current->geom.y);
}

void snap_down()
{
    move_client(current, current->geom.x, display_h - current->geom.h);
}

void snap_left()
{
    move_client(current, 0, current->geom.y);
}

/* Grow window in direction */
void grow_up()
{
    wm_debug("Growing up.");
}

void grow_right()
{
    wm_debug("Growing right.");
}

void grow_down()
{
    wm_debug("Growing down.");
}

void grow_left()
{
    wm_debug("Growing left.");
}

/* Maximize / Fullscreen */
void toggle_maximize()
{
    wm_debug("Maximize");
}

void toggle_fullscreen()
{
    wm_debug("Fullscreen");
}
