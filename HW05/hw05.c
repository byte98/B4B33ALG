#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "config.h"
#include "hw05_utils.h"
#include "node.h"


int OPERATIONS;
int MAXIMAL_DEPTH = 0;
int NODES = 0;


int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;
	scanf("%d", &OPERATIONS);
	node_t* root = node_create_empty();
	node_set_depth(root, 0);
	for (int i = 0; i < OPERATIONS; i++)
	{
		int value = 0;
		scanf("%d", &value);
		if (value > 0)	//INSERT
		{
#ifdef DEBUG
			printf("Inserting %d to tree...\n", value);
#endif // DEBUG
			if (NODES == 0) //FIRST NODE
			{
#ifdef DEBUG
				printf("=> inserted to node %d <%d> (root)\n", node_get_identifier(root), node_get_depth(root));
#endif // DEBUG

				node_set_data(root, value, utils_default_deleter);
			}
			else
			{
				utils_bst_insert(root, value);
			}
			NODES++;
			utils_bst_print_inorder(root);
			printf("\n");
		}
		else
		{
#ifdef DEBUG
			printf("Deleting %d from tree...\n", abs(value));
#endif // DEBUG
			root = utils_bst_delete(root, abs(value));
			utils_bst_print_inorder(root);
			printf("\n");
		}
	}
#ifdef DEBUG
	printf("=== Depth of tree: %d ===\n", MAXIMAL_DEPTH);
#endif // DEBUG
	utils_bst_print_inorder(root);
	printf("\n");

	return reti;
}