///<summary>
/// File containing declaration of node in tree
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
#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>
#include "simple_bool.h"

///<summary>
///Definiton of structure node in tree
///</summary>
struct Node
{
	///<summary>
	///Unique identifier of node
	///</summary>
	int id;

	///<summary>
	///Left child of node
	///</summary>
	struct Node* left_child;

	///<summary>
	///Right child of node
	///</summary>
	struct Node* right_child;

	///<summary>
	///Parent of node int tree
	///</summary>
	struct Node* parent;

	///<summary>
	///Data stored in node
	///</summary>
	void* data;

	///<summary>
	///Function which can delete data from node
	///</summary>
	void (*delete)(void*);

	///<summary>
	///Function which can get integer from node
	///</summary>
	int (*evaluator)(struct Node*);
};

///<summary>
///Type definition of node in tree
///</summary>
typedef struct Node node_t;

///<summary>
///Enumeration defining position of child
///</summary>
enum Node_Child
{
	///<summary>
	///Defines left child
	///</summary>
	LEFT,

	///<summary>
	///Defines right child
	///</summary>
	RIGHT,

	///<summary>
	///Defines any child
	///</summary>
	ANY
};

///<summary>
///Type definition of enumeration defining position of child
///</summary>
typedef enum Node_Child node_child_t;

///<summary>
///Stores last used identifier of node
///</summary>
static volatile int node_LAST_ID = -1;

///<summary>
///Defines <c>NULL</c> node
///</summary>
#define node_NULL ((node_t*)NULL)

///<summary>
///Creates empty node
///</summary>
///<returns>Empty node or <c>NULL</c> if allocation of memory failed</returns>
node_t* node_create_empty();

///<summary>
///Creates node with data
///</summary>
///<param name="data">Data which will be stored in node</param>
///<param name="delete">Function which can delete data stored in node</param>
///<returns>New node with data or <c>NULL</c> if allocation of memory failed</returns>
node_t* node_create(void* data, void(*delete)(void*));

///<summary>
///Deletes node and data stored in node
///</summary>
///<param name="node">Node which will be deleted</param>
void node_delete(node_t* node);

///<summary>
///Default function used to delete data
///</summary>
///<param name="data">Data which will be deleted</param>
void node_delete_empty_data(void* data);

///<summary>
///Checks, whether node is empty
///</summary>
///<returns><c>TRUE</c> if node is empty, <c>FALSE</c> otherwise</returns>
bool node_is_empty(node_t* node);

///<summary>
///Sets parential node of node
///</summary>
///<param name="node">Node, which parent will be set</param>
///<param name="parent">Parential node</param>
///<param name="child">Sets, which child of parent will be this node</param>
///<returns><c>TRUE</c> if setting was successfull, <c>FALSE</c> otherwise</returns>
bool node_set_parent(node_t* node, node_t* parent, node_child_t child);

///<summary>
///Sets parential node of node with overwriting current one
///</summary>
///<param name="node">Node, which parent will be set</param>
///<param name="parent">Parential node</param>
///<param name="child">Sets, which child of parent will be this node</param>
void node_set_parent_F(node_t* node, node_t* parent, node_child_t child);

///<summary>
///Gets parent node of node
///</summary>
///<param name="node">Node which parent will be get</param>
///<returns>Pointer to parential node</returns>
node_t* node_get_parent(node_t* node);

///<summary>
///Sets child of node
///</summary>
///<param name="node">Node, which child will be set</param>
///<param name="child">Node, which will be set as child</param>
///<param name="position">Position of child</param>
///<returns><c>TRUE</c> if child has been successfully set, <c>FALSE</c> otherwise</returns>
bool node_set_child(node_t* node, node_t* child, node_child_t position);

///<summary>
///Gets child of node
///</summary>
///<param name="node">Node, which child will be set</param>
///<param name="child">Node, which will be set as child</param>
///<param name="position">Position of child</param>
///<returns>Selected child of node or <c>NULL</c> </returns>
node_t* node_get_child(node_t* node, node_child_t position);

///<summary>
///Sets left child of node
///</summary>
///<param name="node">Node, which left child will be set</param>
///<param name="left_child">Node which will be set as left child</param>
///<returns><c>TRUE</c> if child has been successfully set, <c>FALSE</c> otherwise</returns>
bool node_set_left_child(node_t* node, node_t* left_child);

///<summary>
///Sets left child of node with overwriting current child
///</summary>
///<param name="node">Node, which left child will be set</param>
///<param name="left_child">Node which will be set as left child</param>
void node_set_left_child_F(node_t* node, node_t* left_child);

///<summary>
///Gets left child of node
///</summary>
///<param name="node">Node, wchich left child will be get</param>
///<returns>Pointer to left child of node</returns>
node_t* node_get_left_child(node_t* node);

///<summary>
///Sets right child of node
///</summary>
///<param name="node">Node, which right child will be set</param>
///<param name="right_child">Node which will be set as right child</param>
///<returns><c>TRUE</c> if child has been successfully set, <c>FALSE</c> otherwise</returns>
bool node_set_right_child(node_t* node, node_t* right_child);

///<summary>
///Sets right child of node with overwriting current child
///</summary>
///<param name="node">Node, which right child will be set</param>
///<param name="right_child">Node which will be set as right child</param>
void node_set_right_child_F(node_t* node, node_t* right_child);

///<summary>
///Gets right child of node
///</summary>
///<param name="node">Node, which right child will be get</param>
///<returns>Pointer to right child of node</returns>
node_t* node_get_right_child(node_t* node);

///<summary>
///Gets unique identifier of node
///</summary>
///<param name="node">Node which identifier will be returned</param>
///<returns>Identifier of node or -1 for null node</returns>
int node_get_identifier(node_t* node);

///<summary>
///Gets data stored in node
///</summary>
///<param name="node">Node, which data will be returned</param>
///<returns>Data stored in node or <c>NULL</c></returns>
void* node_get_data(node_t* node);

///<summary>
///Sets data stored in node
///</summary>
///<param name="node">Node, which data will be returned</param>
///<param name="data">Data which will be stored in node</param>
///<param name="delete">Function, which can delete data</param>
///<returns><c>TRUE</c> if setting of data has been successfull, <c>FALSE</c> otherwise</returns>
bool node_set_data(node_t* node, void* data, void(*delete)(void*));

///<summary>
///Sets data stored in node
///</summary>
///<param name="node">Node, which data will be returned</param>
///<param name="data">Data which will be stored in node</param>
///<param name="delete">Function, which can delete data</param>
void node_set_data_force(node_t* node, void* data, void(*delete)(void*));

///<summary>
///Checks, whether nodes are same
///</summary>
///<param name="node1">First node to be compared</param>
///<param name="node2">Second node to be compared</param>
///<returns><c>TRUE</c> if they are same, <c>FALSE</c> otherwise</returns>
bool node_check_same(node_t* node1, node_t* node2);

///<summary>
///Checks, whether nodes and its subtrees are same
///</summary>
///<param name="node1">First node to be compared</param>
///<param name="node2">Second node to be compared</param>
///<returns><c>TRUE</c> if they and its subtrees are same, <c>FALSE</c> otherwise</returns>
bool node_deep_check_same(node_t* node1, node_t* node2);

///<summary>
///Checks, whether node is null node
///</summary>
///<param name="node">Node which will be checked</param>
///<returns><c>TRUE</c> if node is null, <c>FALSE</c> otherwise</returns>
bool node_check_null(node_t* node);

///<summary>
///Checks, whether node has left child
///</summary>
///<param name="node">Node which will be checked</param>
///<returns><c>TRUE</c> if node has left child, <c>FALSE</c> otherwise</returns>
bool node_has_left_child(node_t* node);

///<summary>
///Checks, whether node has right child
///</summary>
///<param name="node">Node which will be checked</param>
///<returns><c>TRUE</c> if node has right child, <c>FALSE</c> otherwise</returns>
bool node_has_right_child(node_t* node);

///<summary>
///Checks, whether node has child
///</summary>
///<param name="node">Node which will be checked</param>
///<returns><c>TRUE</c> if node has child, <c>FALSE</c> otherwise</returns>
bool node_has_child(node_t* node);

///<summary>
///Checks, whether node has parent
///</summary>
///<param name="node"> Node, which will be checked</param>
///<returns><c>TRUE</c> if node has parent, <c>FALSE</c> otherwise</returns>
bool node_has_parent(node_t* node);

///<summary>
///Checks, whether node is leaf of tree
///</summary>
///<param name="node">Node which will be checked</param>
///<returns><c>TRUE</c> if node is leaf of tree, <c>FALSE</c> otherwise</returns>
bool node_is_leaf(node_t* node);

///<summary>
///Sets function which can return integer from node
///</summary>
///<param name="node">Node which function will be defined</param>
///<param name="evaluator">Function which can get integer from node</param>
void node_set_evaluator(node_t* node, int(*evaluate)(node_t*));

///<summary>
///Default node evaluator
///</summary>
///<param name="node">Node which will be evaluated</param>
///<returns>Identifier of node</returns>
int node_default_evaluator(node_t* node);

///<summary>
///Gets integer from node
///</summary>
///<param name="node">Node which integer will be computed</param>
///<returns>Integer computed from node</returns>
int node_evaluate(node_t* node);

///<summary>
///Deletes tree defined by node
///</summary>
///<param name="node">Node which is root of tree which will be deleted</param>
void node_delete_tree(node_t* node);

///<summary>
///Counts leaves in tree
///</summary>
///<param name="node">Node which is root of tree which leavs will be counted</param>
///<returns>Count of leaves</returns>
int node_count_leaves(node_t* node);

///<summary>
///Gets leaves from tree
///</summary>
///<param name="node">Node which is root of tree which leaves will be returned</param>
///<param name="result">Array, where will be stored results</param>
void node_get_leaves(node_t* node, node_t** result);

///<summary>
///Recursive function to find leaves in tree
///!!!THIS FUNCTION SHOULDN'T BE CALLED ALONE!!!
///</summary>
///<param name="node">Node which is root of tree which leaves will be found</param>
///<param name="result">Array, where will be stored results</param>
void node_find_leaves(node_t* node, node_t** result);


#ifdef DEBUG
///<summary>
///Prints information about node
///</summary>
///<param name="node">Node which information will be printed</param>
///<param name="print">Function which can print data</param>
void node_print(node_t* node, void(*print)(void*));

///<summary>
///Prints nodes with its evaluation
///</summary>
///<param name="node">Node which evaluation will be printed</param>
void node_print_tree_nodes_evaluation(node_t* node);
#endif // DEBUG
#endif // ! __NODE_H__