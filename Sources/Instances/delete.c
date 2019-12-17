//
// Created by rudreais on 03/12/2019.
//

#include <stdlib.h>
#include "../../Headers/simple_gui.h"

static void free_buffer(t_buff *buff)
{
	for (short i = 0; i < buff->c_word; i++) {
		free(buff->properties[i]);
		free(buff->word_arr[i]);
	}
	free(buff->properties);
	free(buff->word_arr);
}

void destroy_win_arr(instance *to_free)
{
	for (unsigned short i = 0; i < to_free->win_count; i++) {
		delwin(to_free->win[i]);
		free_buffer(to_free->buffer[i]);
		free(to_free->buffer[i]);
	}
	free(to_free->win);
	free(to_free->buffer);
	to_free->win_count = 0;
}