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

void wb_append(instance *current, const char *str, int index);
void wb_write(instance *current, const char *str, int index);
t_buff *create_empty_buffer(void);
void buffer_flush(instance *current, int index);

short is_whitespace(const char c);
char **buffer_split_words(const char *str, short *c_word);

void buffer_scroll(instance *current);

#define DEFAULT_MODE 0
#define LOOK_WORDS 1

#define IS_WHITESPACE 1
#define IS_NOT_WHITESPACE 2

// PROPERTIES
#define P_MODE_APPLY 1
#define P_MODE_UNAPPLY 2

#define P_INIT 0
#define P_WHITESPACE 1
#define P_RED 2

#define wattr(win, CP, mode) (mode == P_MODE_APPLY) ? wattron(win, CP) : wattroff(win, CP)

#endif //SIMPLEGUI_BUFFER_H