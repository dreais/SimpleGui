//
// Created by rudreais on 03/12/2019.
//

#include <stdlib.h>
#include "../../Headers/simple_gui.h"

void destroy_win_arr(instance *to_free)
{
	for (unsigned short i = 0; i < to_free->win_count; i++) {
		delwin(to_free->win[i]);
		free(to_free->buffer[i]);
	}
	free(to_free->win);
	free(to_free->buffer);
	to_free->win_count = 0;
}