//
// Created by rudreais on 14/12/2019.
//

#include <string.h>
#include <malloc.h>
#include "../../../Headers/simple_gui.h"

static short get_words(const char *str)
{
	short count = 0;

	for (unsigned int i = 0; str[i]; i++) {
		if (str[i] == ' ')
			count++;
	}
	return ++count;
}

static void append_inst_buffer(instance *current, char **arr, int index, short words)
{
	char **new;
	t_buff *cur = current->buffer[index];
	int count = 0;

	if (cur->word_arr == NULL) {
		cur->c_word = words;
		cur->word_arr = arr;
		return;
	}
	new = malloc(sizeof(char *) * (words + cur->c_word));
	for (short i = 0; i < (words + cur->c_word); i++) {
		if (i < cur->c_word)
			new[i] = cur->word_arr[i];
		else {
			new[i] = arr[count];
		}
	}
	cur->word_arr = new;
	cur->c_word += words;
	free(arr);
}

void wb_write(instance *current, const char *str, int index)
{
	char *delim = " ";
	char *tmp = strdup(str);
	char *tok = NULL;
	int i = 0;
	short c_word = get_words(str);
	char **arr = malloc(sizeof(char *) * c_word);

	if (index < 0 || index > (current->win_count-1)) {
		output_logs_str(PREFIX_ERROR, "Selected WINDOW does not exist.\n");
		return;
	}
	for (tok = strtok(tmp, delim); tok != NULL;) {
		arr[i++] = strdup(tok);
		tok = strtok(NULL, delim);
	}
	free(tmp);
	append_inst_buffer(current, arr, index, c_word);
	for (short x = 0; x < current->buffer[index]->c_word; x++) {
		wprintw(current->win[index], "%s", current->buffer[index]->word_arr[x]);
	}
}