//
// Created by rudreais on 02/12/2019.
//

#include <stdio.h>
#include "../Headers/simple_gui.h"

void bin(unsigned n)
{
	/* step 1 */
	if (n > 1)
		bin(n/2);

	/* step 2 */
	printf("%d", n % 2);
}

int create_instance()
{
    return INSTANCE_CREATED;
}
