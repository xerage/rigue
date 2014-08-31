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
#ifndef RIGUE_H

#define RIGUE_H

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

enum { UP, RIGHT, DOWN, LEFT };

typedef struct Geom Geom;
struct Geom {
    int x, y, w, h;
};

typedef struct Client Client;
struct Client {
    Window win;
    Geom geom;
    Client * next;
};

Display * display;
Window root;
int screen;

XEvent event;
XButtonEvent move_start;

XWindowAttributes attr;

#endif /* end of include guard: RIGUE_H */
