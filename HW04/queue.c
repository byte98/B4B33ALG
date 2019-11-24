#include "queue.h"
#include "config.h"
#include "ConsoleColor.h"
#include <stdlib.h>
#include <stdio.h>
queue_t* queue_create()
{
	queue_t* reti = malloc(sizeof(queue_t));
	if (reti != NULL)
	{
		reti->count = 0;
		reti->head = NULL;
		reti->tail = NULL;
	}
#ifdef DEBUG
	if (reti == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for QUEUE FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
	return reti;
}

void queue_push(queue_t* queue, void* data)
{
	queue_node_t* node = (queue_node_t*)malloc(sizeof(queue_node_t));
#ifdef DEBUG
	if (node == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for NODE FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
	node->data = data;
	node->next = NULL;
	node->id = queue_node_identifier;
	queue_node_identifier++;
	if (queue->head == NULL)
	{
		queue->head = node;
	}
	if (queue->tail == NULL)
	{
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->count++;
#ifdef DEBUG
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("Queue info:: head: ");
	if (queue->head == NULL)
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("NULL");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(MAGENTA_BRIGHT));
		printf("%d", queue->head->id);
	}
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("; tail:");
	if (queue->tail == NULL)
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("NULL");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(MAGENTA_BRIGHT));
		printf("%d", queue->tail->id);
	}
	console_color_reset_colors();
	printf("\n");
#endif // DEBUG

#ifdef DEBUG
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("Pushed data ");
	if (data == NULL)
	{
		console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
		printf("NULL");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN));
		printf("NOT NULL");
	}
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(" into queue[");
	console_color_set_foreground(console_color_get_from_ansi(CYAN_BRIGHT));
	printf("%d", node->id);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("]; size: ");
	console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
	printf("%d", queue_count(queue));
	console_color_reset_colors();
	printf("\n");
#endif // DEBUG

}

void* queue_pop(queue_t* queue)
{
	void* reti = NULL;
#ifdef DEBUG
	int id = -1;
#endif // DEBUG

	if (queue->head != NULL)
	{
		reti = queue->head->data;
#ifdef DEBUG
		id = queue->head->id;
#endif // DEBUG
		queue->head = queue->head->next;
	}
	queue->count--;
#ifdef DEBUG
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("Popped ");
	if (reti == NULL)
	{
		console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
		printf("NULL");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN));
		printf("NOT NULL");
	}
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(" data from queue[");
	console_color_set_foreground(console_color_get_from_ansi(CYAN_BRIGHT));
	printf("%d", id);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("]; size: ");
	console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
	printf("%d", queue_count(queue));
	console_color_reset_colors();
	printf("\n");
#endif // DEBUG

	return reti;
}

int queue_count(queue_t* queue)
{
	return queue->count;
}

bool queue_is_empty(queue_t* queue)
{
	return (queue->count <= 0 ? TRUE : FALSE);
}