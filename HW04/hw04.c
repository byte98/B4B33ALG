
#include <stdlib.h>
#include <stdio.h>
#include "ConsoleColor.h"
#include "config.h"
#include "queue.h"
#include "globals.h"
#include "hw04utils.h"
#include <limits.h>

int ROWS, COLS, E_init, D_mov, D_env;
int** MAP;
situation_t*** VISITED;
int MIN_STEPS;
queue_t* SITUATIONS;
point_t* FINISH;
#ifdef SHOW_MAP
int STEPS;
#endif // SHOW_MAP


int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	//Load first row with data
	scanf("%d %d %d %d %d", &ROWS, &COLS, &E_init, &D_mov, &D_env);
#ifdef DEBUG
	printf("[%d x %d]\n", ROWS, COLS);
#endif // DEBUG

	MAP = (int**)malloc(ROWS * sizeof(int*));
	VISITED = (situation_t***)malloc(ROWS * sizeof(situation_t**));
#ifdef DEBUG
	if (VISITED == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for VISITED FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
#ifdef DEBUG
	if (MAP == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for MAP FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
	SITUATIONS = queue_create();
	MIN_STEPS = INT_MAX;
	FINISH = utils_create_point(COLS - 1, ROWS - 1);
#ifdef DEBUG
	if (FINISH == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for FINISH FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
	console_color_set_background(console_color_get_from_ansi(WHITE_BRIGHT));
	console_color_set_foreground(console_color_get_from_ansi(BLACK));
	printf("Drone goal: go to [");
	console_color_set_foreground(console_color_get_from_ansi(GREEN));
	printf("%d", FINISH->X);
	console_color_set_foreground(console_color_get_from_ansi(BLACK));
	printf("; ");
	console_color_set_foreground(console_color_get_from_ansi(GREEN));
	printf("%d", FINISH->Y);
	console_color_set_foreground(console_color_get_from_ansi(BLACK));
	printf("]");
	console_color_set_background(console_color_get_from_ansi(BLACK));
	console_color_reset_colors();
	printf("\n");
#endif // DEBUG
	for (int r = 0; r < ROWS; r++)
	{
		MAP[r] = (int*)malloc(COLS * sizeof(int));
		VISITED[r] = (situation_t**)malloc(COLS * sizeof(situation_t**));
#ifdef DEBUG
		if (VISITED[r] == NULL)
		{
			console_color_set_background(console_color_get_from_ansi(RED));
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("Allocating space for row %d FAILED!\n", r);
			console_color_reset_colors();
			console_color_set_background(console_color_get_from_ansi(BLACK));
		}
#endif // DEBUG
#ifdef DEBUG
		if (MAP[r] == NULL)
		{
			console_color_set_background(console_color_get_from_ansi(RED));
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("Allocating space for MAP[%d] FAILED!\n", r);
			console_color_reset_colors();
			console_color_set_background(console_color_get_from_ansi(BLACK));
		}
#endif // DEBUG

		for (int c = 0; c < COLS; c++)
		{
			scanf("%d", &MAP[r][c]);
#ifdef DEBUG
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("%2d ", MAP[r][c]);
			console_color_reset_colors();
#endif // DEBUG

		}
#ifdef DEBUG
		printf("\n");
#endif // DEBUG

	}


	//BFS

	situation_t* actual = utils_create_situation(utils_create_point(0, 0), E_init, 0);
	utils_check_position(actual);
#ifdef SHOW_MAP
	printf("\033[2J");
	utils_display_map(actual->point);
#endif // SHOW_MAP

	while (queue_is_empty(SITUATIONS) == FALSE && MIN_STEPS == INT_MAX)
	{
#ifdef DEBUG
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf("Popping new item...size before pop: ");
		console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
		printf("%d", queue_count(SITUATIONS));
		console_color_reset_colors();
		printf("\n");
#endif // DEBUG

		situation_t* s = queue_pop(SITUATIONS);
		utils_check_position(s);
#ifdef SHOW_MAP
		STEPS = s->steps;
		utils_display_map(s->point);
#endif // SHOW_MAP
		
	}

	printf("%d\n", MIN_STEPS);
	return reti;
}