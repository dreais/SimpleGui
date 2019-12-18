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

int main(void)
{
	instance inst_tmp;

	create_terminal(RAW|KEYPAD|NOECHO|NOCURSOR);
	inst_tmp = create_instance(-1);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_HORI, true);

	inst_split_win(&inst_tmp, SPLIT_MODE_VERT, true);

	clear();
	refresh();

	char *str = "test1 test2 test3\n";
	//wb_append(&inst_tmp, str, 0);
	//wb_append(&inst_tmp, str, 0);
	char *str2 = "nop nah \n, idk je \nouepbreftest test test test il faut plus e fezo ecrire test";
	wb_append(&inst_tmp, str2, 0);

	int ch = '\0';
	while (ch != 'q') {
		show_win(&inst_tmp);
		ch = getch();
	}
	destroy_win_arr(&inst_tmp);
	cancel_poll();
	endwin();
	return 0;
}
