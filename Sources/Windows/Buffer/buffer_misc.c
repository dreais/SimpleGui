//
// Created by rudreais on 17/12/2019.
//

#include <string.h>
#include <stdlib.h>
#include <Modules/buffer.h>
#include <easylogs.h>

static short c_word_static = 0;

static char *sub_str(const char *str, unsigned int i, unsigned int length)
{
	char *new = malloc(sizeof(char) * length + 1);

	new[length] = '\0';
	for (unsigned int index = 0; index < length; index++) {
		new[index] = str[(i - length) + index];
	}
	return new;
}

static char **divide_str(const char *str, unsigned int mode)
{
	char **new = NULL;
	short switch_mode;
	short n_word = 1;
	unsigned int length = 0, prev_i = 0, count = 0;

	switch_mode = is_whitespace(str[0]);
	if (mode == DEFAULT_MODE) {
		divide_str(str, LOOK_WORDS);
		n_word = c_word_static;
		new = malloc(sizeof(char *) * n_word + 1);
		new[n_word - 1] = NULL;
	}
	for (unsigned int i = 1; str[i]; i++) {
		if (is_whitespace(str[i]) == switch_mode) {
			continue;
		} else {
			switch_mode = is_whitespace(str[i]);
			if (mode == LOOK_WORDS) {
				n_word++;
			} else {
				length = i - prev_i;
				new[count++] = sub_str(str, i, length);
				prev_i = i;
			}
		}
	}
	if (mode == DEFAULT_MODE) {
		new[count] = sub_str(str, strlen(str), strlen(str) - prev_i);
	} else {
		c_word_static = n_word;
		return NULL;
	}
	return new;
}

short is_whitespace(const char c)
{
	// TODO: use a defined array
	if (c == ' ' || c == '\t' || c == '\n')
		return IS_WHITESPACE;
	return IS_NOT_WHITESPACE;
}

char **buffer_split_words(const char *str, short *c_word)
{
	char **new = NULL;

	new = divide_str(str, DEFAULT_MODE);
	*c_word = c_word_static;
	if (new == NULL) {
		output_logs_str(PREFIX_WARNING, "ARRAY IS NULL\n");
	}
	return new;
}