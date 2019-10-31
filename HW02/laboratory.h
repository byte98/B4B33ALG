#pragma once
#include "experiment.h"
#include "simple_bool.h"
#include "queue.h"
#include "dynamic_queue.h"
#include "laboratory_struct.h"



laboratory_t* laboratory_create(int days_available, int experiments_count, experiment_t** experiments);

laboratory_t* laboratory_copy(laboratory_t* laboratory);

void laboratory_quicksort_experiments_by_length_asc(laboratory_t* laboratory);

void laboratory_quicksort_experiments_by_length_asc_rec(laboratory_t* laboratory, int left_begin, int right_begin);

void laboratory_quicksort_experiments_by_length_desc(laboratory_t* laboratory);

experiment_t** laboratory_get_experiments(laboratory_t* laboratory);

int laboratory_get_experiments_count(laboratory_t* laboratory);

bool laboratory_schedule_experiment(laboratory_t* laboratory, experiment_t* experiment, int start_day);

bool laboratory_can_schedule_experiment(laboratory_t* laboratory, experiment_t* experiment, int start_day);

bool laboratory_is_not_scheduled_day(laboratory_t* laboratory, int day);

dyn_queue_t* laboratory_experiment_scheduler(laboratory_t* laboratory, experiment_t* experiment, int start_day);

void laboratory_recursive_scheduler(laboratory_t* laboratory, int last_used_day);

void laboratory_scheduler(laboratory_t* laboratory);