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
#include <limits.h>

#include "node.h"
#include "plane.h"
#include "hw03utils.h"
#include "config.h"

///<summary>
/// Stores count of planes stored in tree
///</summary>
volatile static int COUNT = 0;

///<summary>
///Stores wight of one pilot figurine
///</summary>
volatile static int WEIGHT = 0;

///<summary>
///Entry function of program
///</summary>
///<param name="argc">Count of arguments</param>
///<param name="argv">Arguments of program</param>
///<returns>0 if finished successfully, something different otherwise</returns>
int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	scanf("%i %i", &COUNT, &WEIGHT);
#ifdef DEBUG
	printf("Loaded data:: count: %d, weight of pilot: %d\n", COUNT, WEIGHT);
#endif // DEBUG
	
	plane_t** planes = (plane_t**)malloc(COUNT * sizeof(plane_t*));

	

	for (int i = 0; i < COUNT; i++)
	{
		int weight = -1;
		scanf("%i", &weight);
		planes[i] = plane_create(weight);
#ifdef DEBUG
		printf("Loaded plane:: id: %d, weight: %d\n", plane_get_identifier(planes[i]), plane_get_weight(planes[i]));
#endif // DEBUG			
	}

	//Create tree from planes
	node_t* root = utils_create_tree(planes, 0, (COUNT - 1));

#ifdef DEBUG
	utils_print_tree(root);
	printf("Leaves: %d\n", node_count_leaves(root));
#endif // DEBUG

	int result = utils_count_whole_difference(root);
#ifdef DEBUG
	printf("Sum of differences in tree: %d\n", result);
#endif // DEBUG


	for (int i = 0; i < PILOTS; i++)
	{
		utils_place_pilot(root, WEIGHT);
	}

#ifdef DEBUG
	utils_set_evaluator(root);
	node_print_tree_nodes_evaluation(root);
#endif // DEBUG


	int result_pilot = utils_count_whole_difference(root);


	for (int i = 0; i < COUNT; i++)
	{
		plane_delete(planes[i]);
	}
	
	printf("%d %d\n", result, result_pilot);

	return reti;
}