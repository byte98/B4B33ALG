///<summary>
/// File containing implementation of node functions
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

#include <stdlib.h>
#include <stdio.h>

#include "node.h"


//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_create_empty()
{
	node_t* reti = (node_t*)malloc(sizeof(node_t));
	if (reti != node_NULL)
	{
		reti->data = NULL;
		reti->delete = node_delete_empty_data;
		node_LAST_ID++;
		reti->id = node_LAST_ID;
		reti->left_child = node_NULL;
		reti->right_child = node_NULL;
		reti->parent = node_NULL;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_create(void* data, void(*delete)(void*))
{
	node_t* reti = (node_t*)malloc(sizeof(node_t));
	if (reti != NULL)
	{
		reti->data = data;
		reti->delete = delete;
		node_LAST_ID++;
		reti->id = node_LAST_ID;
		reti->left_child = node_NULL;
		reti->parent = node_NULL;
		reti->right_child = node_NULL;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void node_delete(node_t* node)
{
	node->delete(node->data);
	free(node);
}

//-------------------------------------------------------------------------------------------------------------------------------

void node_delete_empty_data(void* data)
{
	//pass
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_is_empty(node_t* node)
{
	bool reti = FALSE;
	if (
		node_check_null(node) == TRUE ||
		(
			node->data == NULL &&
			node_check_null(node_get_left_child(node)) == TRUE &&
			node_check_null(node_get_right_child(node)) == TRUE
			)
		)
	{
		reti = TRUE;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_set_parent(node_t* node, node_t* parent, node_child_t child)
{
	bool reti = FALSE;
	bool set = FALSE;
	if (child == LEFT || child == ANY)
	{
		if (node_check_null(node_get_left_child(parent)) == TRUE)
		{
			node->parent = parent;
			node_set_left_child(node_get_parent(node), node);
			set = TRUE;
			reti = TRUE;
		}
	}
	if (child == RIGHT || (child == ANY && set == FALSE))
	{
		if (node_check_null(node_get_right_child(parent)) == TRUE)
		{
			node->parent = parent;
			node_set_right_child(node_get_parent(node), node);
			reti = TRUE;
			set = TRUE;
		}
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_get_parent(node_t* node)
{
	return node->parent;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_set_child(node_t* node, node_t* child, node_child_t position)
{
	bool reti = FALSE;
	if (position == LEFT)
	{
		reti = node_set_left_child(node, child);
	}
	else if (position == RIGHT)
	{
		reti = node_set_right_child(node, child);
	}
	else if (position == ANY)
	{
		int rnd = rand() % 2;
		node_child_t first_position = (rnd == 0 ? LEFT : RIGHT);
		node_child_t second_position = (first_position == LEFT ? RIGHT : LEFT);
		reti = node_set_child(node, child, first_position);
		if (reti == FALSE)
		{
			reti = node_set_child(node, child, second_position);
		}
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_get_child(node_t* node, node_child_t position)
{
	node_t* reti = node_NULL;
	if (position == LEFT)
	{
		reti = node_get_left_child(node);
	}
	else if (position == RIGHT)
	{
		reti = node_get_right_child(node);
	}
	else if (position == ANY)
	{
		int rnd = rand() % 2;
		node_child_t first_position = (rnd == 0 ? LEFT : RIGHT);
		node_child_t second_position = (first_position == LEFT ? RIGHT : LEFT);
		reti = node_get_child(node, first_position);
		if (node_check_null(reti) == TRUE)
		{
			reti = node_get_child(node, second_position);
		}
	}

	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_set_left_child(node_t* node, node_t* left_child)
{
	bool reti = FALSE;
	if (node_check_null(node_get_left_child(node)) == TRUE)
	{
		reti = TRUE;
		node->left_child = left_child;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_get_left_child(node_t* node)
{
	return node->left_child;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_set_right_child(node_t* node, node_t* right_child)
{
	bool reti = FALSE;
	if (node_check_null(node_get_right_child(node)) == TRUE)
	{
		reti = TRUE;
		node->right_child = right_child;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* node_get_right_child(node_t* node)
{
	return node->right_child;
}

//-------------------------------------------------------------------------------------------------------------------------------

int node_get_identifier(node_t* node)
{
	int reti = -1;
	if (node_check_null(node) == FALSE)
	{
		reti = node->id;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void* node_get_data(node_t* node)
{
	return node->data;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_set_data(node_t* node, void* data, void(*delete)(void*))
{
	bool reti = FALSE;
	if (node->data == NULL)
	{
		node->data = data;
		node->delete = delete;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_check_same(node_t* node1, node_t* node2)
{
	return (node_get_identifier(node1) == node_get_identifier(node2) ? TRUE : FALSE);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_deep_check_same(node_t* node1, node_t* node2)
{
	bool reti = FALSE;
	if
	(
		(node_check_null(node1) == TRUE && node_check_null(node2) == TRUE)||
		(
			node_check_null(node1) == FALSE &&
			node_check_null(node2) == FALSE &&
			node_get_identifier(node1) == node_get_identifier(node2) &&
			node_deep_check_same(node_get_left_child(node1), node_get_left_child(node2)) == TRUE &&
			node_deep_check_same(node_get_right_child(node1), node_get_right_child(node2)) == TRUE &&
			node_get_data(node1) == node_get_data(node2)
		)
	)
	{
		reti = TRUE;
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_check_null(node_t* node)
{
	return (node == node_NULL ? TRUE : FALSE);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_has_left_child(node_t* node)
{
	return (node_check_null(node_get_left_child(node)) == TRUE ? FALSE : TRUE);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_has_right_child(node_t* node)
{
	return (node_check_null(node_get_right_child(node)) == TRUE ? FALSE : TRUE);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_has_child(node_t* node)
{
	return (node_has_left_child(node) == TRUE ? TRUE : node_has_right_child(node) ? TRUE : FALSE);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool node_has_parent(node_t* node)
{
	return (node_check_null(node_get_parent(node)) == TRUE ? FALSE : TRUE);
}

//-------------------------------------------------------------------------------------------------------------------------------

#ifdef DEBUG
void node_print(node_t* node, void(*print)(void*))
{
	printf("NODE\n");
	printf(" - id: %d\n", node_get_identifier(node));
	printf(" - parent: ");
	printf((node_has_parent(node)) == TRUE ? "%d" : "(null)", node_get_identifier(node_get_parent(node)));
	printf("\n");
	printf(" - left child: ");
	printf((node_has_left_child(node)) == TRUE ? "%d" : "(null)", node_get_identifier(node_get_left_child(node)));
	printf("\n");
	printf(" - right child: ");
	printf((node_has_right_child(node)) == TRUE ? "%d" : "(null)", node_get_identifier(node_get_right_child(node)));
	printf("\n");
	printf(" - data:");
	print(node_get_data(node));
	printf("\n");
}
#endif // DEBUG

//-------------------------------------------------------------------------------------------------------------------------------
