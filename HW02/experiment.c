#include "experiment.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

experiment_t* experiment_create(int id, int days, int income)
{
	experiment_t* reti = (experiment_t*)malloc(sizeof(experiment_t));
	reti->id = id;
	reti->days_count = days;
	reti->income = income;
	reti->days = (int*)calloc(reti->days_count, sizeof(int));
	return reti;
}

void experiment_set_active_day(experiment_t* experiment, int index, int day)
{
	if (index < experiment->days_count)
	{
		experiment->days[index] = day;
	}
}


int experiment_get_days_count(experiment_t* experiment)
{
	return experiment->days_count;
}
