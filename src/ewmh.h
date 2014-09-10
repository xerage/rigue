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
#ifndef EWMH_H

#define EWMH_H

Atom ewmh_get_atom(Client*, int);
char* ewmh_get_text(Client*, int);
int ewmh_init();
int ewmh_send_message(Client*, int, int);
Atom ewmh_make_atom(const char*);

#endif /* end of include guard: EWMH_H */
