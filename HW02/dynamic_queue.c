#include "dynamic_queue.h"
#include <stdlib.h>

dyn_queue_t* dyn_queue_create()
{
	dyn_queue_t* reti = malloc(sizeof(dyn_queue_t));
	if (reti != NULL)
	{
		reti->capacity = 2;
		reti->count = 0;
		reti->data = malloc(reti->capacity * sizeof(laboratory_t*));
		reti->head = 0;
		reti->tail = 0;
		reti->next = 0;
	}
	return reti;
}

bool dyn_queue_push(dyn_queue_t* queue, laboratory_t* item)
{
	bool reti = TRUE;
	if (queue->capacity < queue->tail + 1)
	{
		reti = dyn_queue_upscale(queue);
	}
	if (reti == TRUE)
	{
		queue->data[queue->tail] = item;
		queue->tail++;
		queue->count++;
	}
	return reti;
}

laboratory_t* dyn_queue_pop(dyn_queue_t* queue)
{
	laboratory_t* reti = NULL;
	if (dyn_queue_is_empty(queue) == FALSE)
	{
		reti = queue->data[queue->head];
		queue->head++;
		queue->count--;
	}

	return reti;
}

bool dyn_queue_is_empty(dyn_queue_t* queue)
{
	return (queue->count == 0 ? TRUE : FALSE);
}

bool dyn_queue_upscale(dyn_queue_t* queue)
{
	bool reti = FALSE;
	laboratory_t** new_data = realloc(queue->data, queue->capacity * DYN_QUEUE_UPSCALE * sizeof(laboratory_t*));
	if (new_data != NULL)
	{
		queue->data = new_data;
		reti = TRUE;
		queue->capacity = queue->capacity * DYN_QUEUE_UPSCALE;
	}

	return reti;
}

void dyn_queue_delete(dyn_queue_t* queue)
{
	free(queue->data);
	free(queue);
}

bool dyn_queue_has_next(dyn_queue_t* queue)
{
	return ((queue->next + 1) == queue->tail ? FALSE : TRUE);
}

laboratory_t* dyn_queue_next(dyn_queue_t* queue)
{
	laboratory_t* reti = NULL;
	if (dyn_queue_has_next(queue) == TRUE)
	{
		reti = queue->data[queue->next];
		queue->next++;
	}
	return reti;
}

void dyn_queue_reset_next_index(dyn_queue_t* queue)
{
	queue->next = queue->head;
}

dyn_queue_t* dyn_queue_copy(dyn_queue_t* queue)
{
	dyn_queue_t* reti = (dyn_queue_t*)malloc(sizeof(dyn_queue_t));
	reti->capacity = queue->capacity;
	reti->count = queue->count;
	reti->head = queue->head;
	reti->next = queue->next;
	reti->tail = queue->tail;
	reti->data = (laboratory_t**)malloc(reti->capacity * sizeof(laboratory_t*));
	for (int i = reti->head; i < reti->tail; i++)
	{
		reti->data[i] = queue->data[i];
	}
	return reti;
}
