//
// Created by rudreais on 14/12/2019.
//

#ifndef SIMPLEGUI_BUFFER_H
#define SIMPLEGUI_BUFFER_H

#include "../instance.h"

/** in the future:
 * DEPENDENCIES:
 * scroll, input, mouse (optional)
 */

void wb_write(instance *current, const char *str, int index);
t_buff *create_empty_buffer(void);
void buffer_flush(instance *current, int index);

short is_whitespace(const char c);
char **buffer_split_words(const char *str, short *c_word);

#define DEFAULT_MODE 0
#define LOOK_WORDS 1

#define IS_WHITESPACE 1
#define IS_NOT_WHITESPACE 2

#define P_INIT 0
#define P_WHITESPACE 1

#endif //SIMPLEGUI_BUFFER_H