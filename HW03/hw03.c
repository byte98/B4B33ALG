///<summary>
/// File containing main program of third homework
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

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void print_int(void* data)
{
	int d = *(int*)data;
	printf("%d", d);
}

void delete_int(void* data)
{
	int d = *(int*)data;
	printf("%d deleted\n", d);
}

///<summary>
///Entry function of program
///</summary>
///<param name="argc">Count of arguments</param>
///<param name="argv">Arguments of program</param>
///<returns>0 if finished successfully, something different otherwise
int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;
	int data = 3;
	int* d = &data;
	node_t* n = node_create(d, delete_int);

	int data2 = 13;
	int* d2 = &data2;
	node_t* n2 = node_create(d2, delete_int);

	int data3 = 103;
	int* d3 = &data3;
	node_t* n3 = node_create(d3, delete_int);

	int data4 = 203;
	int* d4 = &data4;
	node_t* n4 = node_create(d4, delete_int);

	node_set_parent(n2, n, LEFT);
	node_set_left_child(n2, n3);
	node_set_right_child(n2, n4);

	node_print(n2, print_int);


	return reti;
}