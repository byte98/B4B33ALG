#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "simple_bool.h"

volatile static int queue_node_identifier = 0;
struct QueueNode
{
	void* data;
	struct QueueNode* next;
	int id;
};
typedef struct QueueNode queue_node_t;

struct Queue
{
	int count;
	queue_node_t* head;
	queue_node_t* tail;
};
typedef struct Queue queue_t;

queue_t* queue_create();
void queue_push(queue_t* queue, void* data);
void* queue_pop(queue_t* queue);
int queue_count(queue_t* queue);
bool queue_is_empty(queue_t* queue);

#endif // !__QUEUE_H__
