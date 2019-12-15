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

pt coord_found = {-1, -1};
pthread_mutex_t mutexcoord = PTHREAD_MUTEX_INITIALIZER;

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

void *mouse_events(void *n)
{
	MEVENT event;
	struct pollfd fds = {.fd = STDIN_FILENO, .events = POLLIN};
	int ret_value = 0;

	pthread_mutex_init(&mutexcoord, NULL);
	while (quit == false) {
		ret_value = poll(&fds, 1, 100);
		if (ret_value > 0) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					pthread_mutex_lock(&mutexcoord);
					coord_found = (pt) {.x = event.x, .y = event.y};
					pthread_mutex_unlock(&mutexcoord);
					continue;
				}
			}
		}
	}
	pthread_mutex_destroy(&mutexcoord);
}