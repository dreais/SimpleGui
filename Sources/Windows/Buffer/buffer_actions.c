//
// Created by rudreais on 14/12/2019.
//

#include <string.h>
#include <malloc.h>
#include <simple_gui.h>

static void append_inst_buffer(instance *current, char **arr, int index, short words)
{
	char **new;
	int *prop_new;
	t_buff *cur = current->buffer[index];
	int count = 0;

	if (cur->word_arr == NULL) {
		cur->word_arr = arr;
		cur->properties = malloc(sizeof(int *) * words);
		for (short i = 0; i < words; i++) {
			cur->properties = malloc(sizeof(int) * words);
			cur->properties[i] = P_INIT;
		}
		cur->c_word = words;
		return;
	}
	new = malloc(sizeof(char *) * (words + cur->c_word));
	prop_new = malloc(sizeof(int) * (words + cur->c_word));
	for (short i = 0; i < (words + cur->c_word); i++) {
		if (i < cur->c_word) {
			new[i] = cur->word_arr[i];
			prop_new[i] = cur->properties[i];
		} else {
			new[i] = arr[count++];
			if (is_whitespace(new[i][0]) == IS_WHITESPACE) {
				prop_new[i] = P_WHITESPACE;
			} else {
				prop_new[i] = P_INIT;
			}
		}
	}
	cur->word_arr = new;
	cur->properties = prop_new;
	cur->c_word += words;
	free(arr);
}

void wb_write(instance *current, const char *str, int index)
{
	char **arr;

	if (index < 0 || index > (current->win_count-1)) {
		output_logs_str(PREFIX_ERROR, "Selected WINDOW does not exist.\n");
		return;
	}
	arr = buffer_split_words(str, &current->buffer[index]->c_word);
	append_inst_buffer(current, arr, index, current->buffer[index]->c_word);
	buffer_flush(current, index);
}