//
// Created by rudreais on 17/12/2019.
//

#include <stdlib.h>
#include <simple_gui.h>
#include <properties.h>

static short active_w = -1;
static instance *cur_ptr;
static bool already_allocated = false;

static short find_window(pt coord)
{
	for (unsigned short i = 0; i < cur_ptr->win_count; i++) {
		if (is_in_window(cur_ptr->win[i], coord)) {
			return (short) i;
		}
	}
	return -1;
}

void w_set_active(pt coord)
{
	short tmp = active_w;

	active_w = find_window(coord);
	if (active_w == -1) {
		active_w = tmp;
	}
	output_logs_str(PREFIX_INFO, "New window=%d\n", 1+find_window(coord));
}

short w_get_active(void)
{
	return active_w;
}

void set_instance(instance *current)
{
	if (already_allocated == false) {
		output_logs_str(PREFIX_INFO, "Setting up new instance as active.\n");
		cur_ptr = malloc(sizeof(instance));
		already_allocated = true;
	} else {
		cur_ptr = realloc(cur_ptr, sizeof(instance));
	}
	*cur_ptr = *current;
}
