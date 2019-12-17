//
// Created by rudreais on 17/12/2019.
//

#include "../Headers/simple_gui.h"

void show_win(instance *current)
{
	WINDOW *win;

	for (unsigned short i = 0; i < current->win_count; i++) {
		win = current->win[i];
		buffer_flush(current, i);
		wrefresh(win);
	}
}