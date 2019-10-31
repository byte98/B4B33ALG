#pragma once

struct Experiment
{
	int id;
	int income;
	int days_count;
	int* days;
};

typedef struct Experiment experiment_t;

experiment_t* experiment_create(int id, int days, int income);

int experiment_get_days_count(experiment_t* experiment);

void experiment_set_active_day(experiment_t* experiment, int index, int day);

int experiment_sorter_by_length_asc(const void* element1, const void* element2);

int experiment_sorter_by_length_desc(const void* element1, const void* element2);

int experiment_sorter_by_income_asc(const void* element1, const void* element2);

int experiment_sorter_by_income_desc(const void* element1, const void* element2);