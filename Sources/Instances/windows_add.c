//
// Created by rudreais on 09/12/2019.
//

#include "../Headers/simple_gui.h"
#include "../Headers/properties.h"
#include "../Headers/window_manage.h"

// begins at 1 since the very first one will not be created here (for now)
// /+TODO for visibility
static int counter = 1;
void inst_add_window(instance *current, prop_t *properties_window)
{
	WINDOW *new = NULL;

	if (non_empty_prop(properties_window)) {
		output_logs_str(PREFIX_DEBUG, "WINDOW N°%d\n", ++counter);
		hit_windows(current, properties_window);
		new = new_win(properties_window);
		win_push_back(current, new);
		return;
	}
	output_logs_str(PREFIX_DEBUG, "WINDOW N°%d\n", ++counter);
	*properties_window = get_start(current);
	if (non_empty_prop(properties_window)) {
		new = new_win(properties_window);
		win_push_back(current, new);
	}
}