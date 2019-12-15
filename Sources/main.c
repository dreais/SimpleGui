#include <ncurses.h>
#include <pthread.h>
#include "../Headers/simple_gui.h"
#include "../Headers/properties.h"
#include "../Headers/window_manage.h"
#include "../Headers/Modules/mouse.h"

/**
 * this is an example program. please see the whole file and read through the flow to understand
 * how the lib is to be used.
 */

void print_stat(WINDOW *cur, int index)
{
	wmove(cur, 1, 1);
	wprintw(cur, "w%d", index+1);
	wmove(cur, 2, 1);
	wprintw(cur, "size x=%d", getmaxx(cur));
	wmove(cur, 3, 1);
	wprintw(cur, "size y=%d", getmaxy(cur));
	wmove(cur, 4, 1);
	wprintw(cur, "pos x=%d", getbegx(cur));
	wmove(cur, 5, 1);
	wprintw(cur, "pos y=%d", getbegy(cur));
}

void print_windows(instance *current)
{
	int ch;

	for (unsigned short i = 0; i < current->win_count; i++) {
		box(current->win[i], 0, 0);
		print_stat(current->win[i], i);
		wrefresh(current->win[i]);
		ch = getch();
		check_click(current);
	}
}

int main(void)
{
	instance inst_tmp;

	create_terminal(RAW|KEYPAD|NOECHO|NOCURSOR);
	output_logs_str(PREFIX_INFO, "Max Size X=%d\tSize Y=%d\n", getmaxx(stdscr), getmaxy(stdscr));
	inst_tmp = create_instance(-1);

	//inst_add_window(&inst_tmp, &(prop_t) {.posx = -1});
	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	output_logs_str(PREFIX_DEBUG, "Initializing over\n");
	// TODO inst_split_insert()
	clear();
	refresh();
	win_pop(&inst_tmp, 3);
	print_windows(&inst_tmp);

	destroy_win_arr(&inst_tmp);
	endwin();
	cancel_poll();
	return 0;
}
