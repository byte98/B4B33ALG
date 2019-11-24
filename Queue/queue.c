#include "queue.h"
#include <stdlib.h>

queue_t* queue_create()
{
	queue_t* reti = malloc(sizeof(queue_t));
	if (reti != NULL)
	{
		reti->count = 0;
		reti->length = 2;
		reti->head = 0;
		reti->tail = 0;
		reti->next_head = 0;
		reti->data = (void**)malloc(reti->length * sizeof(void*));
	}
	return reti;
}

bool queue_push(queue_t* queue, void* data)
{
	if (queue->count + 1 <= queue->length)
	{
		queue_upscale(queue);
	}
	queue->data[queue->tail] = data;
	queue->tail++;
	queue->count++;
	return TRUE;
}

void* queue_pop(queue_t* queue)
{
	void* reti = NULL;
	if (queue_is_empty(queue) == FALSE)
	{
		reti = queue->data[queue->head];
		queue->head++;
		queue->count--;
		queue_shrink(queue);
	}
	return reti;
}

bool queue_is_empty(queue_t* queue)
{
	return (queue->count == 0 ? TRUE : FALSE);
}

bool queue_is_full(queue_t* queue)
{
	return (queue->count == queue->length ? TRUE : FALSE);
}

void queue_upscale(queue_t* queue)
{
	queue->length = queue->length * 2;
	queue->data = realloc(queue->data, queue->length);
}

void queue_shrink(queue_t* queue)
{
	if (queue->count == ((queue->length / 3) * 2))
	{
		void** new_data = malloc(((queue->length / 3) * 2) * sizeof(void*));
		int idx = 0;
		for (int i = queue->head; i < queue->tail; i++)
		{
			new_data[idx] = queue->data[i];
		}
		free(queue->data);
		queue->data = new_data;
		int diff = queue->head;
		queue->head = 0;
		queue->tail = idx;
		queue->length = ((queue->length / 3) * 2);
		queue->next_head = queue->next_head - diff;
	}
}

int queue_count(queue_t* queue)
{
	return queue->count;
}
void* queue_at(queue_t* queue, int index)
{
	void* reti = NULL;
	if (queue_index_in_queue(index, queue))
	{
		reti = queue->data[index];
	}
	return reti;
}

bool queue_is_not_empty(queue_t* queue)
{
	return (queue->count > 0 ? TRUE : FALSE);
}

void* queue_next(queue_t* queue)
{
	void* reti = NULL;
	if (queue->next_head < queue->tail)
	{
		reti = queue_at(queue, queue->next_head);
		queue->next_head++;
	}
	return reti;
}

bool queue_next_not_empty(queue_t* queue)
{
	bool reti = FALSE;
	if (queue->next_head + 1 < queue->tail)
	{
		reti = TRUE;
	}
	return reti;
}

void queue_reset_next_index(queue_t* queue)
{
	queue->next_head = queue->head;
}

queue_t* queue_reverse_data(queue_t* queue)
{
	queue_t* reti = queue_create();
	for (int i = (queue->tail - 1); i >= queue->head; i--)
	{
		queue_push(reti, queue_at(queue, i));
	}
	return reti;
}

void queue_delete(queue_t* queue)
{
	free(queue->data);
	free(queue);
}

bool queue_contains(queue_t* queue, void* element, sort_t sort, int(*comparator(void*, void*)))
{
	bool reti = FALSE;
	if (sort == NONE)
	{
		for (int i = queue->head; i <= queue->tail; i++)
		{
			if (comparator(queue_at(queue, i), element) == 0)
			{
				reti = TRUE;
				break;
			}
		}
	}
	else
	{
		reti = queue_binary_search(queue, element, sort, comparator);
	}
	return reti;
}

bool queue_binary_search(queue_t* queue, void* element, sort_t sort, int(*comparator(void*, void*)))
{
	return queue_binary_search_recursive(queue, element, sort, queue->head, queue->tail, comparator);
}

bool queue_binary_search_recursive(queue_t* queue, void* element, sort_t sort, int start_index, int end_index, int(*comparator(void*, void*)))
{
	int index = queue_binary_search_next_index(start_index, end_index, queue);
	void* found = queue_at(queue, index);


	if (comparator(found, element) == 0)
	{

		return TRUE;
	}
	else if ((start_index == index && queue_index_in_queue(start_index, queue)) || (end_index == index && queue_index_in_queue(end_index, queue)))
	{
		if ((comparator(queue_at(queue, start_index), element) == 0 && queue_index_in_queue(start_index, queue) == TRUE) || (comparator(queue_at(queue, end_index), element) == 0 && queue_index_in_queue(end_index, queue) == TRUE))
		{

			return TRUE;
		}
		else
		{

			return FALSE;
		}
	}
	else if (index != -1)
	{
		if (sort == ASC)
		{
			if (comparator(found, element) > 0)
			{
				return queue_binary_search_recursive(queue, element, sort, start_index, index, comparator);
			}
			else if (comparator(found, element) < 0)
			{
				return queue_binary_search_recursive(queue, element, sort, index, end_index, comparator);
			}
		}
		else if (sort == DESC)
		{
			if ( comparator(found, element) > 0)
			{
				return queue_binary_search_recursive(queue, element, sort, index, end_index, comparator);
			}
			else if (comparator(found, element) < 0)
			{
				return queue_binary_search_recursive(queue, element, sort, start_index, index, comparator);
			}
		}
		else
		{
			if ((comparator(queue_at(queue, start_index), element) == 0 && queue_index_in_queue(start_index, queue) == TRUE) || (comparator(queue_at(queue, end_index), element) == 0 && queue_index_in_queue(end_index, queue) == TRUE))
			{

				return TRUE;
			}
		}
	}
	else if (index == -1)
	{
		if ((comparator(queue_at(queue, start_index), element) == 0 && queue_index_in_queue(start_index, queue) == TRUE) || (comparator(queue_at(queue, end_index), element) == 0 && queue_index_in_queue(end_index, queue)))
		{

			return TRUE;
		}
	}

	return FALSE;
}

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

bool queue_index_in_queue(int index, queue_t* queue)
{
	bool reti = FALSE;
	if (index >= queue->head && index < queue->tail)
	{
		reti = TRUE;
	}
	return reti;
}