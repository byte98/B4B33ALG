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
		reti->data = malloc(reti->length * sizeof(int));
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

bool queue_push(queue_t* queue, int data)
{
	bool reti = FALSE;
	if (queue_is_full(queue) == FALSE)
	{
		reti = TRUE;
		queue->data[queue->tail] = data;
		queue->tail++;
		queue->count++;
#ifdef DEBUG
		printf("%d added to queue\n", data);
#endif // DEBUG

	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int queue_pop(queue_t* queue)
{
	int reti = NULL;
	if (queue->count > 0)
	{
		reti = queue->data[queue->head];
		queue->head++;
		queue->count--;
#ifdef DEBUG
		printf("%d popped from queue\n", reti);
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

int queue_at(queue_t* queue, int index)
{
	int reti = NULL;
	if (queue->head <= index && queue->tail > index)
	{
		reti = queue->data[index];
	}
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_has_next(queue_t* queue)
{
	bool reti = (queue_count(queue) >= 1) ? TRUE : FALSE;
	return reti;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#ifdef DEBUG
void queue_print(queue_t* queue)
{
	for (int i = queue->head; i < queue->tail; i++)
	{
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}
#endif // DEBUG

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool queue_contains(queue_t* queue, int element, sort_t sort)
{
	bool reti = FALSE;
	if (sort == ASC)
	{
		for (int i = queue->head; i < queue->tail; i++)
		{
			if (queue_at(queue, i) == element)
			{
				reti = TRUE;
				break;
			}
			if (queue_at(queue, i) > element)
			{
				break;
			}
		}
	}
	else if (sort == DESC)
	{
		for (int i = (queue->tail - 1); i >= queue->head; i++)
		{
			if (queue_at(queue, i) == element)
			{
				reti = TRUE;
				break;
			}
			if (queue_at(queue, i) < element)
			{
				break;
			}
		}
	}
	else if (sort == NONE)
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
	return reti;
}