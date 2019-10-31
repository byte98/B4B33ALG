#pragma once

#include "simple_bool.h"
#include "laboratory_struct.h"

#define DYN_QUEUE_UPSCALE 2

struct Dynamic_Queue
{
	int count;
	int capacity;
	laboratory_t** data;
	int head;
	int tail;
	int next;
};
typedef struct Dynamic_Queue dyn_queue_t;

dyn_queue_t* dyn_queue_create();

bool dyn_queue_push(dyn_queue_t* queue, laboratory_t* item);

laboratory_t* dyn_queue_pop(dyn_queue_t* queue);

bool dyn_queue_is_empty(dyn_queue_t* queue);

bool dyn_queue_upscale(dyn_queue_t* queue);

void dyn_queue_delete(dyn_queue_t* queue);

bool dyn_queue_has_next(dyn_queue_t* queue);

laboratory_t* dyn_queue_next(dyn_queue_t* queue);

void dyn_queue_reset_next_index(dyn_queue_t* queue);

dyn_queue_t* dyn_queue_copy(dyn_queue_t* queue);