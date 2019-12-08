#include <ncurses.h>
#include "../Headers/simple_gui.h"
#include "../Headers/properties.h"

/**
 * this is an example program. please see the whole file and read through the flow to understand
 * how the lib is to be used.
 */

int main(void)
{
	instance inst_tmp;

	create_terminal(RAW|KEYPAD|NOECHO|NOCURSOR);
	refresh();
	output_logs_str(PREFIX_INFO, "Max Size X=%d\tSize Y=%d\n", getmaxx(stdscr), getmaxy(stdscr));
	inst_tmp = create_instance(-1);
	// create_instance is similar to inst_add_window, and might be replaced
	wresize(inst_tmp.win[0], 20, 50);
	box(inst_tmp.win[0], 0, 0);
	mvwprintw(inst_tmp.win[0], 1, 1, "1");
	wgetch(inst_tmp.win[0]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	wresize(inst_tmp.win[1], 20, 60);
	box(inst_tmp.win[1], 0, 0);
	mvwprintw(inst_tmp.win[1], 1, 1, "2");
	wgetch(inst_tmp.win[1]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	box(inst_tmp.win[2], 0, 0);
	mvwprintw(inst_tmp.win[2], 1, 1, "3");
	wgetch(inst_tmp.win[2]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	box(inst_tmp.win[3], 0, 0);
	mvwprintw(inst_tmp.win[3], 1, 1, "4");
	wgetch(inst_tmp.win[3]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	box(inst_tmp.win[4], 0, 0);
	mvwprintw(inst_tmp.win[4], 1, 1, "5");
	wgetch(inst_tmp.win[4]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = 80, .posy = 16, .sizx = COLS - 80, .sizy = 28});
	box(inst_tmp.win[5], 0, 0);
	mvwprintw(inst_tmp.win[5], 1, 1, "6");
	wgetch(inst_tmp.win[5]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	box(inst_tmp.win[6], 0, 0);
	mvwprintw(inst_tmp.win[6], 1, 1, "7");
	wgetch(inst_tmp.win[6]);

	inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	box(inst_tmp.win[7], 0, 0);
	mvwprintw(inst_tmp.win[7], 1, 1, "8");
	wgetch(inst_tmp.win[7]);

	clear();
	refresh();
	for (unsigned int i = 0; i < inst_tmp.win_count; i++) {
		box(inst_tmp.win[i], 0, 0);
		wrefresh(inst_tmp.win[i]);
	}
	getch();
	endwin();
	return 0;
}