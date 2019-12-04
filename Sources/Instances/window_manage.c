//
// Created by rudreais on 04/12/2019.
//

#include <simple_gui.h>

static WINDOW *new_win(prop_t *properties)
{
	return newwin(properties->sizy, properties->sizx, properties->posy, properties->posx);
}

static int get_sizx(instance *current, int y)
{
	int sizx = 0;

	for (unsigned short i = current->win_count; i > 0; i--) {
		if (getbegy(current->win[i-1]) == y) {
			sizx += getmaxx(current->win[i-1]);
		}
	}
	return sizx;
}

void inst_add_window(instance *current, prop_t *properties_window)
{
	WINDOW *new = NULL;
	int sizy = 0;
	int sizx = 0;
	int y, x;

	getbegyx(current->win[current->win_count-1], y, x);
	(void) new;
	if (properties_window->posx > -1) {
		// TODO fill this case
		return;
	}
	for (unsigned short i = current->win_count; i > 0; i--) {
		if (getbegx(current->win[i-1]) == x) {
			sizy += getmaxy(current->win[i-1]);
		}
	}
	if (sizy < LINES) {
		int tmp = sizy;
		sizx = get_sizx(current, sizy);
		for (unsigned short i = 0; i < current->win_count; i++) {
			if (getbegy(current->win[i]) >= sizy) {
				output_logs_str(PREFIX_DEBUG, "Yes\n");
				if (sizx > getbegx(current->win[i]) && sizx < getmaxx(current->win[i]))
					sizy += getmaxy(current->win[i]);
			}
		}
		*properties_window = (prop_t) {.posy = tmp, .sizy = LINES - sizy, .posx = sizx, .sizx = COLS-sizx};
	} else {
		y = 0;
		sizx = get_sizx(current, y);
		for (unsigned short i = 0; i < current->win_count; i++) {
			if (getmaxx(current->win[i]) > sizx) {
				sizy -= getmaxy(current->win[i]);
			}
		}
		*properties_window = (prop_t) {.posx = sizx, .posy = 0, .sizx = COLS - sizx, .sizy = sizy};
	}
	new = new_win(properties_window);
	win_push_back(current, new);
}