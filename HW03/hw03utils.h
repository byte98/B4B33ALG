///<summary>
/// File containing decalrations of utility functions used in third homework from algorithms
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
#ifndef __HW03_UTILS_H__
#define __HW03_UTILS_H__
#include "node.h"
#include "plane.h"

///<summary>
///Structure with array of planes
///</summary>
struct Plane_Array
{
	///<summary>
	///Count of planes stored in array
	///</summary>
	int count;

	///<summary>
	///Array with planes
	///</summary>
	plane_t** data;
};
///<summary>
///Type definition of structure with array of planes
///</summary>
typedef struct Plane_Array plane_array_t;

///<summary>
///Stores some information as return from function
///</summary>
volatile static _RETI = 0;

///<summary>
///Structure with array of nodes
///</summary>
struct Node_Array
{
	///<summary>
	///Count of nodes stored in array
	///</summary>
	int count;

	///<summary>
	///Array with nodes
	///</summary>
	node_t** data;
};
///<summary>
///Type definition of structure with array of planes
///</summary>
typedef struct Node_Array node_array_t;

///<summary>
///Function to compute difference between weights of subtrees
///</summary>
///<param name="node">Node of tree which will be accpeted as root of tree</param>
///<returns>Difference between weights of trees</returns>
int utils_compute_difference(node_t* node);

///<summary>
///Function to compute weight of left subtree
///</summary>
///<param name="node">Node of tree which left subtree weight will be computed</param>
int utils_compute_left_weight(node_t* node);

///<summary>
///Function to compute weight of right subtree
///</summary>
///<param name="node">Node of tree which right subtree weight will be computed </param>
int utils_compute_right_weight(node_t* node);

///<summary>
///Function to compute weight of subtree
///</summary>
///<param name="node">Root of subtree which weight will be computed</param>
///<returns>Weight of subtree</returns>
int utils_compute_subtree_weight(node_t* node);

///<summary>
///Function to create subtrees with lowes possible difference of weights
///</summary>
///<param name="array">Array with nodes</param>
///<param name="count">Count of nodes in array</param>
///<returns>
///Array of nodes which are roots of subtrees
///and in static variable _RETI count of elements
///</returns>
node_t** utils_create_lowest_plane_subtrees(node_t** array, int count);

///<summary>
///Function to create array of planes
///</summary>
///<param name="count">Count of planes</param>
///<returns>Array of planes or <c>NULL</c></returns>
plane_array_t* utils_create_plane_array(int count);

///<summary>
///Function to delete array of planes
///</summary>
///<param name="plane_arr">Array of planes which will be deleted</param>
void utils_delete_plane_array(plane_array_t* plane_arr);

///<summary>
///Evaluator used in this homework
///</summary>
///<param name="node">Node which will be evaluated</param>
///<returns>Weight of tree</returns>
int utils_node_evaluator(node_t* node);

node_t* utils_create_tree(plane_t** planes, int start, int end);

int utils_get_ideal_delimiter(plane_t** planes, int start, int end);

int utils_sum_planes(plane_t** planes, int start, int end);

void utils_int_deleter(void* int_ptr);

void utils_print_tree(node_t* node);

int utils_count_whole_difference(node_t* node);

int utils_place_pilot(node_t* root, int weight);

int utils_try_place_pilot(node_t* node, int weight);

void utils_update_tree_differences(node_t* leafe);

void utils_update_node(node_t* node);

int utils_default_evaluator(node_t* node);

void utils_set_evaluator(node_t* node);

#endif // !__HW03_UTILS_H__
