//
// Created by rudreais on 15/12/2019.
//

#include <poll.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include "../../../Headers/simple_gui.h"
#include "../../../Headers/properties.h"
#include "../../../Headers/Modules/mouse.h"

static bool quit = false;

volatile pt coord_found = {-1, -1};
pthread_mutex_t mutexcoord = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cnd = PTHREAD_COND_INITIALIZER;

short find_window(instance *current, pt coord)
{
	for (unsigned short i = 0; i < current->win_count; i++) {
		if (is_in_window(current->win[i], coord)) {
			return (short) i;
		}
	}
	return -1;
}

extern pthread_t callThd[NUMTHRDS];

void cancel_poll(void)
{
	pthread_detach(callThd[0]);
	quit = true;
}

static bool accessing = false;

void *mouse_events(void *n)
{
	MEVENT event;
	struct pollfd fds = {.fd = STDIN_FILENO, .events = POLLIN};
	int ret_value = 0;

	(void) n;
	while (quit == false) {
		ret_value = poll(&fds, 1, 100);
		if (ret_value > 0) {
			accessing = true;
			if (fds.revents & POLLIN) {
				if (getmouse(&event) == OK) {
					if (event.bstate & BUTTON1_PRESSED) {
						output_logs_str(PREFIX_WARNING, "Clicked\n");
						coord_found = (pt) {.x = event.x, .y = event.y};
						continue;
					}
				}
			}
			accessing = false;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////
///		EVERYTHING ABOVE IS FROM OTHER THREAD		///
///////////////////////////////////////////////////////

// TODO: change return value
void click_coord(instance *current)
{
	while (accessing == true);
	if (coord_found.x > -1 && coord_found.y > -1) {
		output_logs_str(PREFIX_DEBUG, "Found at %d\n", 1+find_window(current, coord_found));
	}
}
