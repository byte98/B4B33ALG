#include <stdio.h>
#include "structures.h"
#include "config.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

void check_outside_situation(model_t* model, sticky_note_t* note, result_t* result)
{
#ifdef DEBUG
	printf("Checking new sticky note from outside\n");
#endif // DEBUG
	bool counted = FALSE;
	for (int i = note->distance_from_left; i < note->distance_from_left + note->width; i++)
	{

		if (model->situation_out[i] < note->height)
		{
			model->situation_out[i] = note->height;
			if (counted == FALSE)
			{
				queue_push(model->notes_out, note->id);
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
	printf("Checking new sticky note from inside\n");
#endif // DEBUG
	bool counted = FALSE;
	for (int i = note->distance_from_left; i < note->distance_from_left + note->width; i++)
	{
		if (model->situation_in[i] < note->height)
		{
			model->situation_in[i] = note->height;
			if (counted == FALSE)
			{
				queue_push(model->notes_in, note->id);
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
	printf("visible_out: %d\nvisible_in: %d\nvisible_both: %d\nvisibile_one:%d\nunvisible: %d\n", result->visible_out, result->visible_in, result->visible_both, result->visible_one, result->unvisible);
#endif // DEBUG
#ifndef DEBUG
	printf("%d %d %d\n", result->visible_both, result->visible_one, result->unvisible);
#endif // !DEBUG
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int check_visible_both(model_t* model)
{
	int reti = 0;

	while (queue_next_not_empty(model->notes_in) == TRUE)
	{
		int element = queue_next(model->notes_in);
		if (queue_contains(model->notes_out, element, ASC) == TRUE)
		{
			reti++;
		}
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int check_visible_one(model_t* model)
{
	int reti = 0;

	queue_t* data_union = queue_create_static((queue_count(model->notes_in) + queue_count(model->notes_out)));
	queue_t* difference = queue_create_static(queue_count(model->notes_out));
	queue_reset_next_index(model->notes_in);
#ifdef DEBUG
	printf("Checking visibility from one side only...\n");
#endif // DEBUG

	while (queue_next_not_empty(model->notes_in) == TRUE)
	{
		int element = queue_next(model->notes_in);
		queue_push(data_union, element);

	}
	queue_reset_next_index(model->notes_in);
	queue_reset_next_index(model->notes_out);
	while (queue_next_not_empty(model->notes_out) == TRUE)
	{
		int element = queue_next(model->notes_out);
#ifdef DEBUG
		printf("___%d\n", element);
#endif // DEBUG

		if (queue_contains(data_union, element, DESC) == FALSE)
		{
			queue_push(difference, element);
		}
	}
	queue_reset_next_index(model->notes_out);
	queue_reset_next_index(difference);
	while (queue_next_not_empty(difference) == TRUE)
	{
		queue_push(data_union, queue_next(difference));
	}

	queue_reset_next_index(difference);
	queue_reset_next_index(data_union);

#ifdef DEBUG
	printf("-----UNION-----\n");
	printf("1st set:\n");
	queue_print(model->notes_in);
	printf("\n2nd set:\n");
	queue_print(model->notes_out);
	printf("\nUnion:\n");
	queue_print(data_union);
	printf("\n---------------\n");
#endif // DEBUG

	reti = queue_count(data_union);
	queue_delete(data_union);
	queue_delete(difference);

	return reti;
}
