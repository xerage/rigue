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

/* WM controll */
void restart_wm();
void exit_wm();
void recompile_wm();

/* Window management */
void close();
void iconify();
void next_window();
void toggle_always_on_top();
void toggle_always_on_bottom();

/* Desktop management */
void next_desktop();
void toggle_show_desktop();

/* Maximize / Fullscreen */
void toggle_maximize_full();
void toggle_maximize_horizontally();
void toggle_maximize_vertically();
void toggle_fullscreen();

/* Change focus */
void directional_focus_up();
void directional_focus_right();
void directional_focus_down();
void directional_focus_left();

/* Move clients */
void move_to_edge_up();
void move_to_edge_right();
void move_to_edge_down();
void move_to_edge_left();

/* Grow clients */
void grow_to_edge_up();
void grow_to_edge_right();
void grow_to_edge_down();
void grow_to_edge_left();

#endif /* end of include guard: ACTION_H */
