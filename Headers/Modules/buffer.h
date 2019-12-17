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

#define P_INIT 0

#endif //SIMPLEGUI_BUFFER_H