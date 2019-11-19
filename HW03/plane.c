///<summary>
/// File containing implementation of plane functions
///</summary>
///<remarks>
/// Copyright 2019 Jiri Skoda <skodaji4@fel.cvut.cz>
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
/// http ://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissionsand
/// limitations under the License.
///</remarks>


#include "simple_bool.h"
#include "plane.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------------------------------------------------

plane_t* plane_create_empty()
{
	plane_t* reti = (plane_t*)malloc(sizeof(plane_t));
	if (reti != plane_NULL)
	{
		plane_LAST_ID++;
		reti->id = plane_LAST_ID;
		reti->weight = 0;
		reti->pl_has_pilot = FALSE;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

plane_t* plane_create(int weight)
{
	plane_t* reti = plane_create_empty();
	if (reti != plane_NULL)
	{
		reti->weight = weight;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void plane_delete(plane_t* plane)
{
#ifdef DEBUG
	printf("Deleted plane:: id: %d, weight: %d\n", plane_get_identifier(plane), plane_get_weight(plane));
#endif // DEBUG

	free(plane);
}

//-------------------------------------------------------------------------------------------------------------------------------

void plane_deleter(void* data)
{
	plane_delete((plane_t*)data);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool plane_check_same(plane_t* plane1, plane_t* plane2)
{
	bool reti = FALSE;
	if (
		plane_get_identifier(plane1) == plane_get_identifier(plane2) &&
		plane_get_weight(plane1) == plane_get_weight(plane2)
		)
	{
		reti = TRUE;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int plane_get_weight(plane_t* plane)
{
	int reti = -1;
	if (plane != plane_NULL)
	{
		reti = plane->weight;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int plane_get_identifier(plane_t* plane)
{
	int reti = -1;
	if (plane != plane_NULL)
	{
		reti = plane->id;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void plane_set_pilot(plane_t* plane, int weight)
{
	if (plane_get_has_pilot(plane) == FALSE)
	{
		plane->weight += weight;
		plane->pl_has_pilot = FALSE;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

bool plane_get_has_pilot(plane_t* plane)
{
	
	return (plane->pl_has_pilot == TRUE ? TRUE : FALSE);
}

//-------------------------------------------------------------------------------------------------------------------------------

void plane_unset_pilot(plane_t* plane, int weight)
{
	plane->weight = plane_get_weight(plane) - weight;
	plane->pl_has_pilot = FALSE;
}
