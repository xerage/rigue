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

/* Macros */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Standard libs */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

/* X11 libs */
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/Xlocale.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

/* Configs */
#include "config.h"

/* Enums */
enum { UP, RIGHT, DOWN, LEFT };

enum {WM_NAME, WM_PROTOCOLS, WM_DELETE_WINDOW, WM_STATE, WM_TAKE_FOCUS,
        NET_WM_NAME, NET_SUPPORTED, NET_SUPPORTING_WM_CHECK, NET_WM_PID, ATOM_LAST};

/* Typedefs */
typedef struct Key Key;
struct Key{
    unsigned int mod;
    KeySym keysym;
    void (*function)();
};

typedef struct Geom Geom;
struct Geom {
    int x, y, w, h;
};

typedef struct Client Client;
struct Client {
    Window win;
    Geom geom, save;
    char* name;
    Bool focus;
    Client * next;
};

typedef struct Desktop Desktop;
struct Desktop {
    int w, h;
};

/* Rigue libs */
#include "ewmh.h"
#include "action.h"
#include "client.h"
#include "event.h"
#include "wm.h"
#include "keys.h"

/* Variables */
Display * display;
Window root;
int screen;
XEvent event;
XButtonEvent move_start;
XWindowAttributes attr;

Atom atom[ATOM_LAST];

unsigned int color_focus, color_unfocus;
unsigned int display_w, display_h;

Client *head, *current;

extern Key keys[];

int wm_running;

#endif /* end of include guard: RIGUE_H */
