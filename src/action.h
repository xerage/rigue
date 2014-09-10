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
#ifndef ACTION_H

#define ACTION_H

/* Control WM */
void kill_client();

/* Maximize / Fullscreen */
void toggle_maximize();
void toggle_fullscreen();

/* Move clients */
void snap_up();
void snap_right();
void snap_down();
void snap_left();

/* Grow clients */
void grow_up();
void grow_right();
void grow_down();
void grow_left();

#endif /* end of include guard: ACTION_H */
