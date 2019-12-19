//
// Created by rudreais on 18/12/2019.
//

#include <simple_gui.h>
#include <malloc.h>

extern void append_inst_buffer(instance *current, char **arr, int index, short words);

static void empty_current_buffer(t_buff *current)
{
	for (short i = 0; i < current->c_word; i++) {
		current->properties = 0;
		free(current->word_arr[i]);
		current->word_arr[i] = NULL;
	}
	free(current->properties);
	free(current->word_arr);
	current->word_arr = NULL;
}

void wb_write(instance *current, const char *str, int index)
{
	char **arr;

	if (index < 0 || index > (current->win_count-1)) {
		output_logs_str(PREFIX_ERROR, "Selected WINDOW does not exist.\n");
		return;
	}
	empty_current_buffer(current->buffer[index]);
	arr = buffer_split_words(str, &current->buffer[index]->c_word);
	append_inst_buffer(current, arr, index, current->buffer[index]->c_word);
	buffer_flush(current, index);
}