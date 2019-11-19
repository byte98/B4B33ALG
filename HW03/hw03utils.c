#include "hw03utils.h"
#include "simple_bool.h"
#include "plane.h"

#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------------------------------------------------

int utils_compute_difference(node_t* node)
{
	int reti = 0;
	reti = abs(utils_compute_left_weight(node) - utils_compute_right_weight(node));
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_compute_left_weight(node_t* node)
{
	int reti = 0;
	if (node_check_null(node) == FALSE)
	{
		reti = utils_compute_subtree_weight(node_get_left_child(node));
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_compute_right_weight(node_t* node)
{
	int reti = 0;
	if (node_check_null(node) == FALSE)
	{
		reti = utils_compute_subtree_weight(node_get_right_child(node));
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_compute_subtree_weight(node_t* node)
{
	int reti = 0;
	if (node_is_leaf(node) == FALSE)
	{
		if (node_has_left_child(node) == TRUE)
			reti += utils_compute_subtree_weight(node_get_left_child(node));

		if (node_has_right_child(node) == TRUE)
			reti += utils_compute_subtree_weight(node_get_right_child(node));
	}
	else
	{
		reti = plane_get_weight(node_get_data(node));
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
plane_array_t* utils_create_plane_array(int count)
{
	plane_array_t* reti = (plane_array_t*)malloc(sizeof(plane_array_t*));
	if (reti != (plane_array_t*)NULL)
	{
		reti->count = count;
		reti->data = (plane_t**)malloc(sizeof(plane_t));
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void utils_delete_plane_array(plane_array_t* plane_arr)
{
	free(plane_arr->data);
	free(plane_arr);
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_node_evaluator(node_t* node)
{
	int reti = 0;
	if (node_is_leaf(node) == TRUE)
	{
		reti = plane_get_weight(node_get_data(node));
	}
	else
	{
		reti = utils_compute_subtree_weight(node);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

node_t* utils_create_tree(plane_t** planes, int start, int end)
{
#ifdef DEBUG
	printf("Checking interval <%d;%d>\n", start, end);
#endif // DEBUG

	node_t* reti = node_create_empty();
	if (start == end)
	{
		node_set_data(reti, planes[start], plane_deleter);
	}
	else
	{
		int ideal = utils_get_ideal_delimiter(planes, start, end);
		node_set_left_child(reti, utils_create_tree(planes, start, ideal));
		node_set_right_child(reti, utils_create_tree(planes, ideal + 1, end));
		int* diff = (int*)malloc(sizeof(int));
		*diff = utils_compute_difference(reti);
		node_set_data(reti, diff, utils_int_deleter);
#ifdef DEBUG
		printf("Setting data to node:: [%d]: %d\n", node_get_identifier(reti), *diff);
#endif // DEBUG



	}


	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_get_ideal_delimiter(plane_t** planes, int start, int end)
{
	int min = INT_MAX;
	int reti = INT_MAX;
	for (int i = start; i <= end; i++)
	{
		int sum1 = utils_sum_planes(planes, 0, i);
		int sum2 = utils_sum_planes(planes, i + 1, end);
		if (abs(sum2 - sum1) < min)
		{
			min = abs(sum1 - sum2);
			reti = i;
		}
	}
#ifdef DEBUG
	printf("Split at: %d [%d | %d]\n", reti, utils_sum_planes(planes, start, reti), utils_sum_planes(planes, (reti + 1), end));
#endif // DEBUG

	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

int utils_sum_planes(plane_t** planes, int start, int end)
{
	int reti = 0;
	for (int i = start; i <= end; i++)
	{
		reti += plane_get_weight(planes[i]);
	}
	return reti;
}

//-------------------------------------------------------------------------------------------------------------------------------

void utils_int_deleter(void* int_ptr)
{
	free(int_ptr);
}

//-------------------------------------------------------------------------------------------------------------------------------

void utils_print_tree(node_t* node)
{
	printf("(%d)\n", node_get_identifier(node));
	if (node_is_leaf(node) == TRUE)
	{
		return;
	}
	else
	{
		utils_print_tree(node_get_left_child(node));
		utils_print_tree(node_get_right_child(node));
	}
}


int utils_count_whole_difference(node_t* node)
{
	int reti = 0;
	if (node_is_leaf(node) == FALSE)
	{
		reti += *(int*)node_get_data(node);
		if (node_is_leaf(node_get_left_child(node)) == FALSE)
		{
			reti += utils_count_whole_difference(node_get_left_child(node));
		}
		if (node_is_leaf(node_get_right_child(node)) == FALSE)
		{
			reti += utils_count_whole_difference(node_get_right_child(node));
		}
	}
	return reti;
}

int utils_place_pilot(node_t* root, int weight)
{

	int min = INT_MAX;
	int leaves_count = node_count_leaves(root);
	node_t** leaves = (node_t**)malloc(leaves_count * sizeof(node_t*));
	node_get_leaves(root, leaves);
	node_t* position = node_NULL;
	for (int i = 0; i < leaves_count; i++)
	{
		plane_t* plane = (plane_t*)node_get_data(leaves[i]);
		bool plane_has_pilot = plane_get_has_pilot(plane);
		if (plane_has_pilot == FALSE)
		{
			int res = utils_try_place_pilot(leaves[i], weight);
			if (res < min)
			{
				min = res;
				position = leaves[i];
			}
		}
	}
	plane_set_pilot((plane_t*)node_get_data(position), weight);
	utils_update_node(position);
#ifdef DEBUG
	printf(">>%d(%d)\n", node_get_identifier(position), plane_get_weight(node_get_data(position)));
#endif // DEBUG


	free(leaves);
	//utils_update_tree_differences(position);
	return min;
}

int utils_try_place_pilot(node_t* node, int weight)
{
	int reti = 0;
	plane_set_pilot((plane_t*)node_get_data(node), weight);
	utils_update_node(node);
	node_t* root = node;
	while (node_has_parent(root) == TRUE)
	{
		root = node_get_parent(root);
		break;
	}
	reti = utils_count_whole_difference(root);
	plane_unset_pilot((plane_t*)node_get_data(node), weight);
	utils_update_node(node);
	return reti;
}

void utils_update_tree_differences(node_t* leafe)
{
	node_t* parent = leafe;
	node_t* child = node_NULL;
	int sum = plane_get_weight(node_get_data(leafe));
	while (node_has_parent(parent))
	{
		child = parent;
		parent = node_get_parent(parent);
		if (node_is_leaf(parent) == FALSE)
		{
			int* diff = node_get_data(parent);
			if (node_check_same(node_get_left_child(parent), child) == TRUE)
			{
				//Left child
				int right_weight = utils_compute_subtree_weight(node_get_right_child(parent));
				*diff = abs(sum - right_weight);
				node_set_data(parent, diff, utils_int_deleter);
				sum += right_weight;
			}
			if (node_check_same(node_get_right_child(parent), child) == TRUE)
			{
				//Right child
				int left_weight = utils_compute_subtree_weight(node_get_left_child(parent));
				*diff = abs(sum - left_weight);
				node_set_data(parent, diff, utils_int_deleter);
				sum += left_weight;
			}
		}
		
	}

}

void utils_update_node(node_t* node)
{
	if (node_has_parent(node) == FALSE)
	{
		int left_weight = utils_compute_subtree_weight(node_get_left_child(node));
		int right_weight = utils_compute_subtree_weight(node_get_right_child(node));
#ifdef DEBUG

		printf("[id: %d]: L:%d R:%d\n", node_get_identifier(node), left_weight, right_weight);
#endif // DEBUG

		int* diff = node_get_data(node);
		*diff = abs(left_weight - right_weight);
		node_set_data_force(node, diff, utils_int_deleter);
		return;
	}
	if (node_is_leaf(node) == FALSE)
	{
		int left_weight = utils_compute_subtree_weight(node_get_left_child(node));
		int right_weight = utils_compute_subtree_weight(node_get_right_child(node));
#ifdef DEBUG

		printf("[id: %d]: L:%d R:%d\n", node_get_identifier(node), left_weight, right_weight);
#endif // DEBUG

		int* diff = node_get_data(node);
		*diff = abs(left_weight - right_weight);
		node_set_data_force(node, diff, utils_int_deleter);
		utils_update_node(node_get_parent(node));
	}
	else
	{
		utils_update_node(node_get_parent(node));
	}
}

int utils_default_evaluator(node_t* node)
{
	if (node_is_leaf(node) == TRUE)
	{
		return plane_get_weight(node_get_data(node));
	}
	else
	{
		int* reti = node_get_data(node);
		return *reti;
	}
}

void utils_set_evaluator(node_t* node)
{
	node_set_evaluator(node, utils_default_evaluator);
	if (node_is_leaf(node) == FALSE)
	{
		if (node_has_left_child(node) == TRUE)
		{
			utils_set_evaluator(node_get_left_child(node));
		}
		if (node_has_right_child(node) == TRUE)
		{
			utils_set_evaluator(node_get_right_child(node));
		}
	}
}
