//
// Created by rudreais on 02/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "../Headers/simple_gui.h"

void bin(unsigned n)
{
	/* step 1 */
	if (n > 1)
		bin(n/2);

	/* step 2 */
	printf("%d", n % 2);
}

static WINDOW *new_win(prop_t *properties)
{
	return newwin(properties->sizy, properties->sizx, properties->posy, properties->posx);
}

int get_sizx(instance *current, int y)
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

instance create_instance(int prev_z_index)
{
	instance new = {0};

	output_logs_str(PREFIX_DEBUG, "Previous z-index at %d\n", prev_z_index);
	new.win_count = 1;
	new.win = malloc(sizeof(WINDOW *) * new.win_count);
	if (!new.win) {
		output_logs_str(PREFIX_ERROR, "Couldn't allocate new instance.\n");
		new.win_count = 0;
		return (instance) {0};
	}
	// TODO: set size using the other instances' ones
	new.win[0] = newwin(0, 0, 0, 0);
	new.z_index += prev_z_index;
    return new;
}
