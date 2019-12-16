//
// Created by rudreais on 03/12/2019.
//

#include <stdlib.h>
#include "../../Headers/simple_gui.h"

static void free_short_arr(char **arr, short size)
{
	(void) size;
	free(arr);
}

void destroy_win_arr(instance *to_free)
{
	for (unsigned short i = 0; i < to_free->win_count; i++) {
		delwin(to_free->win[i]);
		if (to_free->buffer[i]->c_word > 0)
			free_short_arr(to_free->buffer[i]->word_arr, to_free->buffer[i]->c_word);
		free(to_free->buffer[i]);
	}
	free(to_free->win);
	free(to_free->buffer);
	to_free->win_count = 0;
}