//
// Created by rudreais on 17/12/2019.
//

#include <simple_gui.h
#include <properties.h>

static void p_borders(WINDOW *win, int index)
{
	if (index == w_get_active()) {
		wattron(win, COLOR_PAIR(RED));
		box(win, 0, 0);
		wattroff(win, COLOR_PAIR(RED));
	} else {
		box(win, 0, 0);
	}
}

void show_win(instance *current)
{
	WINDOW *win;

	for (unsigned short i = 0; i < current->win_count; i++) {
		win = current->win[i];
		for (int j = 0; j < getmaxy(current->win[i]); j++) {
			wmove(win, j, 0);
			wprintw(win, "\n");
		}
		p_borders(win, i);
		buffer_flush(current, i);
		wrefresh(win);
	}
}