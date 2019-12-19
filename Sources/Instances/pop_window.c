//
// Created by rudreais on 10/12/2019.
//

#include <simple_gui.h>
#include <window_manage.h>

void win_pop(instance *current, int index)
{
	WINDOW *prev, *next;
	unsigned short n = 0;

	if (current->win_count == 1) {
		output_logs_str(PREFIX_ERROR, "No WINDOW to remove.\n");
		return;
	}
	output_logs_str(PREFIX_WARNING, "Removing WINDOW %d\n", index+1);
	// /+/TODO removing window at index 0
	if (index < current->win_count - 1) {
		output_logs_str(PREFIX_DEBUG, "Index lower\n");
		prev = current->win[index-1];
		next = current->win[index+1];
		n = fetch_n_before(current, index) + fetch_n_after(current, index);
		delwin(current->win[index]);
		current->win_count--;
		(void) n;
		if (FETCH_MODE(prev, next) == SPLIT_MODE_HORI) {

		} else if (FETCH_MODE(prev, next) == SPLIT_MODE_VERT) {

		} else { // if they don't have the same mode at all

		}
		output_logs_str(PREFIX_WARNING, "N = %d\n", fetch_n(current));
	} else {
		prev = current->win[index-1];
		if (FETCH_MODE(current->win[index], prev) == SPLIT_MODE_HORI) {
			wresize(prev, getmaxy(prev) * 2, getmaxx(prev));
		} else {
			wresize(prev, getmaxy(prev), getmaxx(prev) * 2);
		}
		delwin(current->win[index]);
		current->win_count--;
	}
}