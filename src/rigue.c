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

int main(int argc, const char *argv[])
{
    /* Open connection to the X server*/
    if (!(display = XOpenDisplay(NULL)))
        exit(1);

    /* Set up base info */
    screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    /* Registering for events */

    /* Main loop
     * TODO: change wired 1 to a bool running variable or something like that */
    while (1)
    {
        XNextEvent(display, &event);
    }

    return 0;
}
