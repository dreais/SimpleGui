//
// Created by rudreais on 17/12/2019.
//

#include <simple_gui.h>
#include <properties.h>

void apply_properties(WINDOW *win, int prop, short mode)
{
	switch (prop) {
		case P_WHITESPACE:
			break;
		case P_RED:
			wattr(win, COLOR_PAIR(RED), mode);
			break;
		default:
			break;
	}
}

void buffer_flush(instance *current, int index)
{
	WINDOW *win = current->win[index];
	t_buff *buf = current->buffer[index];
	unsigned short newline = 1;
	int y = 0, x, line_scroll = 0;

	buf->to_scroll = 0;
	(void) y; // the warning is just pissing me off (and i might use it again)
	wmove(win, newline, 1);
	for (short i = 0; i < buf->c_word; i++) {
		apply_properties(win, buf->properties[i], P_MODE_APPLY);
		for (short j = 0; buf->word_arr[i][j]; j++) {
			if (buf->word_arr[i][j] != '\n') {
				getyx(win, y, x);
				if (x == getmaxx(win) - 2) { // it's hard-coded, but -2 because we need to take the walls into consideration
					buf->to_scroll++;
					line_scroll = newline;
				} else
					waddch(win, buf->word_arr[i][j]);
			} else {
				wmove(win, ++newline, 1);
			}
		}
		apply_properties(win, buf->properties[i], P_MODE_UNAPPLY);
	}
	if (line_scroll != 0) {
		wmove(win, line_scroll, getmaxx(win)-1);
		waddch(win, '>');
	}
	output_logs_str(PREFIX_WARNING, "INDEX %d\tLeaving with %d scroll\n", index, buf->to_scroll);
}