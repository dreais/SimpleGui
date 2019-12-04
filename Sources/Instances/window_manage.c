//
// Created by rudreais on 04/12/2019.
//

#include "properties.h"
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

void inst_add_window(instance *current, prop_t *properties_window)
{
	WINDOW *new = NULL;
	int sizy = 0;
	int sizx = 0;
	int y, x;

	getbegyx(current->win[current->win_count-1], y, x);
	(void) new;
	if (non_empty_prop(properties_window)) {
		hit_windows(current, properties_window);
		new = new_win(properties_window);
		win_push_back(current, new);
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