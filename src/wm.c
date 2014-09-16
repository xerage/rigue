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

void wm_signal_handler(int signal)
{
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
    Window dw1, dw2;
    Window* wins;
    int i, nwins;
    unsigned long pid;

    pid = getpid();

    /* Set globals */
    screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    display_w = DisplayWidth(display, screen);
    display_h = DisplayHeight(display, screen);

    XDefineCursor(display, root, XCreateFontCursor(display, 68));

    XSelectInput(display, root, SubstructureRedirectMask|SubstructureNotifyMask|PointerMotionMask);

    loc = setlocale(LC_ALL, "");
    if (!loc || !strcmp(loc, "C") || !strcmp(loc, "POSIX") || !XSupportsLocale())
        wm_debug("Locale failed");

    /* Load colors */
    color_focus = wm_get_color(FOCUS);
    color_unfocus = wm_get_color(UNFOCUS);

    keys_init();

    /* EWMH */
    ewmh_init();
    XChangeProperty(display, supportwin, atom[NET_WM_PID], XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&pid, 1);

    /* Manage existing windows */
    XQueryTree(display, root, &dw1, &dw2, &wins, &nwins);
    for (i = 0; i < nwins; i++)
    {
        XGetWindowAttributes(display, wins[i], &attr);
        if (attr.override_redirect || (wins[i] == root)) continue;
        if (client_find(wins[i])) continue;
        client_new(wins[i]);
    }

    ewmh_set_client_list();

    wm_running = 1;
    wm_debug("Rigue started!");
}

void wm_quit()
{
    Client* c;
    for (c = head; c; c = c->next)
        kill_client(c);
    XClearWindow(display, root);
    XUngrabKey(display, AnyKey, AnyModifier, root);
    XUngrabButton(display, AnyKey, AnyModifier, root);
    XFlush(display);
    XSync(display, False);
    XSetInputFocus(display, root, RevertToPointerRoot, CurrentTime);
    wm_running = 0;
    wm_debug("Exiting rigue! Bye!");
}

int wm_recompile()
{
    int ret;

    wm_debug("Recompiling rigue");

    ret = system("make clean all");

    if (ret != 0)
    {
        wm_debug("Recompile failed");
        return False;
    }
    else
    {
        wm_debug("Recompile succeeded");
        return True;
    }
}

void wm_restart()
{
    pid_t pid;
    int ret;

    if (!(wm_recompile())) return;

    wm_debug("Restarting rigue");

    pid = fork();
    if (pid > 0)
        ret = execl("./rigue", "./rigue", NULL);
    else
        wm_quit();
}
