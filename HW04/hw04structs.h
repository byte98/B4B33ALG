#ifndef __HW04_STRUCTS_H__
#define __HW04_STRUCTS_H__
struct Point
{
	int X;
	int Y;
};
typedef struct Point point_t;

struct Situation
{
	point_t* point;
	int energy;
	int steps;
};
typedef struct Situation situation_t;
#endif // !__HW04_STRUCTS_H__