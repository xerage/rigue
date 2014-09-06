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

void keys_init()
{
    int i;
    KeyCode code;

    XUngrabKey(display, AnyKey, AnyModifier, root);

    for (i = 0; i < (sizeof(keys) / sizeof(*keys)); ++i)
    {
        code = XKeysymToKeycode(display, keys[i].keysym);
        XGrabKey(display, code, keys[i].mod, root, True, GrabModeAsync, GrabModeAsync);
    }

    for (i = 0; i < 4; i += 2)
    {
        XGrabButton(display, i, _ALT, root, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None);
    }
}
