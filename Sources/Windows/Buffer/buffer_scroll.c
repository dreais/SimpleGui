//
// Created by rudreais on 13/02/2020.
//

#include <simple_gui.h>

void buffer_scroll(instance *current)
{
    int active_w = w_get_active();

    output_logs_str(PREFIX_DEBUG, "Active: %d\n", active_w);
    if (active_w >= 0) {
        output_logs_str(PREFIX_DEBUG, "SCROLLING: %d\n",
                current->buffer[active_w]->to_scroll);
        if (current->buffer[active_w]->to_scroll > 0) {
            output_logs_str(PREFIX_DEBUG, "TEXT TO SCROLL\n");
        }
    }
}