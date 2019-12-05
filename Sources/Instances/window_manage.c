//
// Created by rudreais on 04/12/2019.
//

#include "properties.h"
#include <simple_gui.h>

static WINDOW *new_win(prop_t *properties)
{
	return newwin(properties->sizy, properties->sizx, properties->posy, properties->posx);
}

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

static void hit_windows(instance *current, prop_t *prop)
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

static int get_sizy(instance *current, int x, int *y_ptr)
{
	int sizy = 0;
	bool first_enc = false;

	for (int y = 0; y < LINES; y++) {
		if (!is_in_any_window(current->win, (pt) {.x = x, .y = y}, current->win_count)) {
			if (first_enc == false) {
				first_enc = true;
				*y_ptr = y - 1;
			}
			sizy++;
		}
	}
	return sizy;
}

static prop_t get_start(instance *current)
{
	int sizx = COLS, sizy = 0;

	for (int y, x = 0; x < COLS; x++) {
		y = 0;
		sizy = get_sizy(current, x, &y);
		if (sizy < LINES) {
			for (unsigned short i = 0; i < current->win_count; i++) {
				if (getbegy(current->win[i]) == y) {
					sizx = sizx - getmaxx(current->win[i]);
					output_logs_str(PREFIX_ERROR, "Test\n");
				}
			}
			output_logs_str(PREFIX_DEBUG, "SizX=%d\n", sizx);
			output_logs_str(PREFIX_DEBUG, "X=%d\n", x);
			output_logs_str(PREFIX_DEBUG, "SizY=%d\n", sizy);
			output_logs_str(PREFIX_DEBUG, "Y=%d\n", y);
			return (prop_t) {.posx = x, .posy = y, .sizy = sizy, .sizx = sizx};
		}
		sizx = COLS;
	}
}

void inst_add_window(instance *current, prop_t *properties_window)
{
	WINDOW *new = NULL;

	if (non_empty_prop(properties_window)) {
		new = newwin(0, 0, 0, 0);
		win_push_back(current, new);
		return;
	}
	*properties_window = get_start(current);
	new = new_win(properties_window);
	win_push_back(current, new);
}