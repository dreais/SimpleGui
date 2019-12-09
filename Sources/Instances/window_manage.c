//
// Created by rudreais on 04/12/2019.
//

#include "properties.h"
#include <simple_gui.h>

static void resize_window(WINDOW *to_resize, prop_t prop)
{
	output_logs_str(PREFIX_WARNING, "Resizing WINDOW, SizX=%d\tSizY=%d\n", prop.sizx, prop.sizy);
	wresize(to_resize, prop.sizy, prop.sizx);
	box(to_resize, 0, 0);
	wrefresh(to_resize);
}

static bool segm_hit_window(instance *current, pos_t *pos)
{
	WINDOW *win;

	for (unsigned short i = 0; i < current->win_count; i++) {
		win = current->win[i];
		if (getbegy(win) > pos->top_left.y && getbegy(win) + getmaxy(win) < pos->bottom_left.y) {
			if (getbegx(win) < pos->top_left.x && getbegx(win) + getmaxx(win) > pos->top_left.x) {
				output_logs_str(PREFIX_WARNING, "Straight hit in %d\n", i + 1);
				resize_window(win, (prop_t) {.posx = getbegx(win), .posy = getbegy(win),
								 .sizx = pos->top_left.x - getbegx(win), .sizy = getmaxy(win)});
			}
		}
	}
	return false;
}

static int get_sizy(instance *current, int x, int y)
{
	int sizy = 0;
	bool first_occ = false;

	output_logs_str(PREFIX_DEBUG, "Entering at %d,%d\n", x, y);
	output_logs_str(PREFIX_WARNING, "%d\n", is_in_any_window(current->win, (pt) {.x = x, .y = y+17}, current->win_count));
	for (int y_alt = y; y_alt < LINES; y_alt++) {
		if (!is_in_any_window(current->win, (pt) {.x = x, .y = y_alt}, current->win_count)) {
			if (first_occ == false) {
				first_occ = true;
			}
			sizy++;
		} else if (sizy != 0 && first_occ == true) {
			return sizy;
		}
	}
	output_logs_str(PREFIX_DEBUG, "Exiting with %d\n", sizy);
	return sizy;
}

static int get_sizx(instance *current, int x, int y)
{
	int sizx = 0;
	bool first_occ = false;

	for (int x_alt = x; x_alt < COLS; x_alt++) {
		if (!is_in_any_window(current->win, (pt) {.x = x_alt, .y = y}, current->win_count)) {
			if (first_occ == false) {
				first_occ = true;
			}
			sizx++;
		} else if (sizx != 0 && first_occ == true) {
			return sizx;
		}
	}
	return sizx;
}

static WINDOW *new_win(prop_t *properties)
{
	return newwin(properties->sizy, properties->sizx, properties->posy, properties->posx);
}

void hit_windows(instance *current, prop_t *prop)
{
	pos_t coords = {
			.top_left = {.x = prop->posx, .y = prop->posy},
			.top_right = {.x = prop->posx + prop->sizx, .y = prop->posy},
			.bottom_left = {.x = prop->posx, .y = prop->posy + prop->sizy},
			.bottom_right = {.x = prop->posx + prop->sizx, .y = prop->posy + prop->sizy}
	};
	WINDOW *cur_tmp;
	prop_t prop_tmp;

	for (unsigned short i = 0; i < current->win_count; i++) {
		cur_tmp = current->win[i];
		prop_tmp = (prop_t) {.posx = getbegx(cur_tmp), .posy = getbegy(cur_tmp),
				.sizx = getmaxx(cur_tmp), .sizy = getmaxy(cur_tmp)};
		if (is_in_window(cur_tmp, coords.top_left) || is_in_window(cur_tmp, coords.bottom_left)) {
			output_logs_str(PREFIX_WARNING, "Top-left or bottom-left point in %d\n", i+1);
			prop_tmp.sizx = coords.top_left.x - prop_tmp.posx;
			resize_window(cur_tmp, prop_tmp);
		} else if (is_in_window(cur_tmp, coords.top_right) || is_in_window(cur_tmp, coords.bottom_right)) {
			output_logs_str(PREFIX_WARNING, "Top-right or bottom-right point in %d\n", i+1);
			prop_tmp.posx = (coords.top_right.x - getbegx(cur_tmp)) + prop_tmp.posx;
			prop_tmp.sizx = prop_tmp.sizx - (coords.top_right.x - getbegx(cur_tmp));
			resize_window(cur_tmp, prop_tmp);
		}
	}
	segm_hit_window(current, &coords);
}

prop_t get_start(instance *current)
{
	prop_t new = {.posx = -1, .posy = -1, .sizx = -1, .sizy = -1};

	for (int y = 0, x = 0; x < COLS; x++, y = 0) {
		for (; y < LINES; y++) {
			if (!is_in_any_window(current->win, (pt) {.x = x, .y = y}, current->win_count)) {
				output_logs_str(PREFIX_DEBUG, "X=%d\tSIZX=%d\n", x, get_sizx(current, x, y));
				new = (prop_t) {.posx = x, .posy = y, .sizx = get_sizx(current, x, y), .sizy = get_sizy(current, x, y)};
				if (x > 0) {
					new.sizx++;
					new.posx--;
				}
				if (y > 0) {
					new.posy--;
					new.sizy = get_sizy(current, x, new.posy) + 1;
				}
				output_logs_str(PREFIX_DEBUG, "Y=%d\tSIZY=%d\n", new.posy, new.sizy);
				return new;
			} else {
				if (non_empty_prop(&new)) {
					return new;
				}
			}
		}
	}
	return new;
}