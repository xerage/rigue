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
#ifndef KEYS_H

#define KEYS_H

#define _ALT        Mod1Mask
#define _CTRL       ControlMask
#define _SHIFT      ShiftMask
#define _SUPER      Mod4Mask

static Key keys[] = {
    {_CTRL|_ALT, XK_Delete, wm_quit},
    {_CTRL|_ALT, XK_Return, wm_restart},
    {_SUPER, XK_c, kill_client},
    {_SUPER, XK_m, toggle_maximize},
    {_SUPER, XK_f, toggle_fullscreen},
    {_SUPER, XK_p, client_print},
    {_SUPER|_SHIFT, XK_Up, snap_up},
    {_SUPER|_SHIFT, XK_Right, snap_right},
    {_SUPER|_SHIFT, XK_Down, snap_down},
    {_SUPER|_SHIFT, XK_Left, snap_left},
    {_SUPER|_CTRL, XK_Up, grow_up},
    {_SUPER|_CTRL, XK_Right, grow_right},
    {_SUPER|_CTRL, XK_Down, grow_down},
    {_SUPER|_CTRL, XK_Left, grow_left}
};

void keys_init();

#endif /* end of include guard: KEYS_H */
