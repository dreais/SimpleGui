//
// Created by rudreais on 04/12/2019.
//

#include <stdbool.h>
#include <properties.h>

bool is_in_window(WINDOW *win, pt coord)
{
	if ((coord.x >= getbegx(win) && coord.x <= getbegx(win) + getmaxx(win)) &&
		 (coord.y >= getbegy(win) && coord.y <= getbegy(win) + getmaxy(win))) {
		return true;
	}
	return false;
}

bool is_in_any_window(WINDOW **win, pt coord, unsigned short win_count)
{
	for (unsigned short i = 0; i < win_count; i++) {
		if (is_in_window(win[i], coord)) {
			return true;
		}
	}
	return false;
}

bool non_empty_prop(prop_t *prop)
{
	if (prop->posx > -1 && prop->posy > -1 &&
	prop->sizx > -1 && prop->sizy > -1) {
		return true;
	}
	return false;
}