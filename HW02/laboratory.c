#include "laboratory.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "utils.h"

#define LAB_FREE -1

laboratory_t* laboratory_create(int days_available, int experiments_count, experiment_t** experiments)
{
	laboratory_t* reti = (laboratory_t*)malloc(sizeof(laboratory_t));
	reti->days_available = days_available;
	reti->days_used = (int*)malloc(reti->days_available * sizeof(int));
	for (int i = 0; i < reti->days_available; i++)
	{
		reti->days_used[i] = LAB_FREE;
	}
	reti->experiments_available = experiments;
	reti->experiments_available_count = experiments_count;
	reti->experiment_unused = queue_create_static(reti->experiments_available_count);
	reti->total_income = 0;
	reti->days_claimed = 0;
	for (int i = 0; i < reti->experiments_available_count; i++)
	{
		queue_push(reti->experiment_unused, experiments[i]);
	}

	return reti;
}

laboratory_t* laboratory_copy(laboratory_t* laboratory)
{
	laboratory_t* reti = (laboratory_t*)malloc(sizeof(laboratory_t));
	reti->days_available = laboratory->days_available;
	reti->days_used = (int*)malloc(reti->days_available * sizeof(int));
	for (int i = 0; i < reti->days_available; i++)
	{
		reti->days_used[i] = laboratory->days_used[i];
	}
	reti->experiments_available_count = laboratory->experiments_available_count;
	reti->experiments_available = laboratory->experiments_available;
	reti->total_income = laboratory->total_income;
	reti->days_claimed = laboratory->days_claimed;
	reti->experiment_unused = queue_create_static(queue_count(laboratory->experiment_unused));
	while (queue_next_not_empty(laboratory->experiment_unused) == TRUE)
	{
		queue_push(reti->experiment_unused, queue_next(laboratory->experiment_unused));
	}
	queue_reset_next_index(laboratory->experiment_unused);
	return reti;
}

void laboratory_quicksort_experiments_by_length_asc(laboratory_t* laboratory)
{
	laboratory_quicksort_experiments_by_length_asc_rec(laboratory, 0, laboratory->experiments_available_count - 1);
	queue_delete(laboratory->experiment_unused);
	laboratory->experiment_unused = queue_create_static(laboratory->experiments_available_count);
	for (int i = 0; i < laboratory->experiments_available_count; i++)
	{
		queue_push(laboratory->experiment_unused, laboratory->experiments_available[i]);
	}
#ifdef DEBUG
	printf("   queue count:%d\n", queue_count(laboratory->experiment_unused));
#endif // DEBUG

}

//Source: https://cs.wikipedia.org/wiki/Quicksort
void laboratory_quicksort_experiments_by_length_asc_rec(laboratory_t* laboratory, int left_begin, int right_begin)
{
		experiment_t* pivot = laboratory->experiments_available[(left_begin + right_begin) / 2];
		int left_index, right_index;
		experiment_t* pom;
		left_index = left_begin;
		right_index = right_begin;
		do
		{
			while (laboratory->experiments_available[left_index]->days_count < pivot->days_count && left_index < right_begin)
				left_index++;
			while (laboratory->experiments_available[right_index]->days_count > pivot->days_count&& right_index > left_begin)
				right_index--;

			if (left_index <= right_index)
			{
				pom = laboratory->experiments_available[left_index];
				laboratory->experiments_available[left_index++] = laboratory->experiments_available[right_index];
				laboratory->experiments_available[right_index--] = pom;
			}
		}
		while (left_index < right_index);

		if (right_index > left_begin) laboratory_quicksort_experiments_by_length_asc_rec(laboratory, left_begin, right_index);
		if (left_index < right_begin) laboratory_quicksort_experiments_by_length_asc_rec(laboratory, left_index, right_begin);
}

void laboratory_quicksort_experiments_by_length_desc(laboratory_t* laboratory)
{
	laboratory_quicksort_experiments_by_length_asc(laboratory);
	experiment_t** new_experiments = (experiment_t**)malloc(laboratory->experiments_available_count * sizeof(experiment_t*));
	for (int i = 0; i < laboratory->experiments_available_count; i++)
	{
		new_experiments[laboratory->experiments_available_count - 1 - i] = laboratory->experiments_available[i];
	}
	free(laboratory->experiments_available);
	laboratory->experiments_available = new_experiments;
	queue_t* new_unused = queue_reverse_data(laboratory->experiment_unused);
	free(laboratory->experiment_unused);
	laboratory->experiment_unused = new_unused;
}




experiment_t** laboratory_get_experiments(laboratory_t* laboratory)
{
	return laboratory->experiments_available;
}

int laboratory_get_experiments_count(laboratory_t* laboratory)
{
	return laboratory->experiments_available_count;
}

bool laboratory_schedule_experiment(laboratory_t* laboratory, experiment_t* experiment, int start_day)
{
	bool reti = FALSE;

	if (laboratory_can_schedule_experiment(laboratory, experiment, start_day) == TRUE)
	{
		reti = TRUE;
		for (int i = 0; i < experiment->days_count; i++)
		{
			laboratory->days_used[experiment->days[i] + start_day] = experiment->id;
		}
		laboratory->total_income += experiment->income;
		laboratory->days_claimed += experiment->days_count;
	}

	return reti;
}

bool laboratory_can_schedule_experiment(laboratory_t* laboratory, experiment_t* experiment, int start_day)
{
	bool reti = TRUE;
	for (int i = 0; i < experiment->days_count; i++)
	{
		if (start_day + experiment->days[i] > laboratory->days_available || laboratory_is_not_scheduled_day(laboratory, start_day + experiment->days[i]) == FALSE)
		{
			reti = FALSE;
			break;
		}
	}

	return reti;
}

bool laboratory_is_not_scheduled_day(laboratory_t* laboratory, int day)
{
	return (laboratory->days_used[day] == LAB_FREE ? TRUE : FALSE);
}



laboratory_t* laboratory_recursive_experiment_scheduler(laboratory_t* laboratory, experiment_t* experiment, int last_used_day)
{
	last_used_day++;
	if (last_used_day == laboratory->days_available)
	{
		return laboratory_copy(laboratory);
	}
	for (int i = last_used_day; i < laboratory->days_available; i++)
	{
		if (laboratory_can_schedule_experiment(laboratory, experiment, i))
		{
			printf("day: %d, start at: %d\n", last_used_day, i);
		}		
		laboratory_recursive_scheduler(laboratory, last_used_day);
	}

#ifdef DEBUG
			//printf("Availablde schedule:: income: %d, experiments: ", laboratory->total_income);
			//util_print_int_array(laboratory->days_used, laboratory->days_available);
			//printf("\n");
#endif // DEBUG


}

void laboratory_recursive_scheduler(laboratory_t* laboratory, int last_used_day)
{
	laboratory_recursive_experiment_scheduler(laboratory, laboratory->experiments_available[0], last_used_day);
}

dyn_queue_t* laboratory_experiment_scheduler(laboratory_t* laboratory, experiment_t* experiment, int start_day)
{
	dyn_queue_t* reti = dyn_queue_create();
	dyn_queue_push(reti, laboratory_copy(laboratory));
	for (int i = start_day; i < laboratory->days_available; i++)
	{
		if (laboratory_can_schedule_experiment(laboratory, experiment, i) == TRUE)
		{
			laboratory_t* new_lab = laboratory_copy(laboratory);
			laboratory_schedule_experiment(new_lab, experiment, i);
#ifdef DEBUG
			printf("start experiment: %d, at: %d ($%d)\n", experiment->id, i, experiment->income);
			printf("$$$%d\n", new_lab->total_income);
#endif // DEBUG
			dyn_queue_push(reti, new_lab);

		}
	}
	return reti;
}

void laboratory_scheduler(laboratory_t* laboratory)
{
	dyn_queue_t* all_states = dyn_queue_create();
	dyn_queue_push(all_states, laboratory);
	while (queue_is_empty(laboratory->experiment_unused) == FALSE)
	{
		experiment_t* exp = queue_pop(laboratory->experiment_unused);
		dyn_queue_t* tmp_states = dyn_queue_copy(all_states);
		while (dyn_queue_is_empty(tmp_states) == FALSE)
		{
			dyn_queue_t* exp_scheduled = laboratory_experiment_scheduler(dyn_queue_pop(tmp_states), exp, 0);
			while (dyn_queue_is_empty(exp_scheduled) == FALSE)
			{
				dyn_queue_push(all_states, dyn_queue_pop(exp_scheduled));
			}
			dyn_queue_delete(exp_scheduled);
		}
		dyn_queue_delete(tmp_states);
		
	}
#ifdef DEBUG
	printf("=== RESULTS (%d) ===\n", all_states->count);

	while (dyn_queue_is_empty(all_states) == FALSE)
	{
		laboratory_t* lab = dyn_queue_pop(all_states);
		printf("$%d, ", lab->total_income);
		util_print_int_array(lab->days_used, lab->days_available);
		printf("\n");
	}
	dyn_queue_delete(all_states);
#endif // DEBUG



}
