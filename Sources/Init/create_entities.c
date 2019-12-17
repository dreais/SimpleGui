//
// Created by rudreais on 02/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <Modules/mouse.h>

pthread_t callThd[NUMTHRDS];

void bin(unsigned n)
{
	/* step 1 */
	if (n > 1)
		bin(n/2);

	/* step 2 */
	printf("%d", n % 2);
}

void open_thread(void)
{
	mousemask(BUTTON1_CLICKED, NULL);
	pthread_create(&callThd[0], NULL, mouse_events, NULL);
}

instance create_instance(int prev_z_index)
{
	instance new = {0};

	new.win_count = 1;
	new.win = malloc(sizeof(WINDOW *) * new.win_count);
	new.buffer = malloc(sizeof(t_buff *) * new.win_count);
	if (!new.win) {
		output_logs_str(PREFIX_ERROR, "Couldn't allocate new instance.\n");
		new.win_count = 0;
		return (instance) {0};
	}
	new.win[0] = newwin(0, 0, 0, 0);
	new.buffer[0] = create_empty_buffer();
	new.z_index += prev_z_index;
	set_instance(&new);
	open_thread();
    return new;
}
