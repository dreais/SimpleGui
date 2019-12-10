//
// Created by rudreais on 09/12/2019.
//

#include "../Headers/simple_gui.h"
#include "../Headers/window_manage.h"
#include "../Headers/properties.h"

static unsigned short mode = SPLIT_MODE_DEFAULT;
static unsigned short last_mode = SPLIT_MODE_DEFAULT;

static void split_half(instance *current, unsigned short g_mode, int index)
{
	WINDOW *new, *prev = current->win[index];
	prop_t prop;

	if (g_mode == SPLIT_MODE_VERT) {
		prop = (prop_t) {.sizx = getmaxx(prev) / 2, .sizy = getmaxy(prev),
				   .posx = getbegx(prev) + (getmaxx(prev) / 2), .posy = getbegy(prev)};
		wresize(prev, getmaxy(prev), getmaxx(prev) / 2);
	} else if (g_mode == SPLIT_MODE_HORI) {
		prop = (prop_t) {.sizx = getmaxx(prev), .sizy = getmaxy(prev) / 2,
				.posx = getbegx(prev), .posy = getbegy(prev) + (getmaxy(prev) / 2)};
		wresize(prev, getmaxy(prev) / 2, getmaxx(prev));
	}
	new = new_win(&prop);
	win_push_back(current, new);
}

static unsigned short fetch_n(instance *current)
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

static void split_n_window(instance *current, unsigned short n, unsigned short offset)
{
	WINDOW *to_add;
	prop_t new;
	float cols = COLS * (1.0/(n+1.0));
	float lines = LINES * (1.0/(n+1.0));
	int count = 0;

	new.posx = (mode != SPLIT_MODE_HORI) ? offset : getbegx(current->win[current->win_count - n]);
	new.posy = (mode == SPLIT_MODE_HORI) ? offset : getbegy(current->win[current->win_count - n]);
	new.sizx = (mode != SPLIT_MODE_HORI) ? (int) cols : getmaxx(current->win[current->win_count - n]);
	new.sizy = (mode == SPLIT_MODE_HORI) ? (int) lines : getmaxy(current->win[current->win_count - n]);
	for (unsigned short i = current->win_count - n; i < current->win_count; i++) {
		output_logs_str(PREFIX_ERROR, "-----\tITERATION %d\t-----\n", i+1);
		if (mode == SPLIT_MODE_VERT) {
			new.posx = offset + (getmaxx(current->win[current->win_count - n])) * count++;
			resize_window(current->win[i], new);
		} else {
			new.posy = offset + (getmaxy(current->win[current->win_count - n])) * count++;
			resize_window(current->win[i], new);
		}
	}
	if (mode == SPLIT_MODE_VERT) {
		new.posx = offset + (getmaxx(current->win[current->win_count - n])) * n;
	} else if (mode == SPLIT_MODE_HORI) {
		new.posy = offset + (getmaxy(current->win[current->win_count - n])) * n;
	}
	to_add = new_win(&new);
	win_push_back(current, to_add);
}

void inst_split_win(instance *current, unsigned short g_mode, bool set_global)
{
	unsigned short offset, n;

	n = fetch_n(current);
	if (g_mode != last_mode) {
		last_mode = g_mode;
		output_logs_str(PREFIX_DEBUG, "Splitting mode changed.\n");
		split_half(current, g_mode, current->win_count - 1);
		return;
	}
	if (g_mode != mode && set_global == true) {
		output_logs_str(PREFIX_WARNING, "Switching to %s mode\n", (g_mode == SPLIT_MODE_VERT) ? "VERT" : "HORZ");
		mode = g_mode;
	}
	if (current->win_count < 2) {
		output_logs_str(PREFIX_WARNING, "Less than 2 WINDOW* in the pool.\n");
		split_half(current, g_mode, 0);
		return;
	}
	output_logs_str(PREFIX_DEBUG, "N FETCHED=%d\n", n);
	if (mode == SPLIT_MODE_VERT) {
		offset = getbegx(current->win[current->win_count - n]);
		split_n_window(current, n, offset);
	} else if (mode == SPLIT_MODE_HORI) {
		offset = getbegy(current->win[current->win_count - n]);
		split_n_window(current, n, offset);
	}
}