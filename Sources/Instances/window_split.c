//
// Created by rudreais on 09/12/2019.
//

#include "../Headers/simple_gui.h"
#include "../Headers/window_manage.h"

static unsigned short mode = SPLIT_MODE_DEFAULT;

void inst_split_win(instance *current, unsigned short g_mode, bool set_global)
{
	if (current->win_count < 2) {
		output_logs_str(PREFIX_WARNING, "Less than 2 WINDOW* in the pool. Exiting\n");
		return;
	}
	if (g_mode != mode && set_global == true) {
		mode = g_mode;
	}
}