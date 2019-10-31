#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "utils.h"
#include "experiment.h"
#include "laboratory.h"

static volatile int COUNT = 0;
static volatile int DAYS = 0;

int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	//Read basic attributes of quest
	scanf("%d %d", &COUNT, &DAYS);
#ifdef DEBUG
	printf("Loaded:: count: %d, days: %d\n", COUNT, DAYS);
#endif // DEBUG

	//Read all experiments
	experiment_t** experiments = malloc(COUNT * sizeof(experiment_t*));
	for (int i = 0; i < COUNT; i++)
	{
		int days, income = 0;
		scanf("%d %d", &days, &income);
		experiment_t* experiment = experiment_create(i, days, income);
		for (int j = 0; j < experiment_get_days_count(experiment); j++)
		{
			int active_day = 0;
			scanf("%d", &active_day);
			experiment_set_active_day(experiment, j, active_day);
		}
		experiments[i] = experiment;
#ifdef DEBUG
		printf("Loaded experiment::[%d] income:%d, days:%d (", experiments[i]->id, experiments[i]->income, experiments[i]->days_count);
		util_print_int_array(experiments[i]->days, experiments[i]->days_count);
		printf(")\n");
#endif // DEBUG
	}

	//Creates laboratory
	laboratory_t* default_lab = laboratory_create(DAYS, COUNT, experiments);

	//Sort experiments in laboratory
	laboratory_quicksort_experiments_by_length_desc(default_lab);
#ifdef DEBUG
	printf("Sorted experiments:\n");
	experiment_t** exs = laboratory_get_experiments(default_lab);
	int exs_count = laboratory_get_experiments_count(default_lab);
	for (int i = 0; i < exs_count; i++)
	{
		printf("[%d]:: id:%d, income: %d, days: %d (", i, exs[i]->id, exs[i]->income, exs[i]->days_count);
		util_print_int_array(exs[i]->days, exs[i]->days_count);
		printf(")\n");
	}
#endif // DEBUG

	//Make state tree
	//laboratory_recursive_scheduler(laboratory_copy(default_lab), -1);
	laboratory_scheduler(default_lab);
	

	return reti;
}