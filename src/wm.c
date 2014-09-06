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

void wm_debug(const char * msg)
{
    fprintf(stdout, "\033[0;34m*** rigue : %s \033[0;m\n", msg);
}

void wm_panic(const char * err)
{
    fprintf(stderr, "\033[0;31m*** rigue : error: %s \033[0;m\n", err);
    exit(1);
}

unsigned long wm_get_color(const char * color)
{
    XColor c;
    Colormap map = DefaultColormap(display, screen);

    if (!XAllocNamedColor(display, map, color, &c, &c))
        wm_panic("Error parsing color.");

    return c.pixel;
}

void wm_init()
{
    char * loc;

    screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    XSelectInput(display, root, SubstructureRedirectMask|PointerMotionMask);

    loc = setlocale(LC_ALL, "");
    if (!loc || !strcmp(loc, "C") || !strcmp(loc, "POSIX") || !XSupportsLocale())
        wm_debug("Locale failed");

    /* Load colors */
    color_focus = wm_get_color(FOCUS);
    color_unfocus = wm_get_color(UNFOCUS);

    keys_init();

    wm_running = 1;
    wm_debug("Rigue started");
}

void wm_quit()
{
    XClearWindow(display, root);
    XUngrabKey(display, AnyKey, AnyModifier, root);
    XSync(display, False);
    XSetInputFocus(display, root, RevertToPointerRoot, CurrentTime);
    wm_running = 0;
    wm_debug("Exiting rigue! Bye!");
}
