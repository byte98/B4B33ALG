#include <stdio.h>
#include "structures.h"
#include "config.h"


//-----------------------------------------------------------------------------------------------------------------------------------------------

void check_outside_situation(model_t* model, sticky_note_t* note, result_t* result)
{
#ifdef DEBUG
	printf("Checking new sticky note from inside\n");
#endif // DEBUG
	bool counted = FALSE;
	for (int i = note->distance_from_left; i < note->distance_from_left + note->width; i++)
	{
		if (model->situation_out[i] < note->height)
		{
			model->situation_out[i] = note->height;
			if (counted == FALSE)
			{
				counted = TRUE;
				result->visible_out++;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void check_inside_situation(model_t* model, sticky_note_t* note, result_t* result)
{
#ifdef DEBUG
	printf("Checking new sticky note from outside\n");
#endif // DEBUG
	bool counted = FALSE;
	for (int i = note->distance_from_left; i < note->distance_from_left + note->width; i++)
	{
		if (model->situation_in[i] < note->height)
		{
			model->situation_in[i] = note->height;
			if (counted == FALSE)
			{
				counted = TRUE;
				result->visible_in++;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void print_result(result_t* result)
{
#ifdef DEBUG
	printf("visible_out: %d\nvisible_in: %d\nvisible_both: %d\nunvisible: %d\n", result->visible_out, result->visible_in, result->visible_both, result->unvisible);
#endif // DEBUG
#ifndef DEBUG
	printf("%d %d %d\n", result->visible_both, (result->visible_in + result->visible_out), result->unvisible);
#endif // !DEBUG
}