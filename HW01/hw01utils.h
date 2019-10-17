///<summary>
/// File containing declarations of utility functions
/// used in first homework for subject B4B33ALG - Algorithms
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

#include "structures.h"

///<summary>
/// Function to check changes from outside after adding new sticky note
///</summary>
///<param name="model">Model describing actual situation of problem</param>
///<param name="note">Sticky note which will be added</param>
///<param name="result">Structure with results of solving actual problem</param>
void check_outside_situation(model_t* model, sticky_note_t* note, result_t* result);

///<summary>
/// Function to check changes from inside after adding new sticky note
///</summary>
///<param name="model">Model describing actual situation of problem</param>
///<param name="note">Sticky note which will be added</param>
///<param name="result">Structure with results of solving actual problem</param>
void check_inside_situation(model_t* model, sticky_note_t* note, result_t* result);

///<summary>
///Prints information about results
///</summary>
///<param name="result">Result which data will be printed</param>
void print_result(result_t* result);
