#include "hw04utils.h"
#include "globals.h"
#include <stdlib.h>
#include <math.h>
#include "ConsoleColor.h"
#include "config.h"
#include <stdio.h>

bool utils_point_on_map(point_t point)
{
	bool reti = FALSE;
#ifdef DEBUG/*
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("Checking point [");
	console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
	printf("%d", point.X);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(";");
	console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
	printf("%d", point.Y);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("] (");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", point.X);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(">=");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", 0);
	printf(":");
	if (point.X >= 0)
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("T");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("F");
	}
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(",");

	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", point.X);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("<");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", COLS);
	printf(":");
	if (point.X < COLS)
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("T");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("F");
	}
	printf(",");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", point.Y);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(">=");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", 0);
	printf(":");
	if (point.Y >= 0)
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("T");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("F");
	}
	printf(",");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", point.Y);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("<");
	console_color_set_foreground(console_color_get_from_ansi(YELLOW_BRIGHT));
	printf("%d", ROWS);
	printf(":");
	if (point.Y < ROWS)
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("T");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("F");
	}
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(") >> ");*/
#endif // DEBUG

	if
		(
			point.X >= 0 &&
			point.X < COLS &&
			point.Y >= 0 &&
			point.Y < ROWS
			)
	{
		reti = TRUE;
	}
#ifdef DEBUG/*
	if (reti == TRUE)
	{
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("TRUE");
	}
	else
	{
		console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
		printf("FALSE");
	}
	console_color_reset_colors();
	printf("\n");*/
#endif // DEBUG

	return reti;
}

bool utils_can_go_left(point_t point)
{
	return (utils_point_on_map((point_t) { .X = point.X - 1, .Y = point.Y }));
}

bool utils_can_go_right(point_t point)
{
	return (utils_point_on_map((point_t) { .X = point.X + 1, .Y = point.Y }));
}

bool utils_can_go_up(point_t point)
{
	return (utils_point_on_map((point_t) { .X = point.X, .Y = point.Y - 1 }));
}

bool utils_can_go_down(point_t point)
{
	return (utils_point_on_map((point_t) { .X = point.X, .Y = point.Y + 1 }));
}

int utils_compute_motor_ionization(int E_initial, point_t start, point_t finish)
{
	int reti = E_initial;
	if (MAP[start.Y][start.X] < MAP[finish.Y][finish.X])
	{
		reti += D_mov;
	}
	else if (MAP[start.Y][start.X] == MAP[finish.Y][finish.X])
	{
		reti = reti + 0;
	}
	else if (MAP[start.Y][start.X] > MAP[finish.Y][finish.X] && E_initial >= D_mov)
	{
		reti -= D_mov;
	}
	else if (MAP[start.Y][start.X] > MAP[finish.Y][finish.X] && E_initial < D_mov)
	{
		reti = 0;
	}
	return reti;
}

int utils_compute_environment_ionization(int E_eng, point_t start, point_t finish)
{
	int reti = E_eng;
	if (E_eng >= (D_env + MAP[finish.Y][finish.X]))
	{
		reti -= D_env;
	}
	else if ((D_env + MAP[finish.Y][finish.X]) > E_eng&& E_eng > MAP[finish.Y][finish.X])
	{
		reti = MAP[finish.Y][finish.X];
	}
	else if (E_eng <= MAP[finish.Y][finish.X])
	{
		reti = reti + 0;
	}
	return reti;
}

int utils_compute_ionization(int E_motor, point_t start, point_t finish)
{
	int reti = utils_compute_motor_ionization(E_motor, start, finish);
	reti = utils_compute_environment_ionization(reti, start, finish);
	return reti;
}

point_t* utils_create_point(int X, int Y)
{
	point_t* reti = (point_t*)malloc(sizeof(point_t));
#ifdef DEBUG
	if (reti == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for new POINT FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
	reti->X = X;
	reti->Y = Y;
	return reti;
}

situation_t* utils_create_situation(point_t* point, int energy, int steps)
{
	situation_t* reti = (situation_t*)malloc(sizeof(situation_t));
#ifdef DEBUG
	if (reti == NULL)
	{
		console_color_set_background(console_color_get_from_ansi(RED));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Allocating space for new SITUATION FAILED!\n");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
	}
#endif // DEBUG
	reti->energy = energy;
	reti->steps = steps;
	reti->point = point;
#ifdef DEBUG
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf("Creating situation:: point: ");
	console_color_set_foreground(console_color_get_from_ansi(CYAN_BRIGHT));
	printf("[%d; %d]", reti->point->X, reti->point->Y);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(", energy: ");
	console_color_set_foreground(console_color_get_from_ansi(MAGENTA_BRIGHT));
	printf("%d", energy);
	console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
	printf(", steps: ");
	console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
	printf("%d", steps);
	console_color_reset_colors();
	printf("\n");
#endif // DEBUG

	return reti;
}

void utils_check_position(situation_t* situation)
{
	//if (utils_point_on_map(*situation->point) == TRUE)
	//{
#ifdef DEBUG
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf("Checking position [");
		console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
		printf("%d", situation->point->X);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf(";");
		console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
		printf("%d", situation->point->Y);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf("] Queue size: ");
		console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
		printf("%d", queue_count(SITUATIONS));
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf(", Energy: ");
		console_color_set_foreground(console_color_get_from_ansi(MAGENTA_BRIGHT));
		printf("%d", situation->energy);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf(", Steps: ");
		console_color_set_foreground(console_color_get_from_ansi(CYAN));
		printf("%d", situation->steps);
		console_color_reset_colors();
		printf("\n");
#endif // DEBUG
		if (situation->point->Y == FINISH->Y && situation->point->X == FINISH->X)
		{
#ifdef DEBUG
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			console_color_set_background(console_color_get_from_ansi(GREEN));
			printf("Drone reached destination.");
			console_color_reset_colors();
			console_color_set_background(console_color_get_from_ansi(BLACK));
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("[");
			console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
			printf("%d", situation->point->X);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf(";");
			console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
			printf("%d", situation->point->Y);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("]\n");
			console_color_reset_colors();
#endif // DEBUG

			if (situation->steps < MIN_STEPS)
			{
				MIN_STEPS = situation->steps;
#ifdef DEBUG
				console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
				printf("Distance to destination: ");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->steps);
				console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
				printf(" steps");
				console_color_reset_colors();
				printf("\n");

#endif // DEBUG

				return;
			}
		}
		else if (situation->steps >= MIN_STEPS)
		{
			console_color_set_background(console_color_get_from_ansi(YELLOW));
			console_color_set_foreground(console_color_get_from_ansi(BLACK));
			printf("Drone reached maximal steps without destination.");
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			console_color_set_background(console_color_get_from_ansi(BLACK));
			printf("[");
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("%d", situation->point->X);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf(";");
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("%d", situation->point->Y);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("]\n");
			console_color_reset_colors();
			return;
		}
		else if (situation->energy <= 0)
		{
#ifdef DEBUG
			console_color_set_background(console_color_get_from_ansi(YELLOW_BRIGHT));
			console_color_set_foreground(console_color_get_from_ansi(BLACK));
			printf("Drone out of energy.");
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			console_color_set_background(console_color_get_from_ansi(BLACK));
			printf("[");
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("%d", situation->point->X);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf(";");
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("%d", situation->point->Y);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("]\n");
			console_color_reset_colors();
#endif // DEBUG

			return;
		}
		if (VISITED[situation->point->Y][situation->point->X] == NULL)
		{
#ifdef DEBUG
#ifdef DEBUG
			console_color_set_background(console_color_get_from_ansi(CYAN));
			console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
			printf("Drone reached UNKNOWN position.");
			console_color_reset_colors();
			console_color_set_background(console_color_get_from_ansi(BLACK));
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("[");
			console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
			printf("%d", situation->point->X);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf(";");
			console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
			printf("%d", situation->point->Y);
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			printf("]\n");
			console_color_reset_colors();
#endif // DEBUG
#endif // DEBUG
			VISITED[situation->point->Y][situation->point->X] = situation;
		}
		else if (VISITED[situation->point->Y][situation->point->X]->energy > situation->energy)
		{
#ifdef DEBUG
				console_color_set_background(console_color_get_from_ansi(BLUE));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Drone reached known position with ");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("lower");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf(" energy.");
				console_color_reset_colors();
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("[");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("]");
				printf("(before: ");
				console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
				printf("%d", VISITED[situation->point->Y][situation->point->X]->energy);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(")");
				console_color_reset_colors();
				printf("\n");
#endif // DEBUG
				return;
		}
		else if (VISITED[situation->point->Y][situation->point->X]->energy < situation->energy)
		{
#ifdef DEBUG
		console_color_set_background(console_color_get_from_ansi(BLUE));
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf("Drone reached known position with ");
		console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
		printf("higher");
		console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
		printf(" energy.");
		console_color_reset_colors();
		console_color_set_background(console_color_get_from_ansi(BLACK));
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf("[");
		console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
		printf("%d", situation->point->X);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf(";");
		console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
		printf("%d", situation->point->Y);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf("]");
		printf("(before: ");
		console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
		printf("%d", VISITED[situation->point->Y][situation->point->X]->energy);
		console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
		printf(")");
		console_color_reset_colors();
		printf("\n");
#endif // DEBUG
		VISITED[situation->point->Y][situation->point->X] = situation;
		}
		else if (VISITED[situation->point->Y][situation->point->X]->energy == situation->energy)
		{
			if (VISITED[situation->point->Y][situation->point->X]->steps > situation->steps)
			{
#ifdef DEBUG
				console_color_set_background(console_color_get_from_ansi(BLUE));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Drone reached known position with same energy and ");
				console_color_set_foreground(console_color_get_from_ansi(GREEN_BRIGHT));
				printf("less");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf(" steps.");
				console_color_reset_colors();
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("[");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("]");
				printf("(before: ");
				console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
				printf("%d", VISITED[situation->point->Y][situation->point->X]->steps);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(")");
				console_color_reset_colors();
				printf("\n");
#endif // DEBUG
				VISITED[situation->point->Y][situation->point->X] = situation;
			}
			else
			{
#ifdef DEBUG
				console_color_set_background(console_color_get_from_ansi(BLUE));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Drone reached known position with same energy and ");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("more or same");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf(" steps.");
				console_color_reset_colors();
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("[");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_rgb(255, 255, 255));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf("]");
				printf("(before: ");
				console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
				printf("%d", VISITED[situation->point->Y][situation->point->X]->steps);
				console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
				printf(")");
				console_color_reset_colors();
				printf("\n");
#endif // DEBUG
				return;
			}
		}

		if (utils_can_go_down(*situation->point) == TRUE)
		{
			point_t* next_point = utils_create_point(situation->point->X , situation->point->Y+1);
			int next_energy = utils_compute_ionization(situation->energy, *situation->point, *next_point);
			situation_t* next_situation = utils_create_situation(next_point, next_energy, situation->steps + 1);
#ifdef DEBUG
			if (next_situation == NULL)
			{
				console_color_set_background(console_color_get_from_ansi(RED));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Allocating space for NEXT SITUATION FAILED!");
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("( going ");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("down");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(" from [");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("]");
				console_color_reset_colors();
				printf("\n");
			}
#endif // DEBUG
			queue_push(SITUATIONS, next_situation);
		}
		if (utils_can_go_right(*situation->point) == TRUE)
		{
			point_t* next_point = utils_create_point(situation->point->X + 1, situation->point->Y);
			int next_energy = utils_compute_ionization(situation->energy, *situation->point, *next_point);
			situation_t* next_situation = utils_create_situation(next_point, next_energy, situation->steps + 1);
#ifdef DEBUG
			if (next_situation == NULL)
			{
				console_color_set_background(console_color_get_from_ansi(RED));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Allocating space for NEXT SITUATION FAILED!");
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("( going ");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("right");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(" from [");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("]");
				console_color_reset_colors();
				printf("\n");
			}
#endif // DEBUG
			queue_push(SITUATIONS, next_situation);
		}
		if (utils_can_go_up(*situation->point) == TRUE)
		{
			point_t* next_point = utils_create_point(situation->point->X, situation->point->Y - 1);
			int next_energy = utils_compute_ionization(situation->energy, *situation->point, *next_point);
			situation_t* next_situation = utils_create_situation(next_point, next_energy, situation->steps + 1);
#ifdef DEBUG
			if (next_situation == NULL)
			{
				console_color_set_background(console_color_get_from_ansi(RED));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Allocating space for NEXT SITUATION FAILED!");
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("( going ");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("up");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(" from [");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("]");
				console_color_reset_colors();
				printf("\n");
			}
#endif // DEBUG
			queue_push(SITUATIONS, next_situation);
		}

		if (utils_can_go_left(*situation->point) == TRUE)
		{
			point_t* next_point = utils_create_point(situation->point->X - 1, situation->point->Y);
			int next_energy = utils_compute_ionization(situation->energy, *situation->point, *next_point);
			situation_t* next_situation = utils_create_situation(next_point, next_energy, situation->steps + 1);

#ifdef DEBUG
			if (next_situation == NULL)
			{
				console_color_set_background(console_color_get_from_ansi(RED));
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("Allocating space for NEXT SITUATION FAILED!");
				console_color_set_background(console_color_get_from_ansi(BLACK));
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("( going ");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("left");
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(" from [");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->X);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf(";");
				console_color_set_foreground(console_color_get_from_ansi(WHITE_BRIGHT));
				printf("%d", situation->point->Y);
				console_color_set_foreground(console_color_get_from_ansi(RED_BRIGHT));
				printf("]");
				console_color_reset_colors();
				printf("\n");
			}
#endif // DEBUG
			queue_push(SITUATIONS, next_situation);
		}
	//}
}

int utils_situation_step_comparator(void* situationA, void* situationB)
{
	situation_t* sA = (situation_t*)situationA;
	situation_t* sB = (situation_t*)situationB;
	int reti = -1;
	if (
		sA->point->X == sB->point->X &&
		sA->point->Y == sB->point->Y &&
		sA->steps == sB->steps
		)
	{
		reti = 0;
	}
	else
	{
		reti = sA->steps - sB->steps;
	}
	return reti;
}

int utils_situation_energy_comparator(void* situationA, void* situationB)
{
	situation_t* sA = (situation_t*)situationA;
	situation_t* sB = (situation_t*)situationB;
#ifdef DEBUG

#endif // DEBUG

	int reti = -1;
	if (
		sA->point->X == sB->point->X &&
		sA->point->Y == sB->point->Y &&
		sA->energy == sB->energy
		)
	{
		reti = 0;
	}
	else
	{
		reti = sA->energy - sB->energy;
	}
	return reti;
}

int utils_situation_exact_comparator(void* situationA, void* situationB)
{
	situation_t* sA = (situation_t*)situationA;
	situation_t* sB = (situation_t*)situationB;
	int reti = -1;
	if (
		sA->point->X == sB->point->X &&
		sA->point->Y == sB->point->Y &&
		sA->energy == sB->energy &&
		sA->steps == sB->steps
		)
	{
		reti = 0;
	}
	else
	{
		point_t vector = {
			.X = sA->point->X - sB->point->X,
			.Y = sA->point->X - sB->point->X,
		};
		reti = sqrt(pow(vector.X, 2) + pow(vector.Y, 2));
	}
	return reti;
}

#ifdef SHOW_MAP
void utils_display_map(point_t* point)
{
	printf("\033[H");
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			console_color_set_foreground(console_color_get_from_ansi(BLACK_BRIGHT));
			console_color_t color = console_color_get_from_ansi(BLACK_BRIGHT);
			if (r == 0 && c == 0)
			{
				color = console_color_get_from_ansi(GREEN);
			}
			else if (r == FINISH->Y && c == FINISH->X)
			{
				color = console_color_get_from_ansi(RED);
			}
			else if (point->X == 0 && point->Y == 0)
			{
				//color = console_color_get_from_ansi(GREEN_BRIGHT);
			}
			else if (point->X == FINISH->X && point->Y == FINISH->Y)
			{
				//color = console_color_get_from_ansi(RED_BRIGHT);
			}
			else if (point->X == c && point->Y == r)
			{
				color = console_color_get_from_ansi(YELLOW_BRIGHT);
			}
			else if (
				(point->X - 1 == c && point->Y == r)||
				(point->X + 1 == c && point->Y == r)||
				(point->Y - 1 == r && point->X == c)||
				(point->Y + 1 == r && point->X == c)
				)
			{
				color = console_color_get_from_ansi(WHITE_BRIGHT);
			}
			console_color_set_foreground(color);
			printf(" %2d ", MAP[r][c]);
			console_color_reset_colors();
		}
		printf("\n");
	}
	printf("\n");
	console_color_set_foreground(console_color_get_from_ansi(WHITE));
	printf("Actual steps: ");
	console_color_set_foreground(console_color_get_from_ansi(BLUE_BRIGHT));
	printf("%d", STEPS);
	console_color_reset_colors();
	printf("\n");
	usleep(SHOW_DELAY);
}
#endif // SHOW_MAP


