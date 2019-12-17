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
	int y = 0, x, to_scroll = 0, line_scroll = 0;

	(void) y;
	wclear(win);
	wmove(win, newline, 1);
	for (short i = 0; i < buf->c_word; i++) {
		for (short j = 0; buf->word_arr[i][j]; j++) {
			if (buf->word_arr[i][j] != '\n') {
				getyx(win, y, x);
				if (x == getmaxx(win) - 2) {
					to_scroll++;
					line_scroll = newline;
				} else
					waddch(win, buf->word_arr[i][j]);
			} else {
				wmove(win, ++newline, 1);
			}
		}
	}
	box(win, 0, 0);
	if (line_scroll != 0) {
		wmove(win, line_scroll, getmaxx(win)-1);
		waddch(win, '>');
	}
}