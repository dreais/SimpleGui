//
// Created by rudreais on 04/12/2019.
//

#include "properties.h"
#include "window_manage.h"

void resize_window(WINDOW *to_resize, prop_t prop)
{
	mvwin(to_resize, prop.posy, prop.posx);
	wresize(to_resize, prop.sizy, prop.sizx);
}

static bool segm_hit_window(instance *current, pos_t *pos)
{
	WINDOW *win;

	for (unsigned short i = 0; i < current->win_count; i++) {
		win = current->win[i];
		if (getbegy(win) > pos->top_left.y && getbegy(win) + getmaxy(win) < pos->bottom_left.y) {
			if (getbegx(win) < pos->top_left.x && getbegx(win) + getmaxx(win) > pos->top_left.x) {
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

WINDOW *new_win(prop_t *properties)
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
			prop_tmp.sizx = coords.top_left.x - prop_tmp.posx;
			resize_window(cur_tmp, prop_tmp);
		} else if (is_in_window(cur_tmp, coords.top_right) || is_in_window(cur_tmp, coords.bottom_right)) {
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
				new = (prop_t) {.posx = x, .posy = y, .sizx = get_sizx(current, x, y), .sizy = get_sizy(current, x, y)};
				if (x > 0) {
					new.sizx++;
					new.posx--;
				}
				if (y > 0) {
					new.posy--;
					new.sizy = get_sizy(current, x, new.posy) + 1;
				}
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

unsigned short fetch_n(instance *current)
{
	unsigned short n = 1;
	prop_t def = {-1, -1, -1, -1};
	int sizx, sizy;

	for (unsigned short i = current->win_count; i > 0; i--) {
		if (!non_empty_prop(&def)) {
			def = (prop_t) {.sizx = getmaxx(current->win[i-1]),
					.sizy = getmaxy(current->win[i-1])};
		} else {
			sizx = getmaxx(current->win[i - 1]);
			sizy = getmaxy(current->win[i - 1]);
			if ((sizx == def.sizx || sizx == def.sizx - 1) &&
				(sizy == def.sizy || sizy == def.sizy - 1)) {
				n++;
			}
		}
	}
	return n;
}

unsigned short fetch_n_before(instance *current, int index)
{
	int mode = FETCH_MODE(current->win[index], current->win[index-1]);
	unsigned short i = index - 1, n = 0;

	while (i > 0) {
		if (FETCH_MODE(current->win[i], current->win[index]) == mode) {
			n++;
		} else {
			return n;
		}
		i--;
	}
	return n;
}

unsigned short fetch_n_after(instance *current, int index)
{
	return (current->win_count - 1) - index;
}