#include "hw05_utils.h"
#include "config.h"
#include <stdio.h>
#include <assert.h>

void utils_default_deleter(void* data) {}
void utils_bst_insert(node_t* node, int data)
{
	void* actual_data = node_get_data(node);
	if (actual_data == NULL)
	{
#ifdef DEBUG
		printf("=> inserted to node %d <%d>\n", node_get_identifier(node), node_get_depth(node));
#endif // DEBUG

		node_set_data(node, (void*)data, utils_default_deleter);
		return;
	}
	else
	{
		int int_data = (int)actual_data;
		if (data > int_data)
		{
			if (node_get_right_child(node) == node_NULL)
			{
				node_t* n = node_create(NULL, utils_default_deleter);
				node_set_right_child_F(node, n);
			}
#ifdef DEBUG
			printf("\tinserting > stored (%d > %d) -> going to right subtree (%d <%d>)\n",
				data,
				int_data,
				node_get_identifier(node_get_right_child(node)),
				node_get_depth(node_get_right_child(node))
				);
#endif // DEBUG
#ifdef DEBUG
			if (node_check_null(node_get_right_child(node)) == TRUE)
			{
				printf("!!! RIGHT CHILD OF NODE %d <%d> IS NULL !!!\n", node_get_identifier(node), node_get_depth(node));
			}
#endif // DEBUG
			utils_bst_insert(node_get_right_child(node), data);
			return;
		}
		else if (data <= int_data)
		{
			if (node_get_left_child(node) == node_NULL)
			{
				node_t* n = node_create(NULL, utils_default_deleter);
				node_set_left_child_F(node, n);
			}
#ifdef DEBUG
			printf("\tinserting <= stored (%d <= %d) -> going to left subtree (%d <%d>)\n",
				data,
				int_data,
				node_get_identifier(node_get_left_child(node)),
				node_get_depth(node_get_left_child(node))
			);
#endif // DEBUG
#ifdef DEBUG
			if (node_check_null(node_get_left_child(node)) == TRUE)
			{
				printf("!!! LEFT CHILD OF NODE %d <%d> IS NULL !!!\n", node_get_identifier(node), node_get_depth(node));
			}
#endif // DEBUG

			utils_bst_insert(node_get_left_child(node), data);
			return;
		}
	}
}

node_t* utils_bst_find(node_t* node, int key)
{
	if (node == node_NULL)
	{
		return node_NULL;
	}
	else
	{
		if (node_get_data(node) == NULL)
		{
			return node_NULL;
		}
		else
		{
			int int_data = (int)node_get_data(node);
			if (int_data == key)
			{
				return node;
			}
			else if (key > int_data)
			{
				return (utils_bst_find(node_get_right_child(node), key));
			}
			else if (key < int_data)
			{
				return (utils_bst_find(node_get_left_child(node), key));
			}
		}
	}
	return node_NULL;
}

/*
node_t* utils_bst_delete(node_t* root, int key)
{
	node_t* node = utils_bst_find(root, key);
	node_t* reti = root;
	if (node != node_NULL)
	{
#ifdef DEBUG
		printf("\tfound node containing key: %d <%d>\n", node_get_identifier(node), node_get_depth(node));
#endif // DEBUG
		if (node_get_left_child(node) == node_NULL && node_get_right_child(node) == node_NULL) //Is leafe
		{
#ifdef DEBUG
			printf("=> is leafe -> removed from parent %d <%d>\n", node_get_identifier(node_get_parent(node)), node_get_depth(node_get_parent(node)));
#endif // DEBUG
			node_child_t position = node_get_child_position(node);
			if (position != NONE)
			{
				node_set_child_F(node_get_parent(node), node_NULL, position);
			}
			return reti;
		}
		node_t* left_child = node_get_left_child(node);
		bool has_left = ((node_check_null(left_child) == TRUE || node_get_identifier(left_child) == -1 || left_child == node_NULL) ? FALSE : TRUE);

		node_t* right_child = node_get_right_child(node);
		bool has_right = ((node_check_null(right_child) == TRUE || node_get_identifier(right_child) == -1 || right_child == node_NULL) ? FALSE : TRUE);

		if (has_left == TRUE && has_right == FALSE) // Has only left child
		{
#ifdef DEBUG
			printf("=> has only left child %d <%d> -> setting new child to parent %d <%d>\n",
				node_get_identifier(left_child),
				node_get_depth(left_child),
				node_get_identifier(node_get_parent(node)),
				node_get_depth(node_get_parent(node))
			);
#endif // DEBUG
			node_set_child_F(node_get_parent(node), left_child, node_get_child_position(node));
			return reti;
		}
		else if(has_right == TRUE && has_left == FALSE) // Has only right child
		{
#ifdef DEBUG
			printf("=> has only right child %d <%d> -> setting new child to parent %d <%d>\n",
				node_get_identifier(right_child),
				node_get_depth(right_child),
				node_get_identifier(node_get_parent(node)),
				node_get_depth(node_get_parent(node))
			);
#endif // DEBUG
			node_set_child_F(node_get_parent(node), right_child, node_get_child_position(node));
		}
	}
#ifdef DEBUG
	else
	{
		printf("\tkey is not in tree");
		printf("=> nothing has been deleted\n");
	}
#endif // DEBUG
	return reti;
}
*/

node_t* utils_bst_delete(node_t* root, int key)
{
	if (root == node_NULL)
	{
		return root;
	}

	if (key < (int)node_get_data(root))
	{
		node_set_left_child_F(root, utils_bst_delete(node_get_left_child(root), key));
	}
	else if (key > (int)node_get_data(root))
	{
		node_set_right_child_F(root, utils_bst_delete(node_get_right_child(root), key));
	}
	else
	{
		if (node_get_left_child(root) == node_NULL)
		{
			node_t* temp = node_get_right_child(root);
			node_delete(temp);
			return temp;
		}
		else if (node_get_right_child(root) == node_NULL)
		{
			node_t* temp = node_get_left_child(root);
			node_delete(temp);
			return temp;
		}
		node_t* temp = utils_bst_get_min_value_node(node_get_right_child(root));
		node_set_data(root, node_get_data(temp), utils_default_deleter);
		node_set_right_child_F(root, utils_bst_delete(node_get_right_child(root), key));
	}
	return root;
}

node_t* utils_bst_get_min_value_node(node_t* node)
{
	node_t* current = node;
	while (current != node_NULL && node_get_left_child(current) != node_NULL)
	{
		current = node_get_left_child(current);
	}
#ifdef DEBUG
	printf("\t\t\t most left leafe: %d <%d>\n", node_get_identifier(current), node_get_depth(current));
#endif // DEBUG

	return current;
}

void utils_bst_print_inorder(node_t* node)
{
	if (node == node_NULL)
	{
		return;
	}
	utils_bst_print_inorder(node_get_left_child(node));
	printf(" %2d", (int)node_get_data(node));
	utils_bst_print_inorder(node_get_right_child(node));
}
