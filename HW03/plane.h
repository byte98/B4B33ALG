///<summary>
/// File containing declaration of planes used in third homework
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
#pragma once
///<summary>
/// Definition of plane in third homework
///</summary>
struct Plane
{
	///<summary>
	///Unique identifier identifiing plane in system
	///</summary>
	int id;

	///<summary>
	///Weight of plane
	///</summary>
	int weight;
};

///<summary>
/// Type definition of plane used in third homework
///</summary>
typedef struct Plane plane_t;

///<summary>
///Stores last used identifier of plane
///</summary>
static volatile int PLANE_LAST_ID = -1;

///<summary>
///Defines <c>NULL</c> plane
///</summary>
#define plane_NULL ((plane_t*)NULL)

///<summary>
///Creates empty plane
///</summary>
///<returns>New empty plane or <c>NULL</c> if allocating space for plane failed</returns>
plane_t* plane_create_empty();

///<summary>
///Creates plane with defined weight
///</summary>
///<param name="weight">Weight of plane</param>
///<returns>New plane with defined weitgh or <c>NULL</c> if allocating space for plane failed
plane_t* plane_create(int weight);

///<summary>
///Deletes plane and all data used by plane
///</summary>
///<param name="plane">Plane, which will be deleted</param>
void plane_delete(plane_t* plane);

///<summary>
///Checks, whether planes are same
///</summary>
///<param name="plane1">First plane to be compared</param>
///<param name="plane2">Second plane to be compared</param>
///<returns><c>TRUE</c> if they are same, <c>FALSE</c> otherwise</returns>
bool plane_check_same(plane_t* plane1, plane_t* plane2);





