///<summary>
/// File containing declaration of sorted data type
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
///Defines way, in which are data sorted
///</summary>
enum Sorted
{
	///<summary>
	///Data are not sorted
	///</summary>
	NONE,

	///<summary>
	///Data are sorted ascending
	///</summary>
	ASC,

	///<summary>
	///Data are sorted descending
	///</summary>
	DESC
};
///<summary>
///Definition of <c>enum</c> sorted as new data type
///</summary>
typedef enum Sorted sort_t;