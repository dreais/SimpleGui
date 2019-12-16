//
// Created by rudreais on 03/12/2019.
//

#include <stdlib.h>
#include "../../Headers/simple_gui.h"
#include "../../Headers/Modules/buffer.h"

void win_push_back(instance *current, WINDOW *to_push)
{
	WINDOW **tmp;
	t_buff **tmp_buf;
	t_buff *new_buff =

	tmp = malloc(sizeof(WINDOW *) * ++current->win_count);
	tmp_buf = malloc(sizeof(t_buff *) * current->win_count);
	if (!tmp) {
		output_logs_str(PREFIX_ERROR, "Couldn't allocate new WINDOW array.\n");
		return;
	} else if (!tmp_buf) {
		output_logs_str(PREFIX_ERROR, "Couldn't allocate new BUFFER array.\n");
		return;
	}
	for (unsigned short i = 0; i < current->win_count - 1; i++) {
		tmp[i] = current->win[i];
		tmp_buf[i] = current->buffer[i];
	}
	tmp[current->win_count - 1] = to_push;
	tmp_buf[current->win_count - 1] = create_empty_buffer();
	free(current->win);
	free(current->buffer);
	current->win = tmp;
	current->buffer = tmp_buf;
	output_logs_str(PREFIX_DEBUG, "Pushed back 1 WINDOW successfully.\n");
}
