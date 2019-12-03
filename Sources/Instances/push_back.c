//
// Created by rudreais on 03/12/2019.
//

#include <stdlib.h>
#include "../../Headers/simple_gui.h"

void win_push_back(instance *current, WINDOW *to_push)
{
	WINDOW **tmp;

	tmp = malloc(sizeof(WINDOW *) * ++current->win_count);
	if (!tmp) {
		output_logs_str(PREFIX_ERROR, "Couldn't allocate new WINDOW array.\n");
		return;
	}
	for (unsigned short i = 0; i < current->win_count - 1; i++) {
		tmp[i] = current->win[i];
	}
	tmp[current->win_count - 1] = to_push;
	free(current->win);
	current->win = tmp;
	output_logs_str(PREFIX_DEBUG, "Pushed back 1 WINDOW successfully.\n");
}
