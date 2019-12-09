#include <ncurses.h>
#include "../Headers/simple_gui.h"
#include "../Headers/properties.h"
#include "../Headers/window_manage.h"

/**
 * this is an example program. please see the whole file and read through the flow to understand
 * how the lib is to be used.
 */

int main(void)
{
	instance inst_tmp;

	create_terminal(RAW|KEYPAD|NOECHO|NOCURSOR);
	output_logs_str(PREFIX_INFO, "Max Size X=%d\tSize Y=%d\n", getmaxx(stdscr), getmaxy(stdscr));
	inst_tmp = create_instance(-1);

	//inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);
	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, false);
	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, false);
	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, false);

	refresh();
	for (unsigned int i = 0; i < inst_tmp.win_count; i++) {
		box(inst_tmp.win[i], 0, 0);
		wrefresh(inst_tmp.win[i]);
	}
	getch();
	endwin();
	return 0;
}
