#ifndef __HW04_UTILS_H__
#define __HW04_UTILS_H__


#include "simple_bool.h"
#include "hw04structs.h"



bool utils_point_on_map(point_t);

bool utils_can_go_left(point_t point);
bool utils_can_go_right(point_t point);
bool utils_can_go_up(point_t point);
bool utils_can_go_down(point_t point);

int utils_compute_motor_ionization(int E_initial, point_t start, point_t finish);
int utils_compute_environment_ionization(int E_eng, point_t start, point_t finish);
int utils_compute_ionization(int E_motor, point_t start, point_t finish);

point_t* utils_create_point(int X, int Y);
situation_t* utils_create_situation(point_t* point, int energy, int steps);

void utils_check_position(situation_t* situation);

int utils_situation_step_comparator(void* situationA, void* situationB);

int utils_situation_energy_comparator(void* situationA, void* situationB);

int utils_situation_exact_comparator(void* situationA, void* situationB);

#ifdef SHOW_MAP
void utils_display_map(point_t* point);
#endif
#endif // !__HW04_UTILS_H__