#include "config.h"
#include "queue.h"
#include "sorted.h"
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

queue_t* queue_create_static(int length)
{
	queue_t* reti = malloc(1 * sizeof(queue_t));
#ifdef SAFE_MODE
	if (reti == NULL)
	{
		fprintf(stderr, "ERROR [queue.c/%d]: Allocation memory for queue failed!\n", __LINE__);
		exit(EXIT_FAILURE);
	}

	if (reti != NULL)
	{
#endif // SAFE_MODE
		reti->length = length;
		reti->count = 0;
		reti->head = 0;
		reti->tail = 0;
		reti->next_head = 0;
		reti->data = malloc(reti->length * sizeof(experiment_t*));
#ifdef SAFE_MODE
		if (reti->data == NULL)
		{
			fprintf(stderr, "ERROR [queue.c/%d]: Allocation memory for 'queue->data <int[%d]>' failed!\n", __LINE__, reti->length);
			exit(EXIT_FAILURE);
		}
#endif // SAFE_MODE

#ifdef SAFE_MODE
	}
#endif // SAFE_MODE
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_push(queue_t* queue, experiment_t* data)
{
	bool reti = FALSE;
	if (queue_is_full(queue) == FALSE)
	{
		reti = TRUE;
		queue->data[queue->tail] = data;
		queue->tail++;
		queue->count++;
#ifdef DEBUG
		//printf("%d added to queue\n", data->id);
#endif // DEBUG

	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

experiment_t* queue_pop(queue_t* queue)
{
	experiment_t* reti = NULL;
	if (queue->count > 0)
	{
		reti = queue->data[queue->head];
		queue->head++;
		queue->count--;
#ifdef DEBUG
		//printf("%d popped from queue (new length: %d)\n", reti->id, queue->count);
#endif // DEBUG
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_is_empty(queue_t* queue)
{
	return (queue->count == 0 ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_is_full(queue_t* queue)
{
	return (queue->tail == queue->length ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int queue_count(queue_t* queue)
{
	return queue->count;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

experiment_t* queue_at(queue_t* queue, int index)
{
	experiment_t* reti = NULL;
	if (queue->head <= index && queue->tail > index)
	{
		reti = queue->data[index];
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_is_not_empty(queue_t* queue)
{
	bool reti = (queue_count(queue) >= 1) ? TRUE : FALSE;
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

experiment_t* queue_next(queue_t* queue)
{
	experiment_t* reti = NULL;
	if (queue_next_not_empty(queue) == TRUE)
	{
		reti = queue->data[queue->next_head];
		queue->next_head++;
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_next_not_empty(queue_t* queue)
{
	return (queue->next_head >= queue->tail) ? FALSE : TRUE;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void queue_reset_next_index(queue_t* queue)
{
	queue->next_head = queue->head;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

queue_t* queue_reverse_data(queue_t* queue)
{
	queue_t* reti = queue_create_static(queue_count(queue));
	for (int i = (queue->tail - 1); i >= queue->head; i--)
	{
		queue_push(reti, queue_at(queue, i));
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void queue_delete(queue_t* queue)
{
	free(queue->data);
	free(queue);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#ifdef DEBUG
void queue_print(queue_t* queue)
{
	for (int i = queue->head; i < queue->tail; i++)
	{
		printf("%d ", queue->data[i]->id);
	}
	printf("\n");
}
#endif // DEBUG

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_contains(queue_t* queue, experiment_t* element, sort_t sort)
{
	bool reti = FALSE;
	if (sort == NONE)
	{
		for (int i = queue->head; i <= queue->tail; i++)
		{
			if (queue_at(queue, i) == element)
			{
				reti = TRUE;
				break;
			}
		}
	}
	else
	{
		reti = queue_binary_search(queue, element, sort);
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_binary_search(queue_t* queue, experiment_t* element, sort_t sort)
{
	return queue_binary_search_recursive(queue, element, sort, queue->head, queue->tail);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_binary_search_recursive(queue_t* queue, experiment_t* element, sort_t sort, int start_index, int end_index)
{
	int index = queue_binary_search_next_index(start_index, end_index, queue);
	experiment_t* found = queue_at(queue, index);
#ifdef DEBUG
	printf("( %d %d %d) f:%d, s:%d [%d %d %d]\n", start_index, index, end_index, found->id, element->id, queue_at(queue, start_index)->id, queue_at(queue, index)->id, queue_at(queue, end_index)->id);
#endif // DEBUG

	if (found == element)
	{
#ifdef DEBUG
		printf(">> TRUE\n");
#endif // DEBUG

		return TRUE;
	}
	else if ((start_index == index && queue_index_in_queue(start_index, queue)) || (end_index == index && queue_index_in_queue(end_index, queue)))
	{
		if ((queue_at(queue, start_index) == element && queue_index_in_queue(start_index, queue) == TRUE) || (queue_at(queue, end_index) == element && queue_index_in_queue(end_index, queue) == TRUE))
		{
#ifdef DEBUG
			printf(">> TRUE\n");
#endif // DEBUG
			return TRUE;
		}
		else
		{
#ifdef DEBUG
			printf(">> FALSE\n");
#endif // DEBUG
			return FALSE;
		}
	}
	else if (index != -1)
	{
		if (sort == ASC)
		{
			if (found > element)
			{
				return queue_binary_search_recursive(queue, element, sort, start_index, index);
			}
			else if (found < element)
			{
				return queue_binary_search_recursive(queue, element, sort, index, end_index);
			}
		}
		else if (sort == DESC)
		{
			if (found > element)
			{
				return queue_binary_search_recursive(queue, element, sort, index, end_index);
			}
			else if (found < element)
			{
				return queue_binary_search_recursive(queue, element, sort, start_index, index);
			}
		}
		else
		{
			if ((queue_at(queue, start_index) == element && queue_index_in_queue(start_index, queue) == TRUE) || (queue_at(queue, end_index) == element && queue_index_in_queue(end_index, queue) == TRUE))
			{
#ifdef DEBUG
				printf(">> TRUE\n");
#endif // DEBUG
				return TRUE;
			}
		}
	}
	else if (index == -1)
	{
		if ((queue_at(queue, start_index) == element && queue_index_in_queue(start_index, queue) == TRUE) || (queue_at(queue, end_index) == element && queue_index_in_queue(end_index, queue)))
		{
#ifdef DEBUG
			printf(">> TRUE\n");
#endif // DEBUG
			return TRUE;
		}
	}
#ifdef DEBUG
	printf(">> FALSE\n");
#endif // DEBUG
	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int queue_binary_search_next_index(int start_index, int end_index, queue_t* queue)
{
	int reti = -1;
	int computed = (start_index + end_index) / 2;
	if (queue_index_in_queue(computed, queue) == TRUE && start_index != end_index)
	{
		reti = computed;
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_index_in_queue(int index, queue_t* queue)
{
	bool reti = FALSE;
	if (index >= queue->head && index < queue->tail)
	{
		reti = TRUE;
	}
	return reti;
}
