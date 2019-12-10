//
// Created by rudreais on 10/12/2019.
//

#include "../Headers/simple_gui.h"

void win_pop(instance *current, int index)
{
	if (index < current->win_count - 1) {
		output_logs_str(PREFIX_WARNING, "Removing WINDOW %d\n", index);
	} else {
		output_logs_str(PREFIX_WARNING, "Removing WINDOW %d\n", index);
		if (getbegx(current->win[index]) == getbegx(current->win[index-1])) {
			delwin(current->win[index]);
			current->win_count--;
			wresize(current->win[index-1], getmaxy(current->win[index-1]) * 2, getmaxx(current->win[index-1]));
		} else {
			delwin(current->win[index]);
			current->win_count--;
			wresize(current->win[index-1], getmaxy(current->win[index-1]), getmaxx(current->win[index-1]) * 2);
		}
	}
}