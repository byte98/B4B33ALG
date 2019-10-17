///<summary>
/// File containig definitions of all necessary structures and definitions
///  used in first homework for subject B4B33ALG - Algorithms
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
///Define <c>TRUE</c> as some non-zero value (here 1)
///</summary>
#define TRUE 1

///<summary>
///Define <c>FALSE</c> as zero value
///</summary>
#define FALSE 0



/* === STRUCTURES DEFINITIONS === */

///<summary>
/// Structure containing information about sticky note
///</summary>
struct StickyNote
{
	///<summary>
	/// Width of sticky note
	///</summary>
	int width;

	///<summary>
	/// Height of sticky note
	///</summary>
	int height;

	///<summary>
	/// Distance of left side of sticky note from left side of area
	/// available for sticky notes
	///</summary>
	int distance_from_left;
};


///<summary>
/// Structures which holds final results of program
///</summary>
struct Result
{
	///<summary>
	/// Number of sticky notes visible from outside
	///</summary>
	int visible_out;

	///<summary>
	/// Number of sticky notes visible from inside
	///</summary>
	int visible_in;

	///<summary>
	/// Number of sticky notes visible from both outside and inside
	///</summary>
	int visible_both;

	///<summary>
	/// Number of sticky notes which are not visible at all
	///</summary>
	int unvisible;
};


///<summary>
///Structure whcich holds actual state of sticky note area
///</summary>
struct Model
{
	///<summary>
	///Describes situation from outside
	///</summary>
	int* situation_out;

	///<summary>
	///Describes situation from inside
	///</summary>
	int* situation_in;
};



/* === DATA TYPES DEFINITIONS === */
///<summary>
///Simple definition of something like a "boolean"
///</summary>
typedef char bool;



///<summary>
/// Defines structure <c>StickyNote</c> as new data type
///<seealso cref="StickyNote"/>
///</summary>
typedef struct StickyNote sticky_note_t;

///<summary>
///Defines structure <c>Result</c> as new data type
///<seealso cref="Result"/>
///</summary>
typedef struct Result result_t;

///<summary>
///Defines structure <c>Model</c> as new data type
///<seealso cref="Model"/>
///</summary>
typedef struct Model model_t;