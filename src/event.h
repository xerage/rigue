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
#ifndef EVENT_H

#define EVENT_H

void EventHandler();

void KeyPressHandler();
void ButtonPressHandler();
void ButtonReleaseHandler();
void ClientMessageHandler();
void ConfigureRequestHandler();
void MotionNotifyHandler();
void MapRequestHandler();
void UnmapNotifyHandler();

#endif /* end of include guard: EVENT_H */
