#include "utils.h"
#include <stdio.h>

void util_print_int_array(int* array, int array_count)
{
	for (int i = 0; i < array_count; i++)
	{
		printf("%2d", array[i]);
		if (i < (array_count - 1))
		{
			printf(", ");
		}
	}
}
