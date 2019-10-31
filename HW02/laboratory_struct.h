#pragma once
#include "queue.h"
#include "experiment.h"
struct Laboratory
{
	int days_available;
	int* days_used;
	int experiments_available_count;
	experiment_t** experiments_available;
	queue_t* experiment_unused;

	int days_claimed;
	int total_income;
};
typedef struct Laboratory laboratory_t; 
