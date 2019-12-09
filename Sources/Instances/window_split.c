//
// Created by rudreais on 09/12/2019.
//

#include "../Headers/simple_gui.h"
#include "../Headers/window_manage.h"

static unsigned short mode = SPLIT_MODE_DEFAULT;

static void split_half(instance *current, unsigned short g_mode)
{
	WINDOW *new, *prev = current->win[0];
	prop_t prop;

	if (g_mode == SPLIT_MODE_VERT) {
		prop = (prop_t) {.sizx = (COLS / 2) + (COLS % 2), .sizy = LINES,
				   .posx = COLS / 2, .posy = 0};
		wresize(prev, LINES, COLS / 2);
	} else if (g_mode == SPLIT_MODE_HORI) {
		prop = (prop_t) {.sizx = COLS, .sizy = (LINES / 2) + (LINES % 2),
				.posx = 0, .posy = LINES/2};
		wresize(prev, LINES / 2, COLS);
	}
	hit_windows(current, &prop);
	new = new_win(&prop);
	win_push_back(current, new);
}

static unsigned short fetch_n(instance *current)
{
	unsigned short n = 0;

	for (unsigned short i = current->win_count; i > 0; i--) {

	}
	return n;
}

void inst_split_win(instance *current, unsigned short g_mode, bool set_global)
{
	WINDOW *new, *prev = current->win[current->win_count-2];
	prop_t prop = {-1, -1, -1, -1};

	if (g_mode != mode && set_global == true) {
		output_logs_str(PREFIX_WARNING, "Switching to %s mode\n", (g_mode == SPLIT_MODE_VERT) ? "VERT" : "HORZ");
		mode = g_mode;
	}
	if (current->win_count < 2) {
		output_logs_str(PREFIX_WARNING, "Less than 2 WINDOW* in the pool.\n");
		split_half(current, g_mode);
		return;
	}
	if (mode == SPLIT_MODE_VERT) {
		output_logs_str(PREFIX_DEBUG, "N FETCHED=%d\n", fetch_n(current));
	} else if (mode == SPLIT_MODE_HORI) {
		output_logs_str(PREFIX_DEBUG, "N FETCHED=%d\n", fetch_n(current));
	}
}