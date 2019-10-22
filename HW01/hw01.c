#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "structures.h"
#include "hw01utils.h"
#include "queue.h"
#include "simple_bool.h"


static volatile int WIDTH = 0;
static volatile int COUNT = 0;

int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;
	result_t result = { 0, 0, 0, 0, 0 };

	int* situation_out;

#ifdef SAFE_MODE
	char line[INPUT_BUFFER_SIZE];
	fgets(line, INPUT_BUFFER_SIZE, stdin);
	if (sscanf(line, "%d %d", &WIDTH, &COUNT) != 2)
	{
		reti = EXIT_FAILURE;
		fprintf(stderr, "ERROR [%d]: Parsing of first line failed!\n Expected: width<int> count<int>\n Get: %s", __LINE__, line);
	}
#endif // SAFE_MODE
#ifndef SAFE_MODE
	scanf("%d %d", &WIDTH, &COUNT);
#endif // !SAFE_MODE
#ifdef DEBUG
	printf("Loaded values:: maximal width: %d, count: %d\n", WIDTH, COUNT);
#endif // DEBUG

#ifdef SAFE_MODE
	if (reti == EXIT_SUCCESS)
	{
#endif // SAFE_MODE
		model_t situation;
		situation.width = WIDTH;
		situation_out = (int*)calloc(WIDTH, sizeof(int));
		situation.situation_out = situation_out;
#ifdef SAFE_MODE
		if (situation.situation_out == NULL)
		{
			reti = EXIT_FAILURE;
			fprintf(stderr, "ERROR [%d]: Allocation memory for 'situation_out <int[%d]>' failed!", __LINE__, WIDTH);
		}
#endif // SAFE_MODE
		int* situation_in = (int*)calloc(WIDTH, sizeof(int));
		situation.situation_in = situation_in;
#ifdef SAFE_MODE
		if (situation.situation_in == NULL)
		{
			reti = EXIT_FAILURE;
			fprintf(stderr, "ERROR [%d]: Allocation memory for 'situation_in <int[%d]>' failed!", __LINE__, WIDTH);
		}
		if (reti == EXIT_SUCCESS)
		{
#endif // SAFE_MODE
			situation.notes_in = queue_create_static(COUNT);
			situation.notes_out = queue_create_static(COUNT);
			sticky_note_t* notes = (sticky_note_t*)malloc(COUNT * sizeof(sticky_note_t));
#ifdef SAFE_MODE
			if (situation.notes_in == NULL)
			{
				reti = EXIT_FAILURE;
				fprintf(stderr, "ERROR [%d]: Allocation for 'notes_in <queue_t>' failed!", __LINE__);
			}
			else if (situation.notes_out == NULL)
			{
				reti = EXIT_FAILURE;
				fprintf(stderr, "ERROR [%d]: Allocation for 'notes_out <queue_t>' failed!", __LINE__);
			}
			else if (notes == NULL)
			{
				reti = EXIT_FAILURE;
				fprintf(stderr, "ERROR [%d]: Allocation memory for 'notes <sticky_note_t[%d]>' failed!", __LINE__, COUNT);
			}
			if (reti == EXIT_SUCCESS)
			{
#endif // SAFE_MODE
				//All memory spaces has been sucessfully allocated
				//Now its time for parse notes data from standart input
				for (int i = 0; i < COUNT; i++)
				{
					sticky_note_t sticky_note;
#ifdef SAFE_MODE
					char data[INPUT_BUFFER_SIZE];
					fgets(data, INPUT_BUFFER_SIZE, stdin);
					if (sscanf(data, "%d %d %d",
						&sticky_note.distance_from_left,
						&sticky_note.height,
						&sticky_note.width) != 3)
					{
						reti = EXIT_FAILURE;
						fprintf(stderr, "ERROR [%d]: Parsing line (%d) with sticky note data failed!\n Expected: distance_from_left<int> height<int> width<int>\n Get: %s\n", __LINE__, (i + 1), data);
						break;
					}
					if (sticky_note.width > WIDTH)
					{
						reti = EXIT_FAILURE;
						fprintf(stderr, "ERROR [%d]: Wrong input (%d)!\n Maximal allowed width: %d\n Get: %d\n", __LINE__, (i + 1), WIDTH, sticky_note.width);
						break;
					}
#endif // SAFE_MODE
#ifndef SAFE_MODE
					scanf("%d %d %d",
						&sticky_note.distance_from_left,
						&sticky_note.height,
						&sticky_note.width);
#endif // !SAFE_MODE
#ifdef DEBUG
					printf("Loaded sticky note[%d]:: distance from left: %d, width: %d, height: %d\n", (i + 1), sticky_note.distance_from_left, sticky_note.width, sticky_note.height);
#endif // DEBUG
					sticky_note.id = i;
					if (reti == EXIT_SUCCESS)
					{
						notes[i] = sticky_note;
						check_outside_situation(&situation, &sticky_note, &result);
					}
				}

				for (int i = (COUNT - 1); i >= 0; i--)
				{
					check_inside_situation(&situation, &notes[i], &result);
				}

				result.visible_both = check_visible_both(&situation);
				result.visible_one = queue_count(situation.notes_in) + queue_count(situation.notes_out) - result.visible_both;
				result.unvisible = COUNT - result.visible_both - result.visible_one;

#ifdef SAFE_MODE
			}
#endif // SAFE_MODE
#ifdef SAFE_MODE
		}
#endif // SAFE_MODE
#ifdef SAFE_MODE
	}
#endif // SAFE_MODE

#ifdef SAFE_MODE
	if (reti == EXIT_SUCCESS)
	{
#endif // SAFE_MODE
		print_result(&result);
#ifdef SAFE_MODE
	}
#endif // SAFE_MODE
	return reti;

}