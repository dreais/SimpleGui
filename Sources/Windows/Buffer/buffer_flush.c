//
// Created by rudreais on 17/12/2019.
//

#include <string.h>
#include "../../../Headers/simple_gui.h"

void buffer_flush(instance *current, int index)
{
	WINDOW *win = current->win[index];
	t_buff *buf = current->buffer[index];
	unsigned short newline = 1;

	wclear(win);
	wmove(win, newline, 1);
	for (short i = 0; i < buf->c_word; i++) {
		for (short j = 0; buf->word_arr[i][j]; j++) {
			if (buf->word_arr[i][j] != '\n') {
				waddch(win, buf->word_arr[i][j]);
			} else {
				wmove(win, ++newline, 1);
			}
		}
	}
	wrefresh(win);
}