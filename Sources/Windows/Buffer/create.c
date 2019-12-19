//
// Created by rudreais on 16/12/2019.
//

#include <stdlib.h>
#include <instance.h>

t_buff *create_empty_buffer(void)
{
	t_buff *new = malloc(sizeof(t_buff) * 1);

	new->word_arr = NULL;
	new->properties = NULL;
	new->scroll_size = 0;
	new->c_line = 0;
	new->c_word = 0;
	return new;
}