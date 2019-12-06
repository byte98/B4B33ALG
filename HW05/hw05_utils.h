#ifndef __HW05_UTILS_H__
#define __HW05_UTILS_H__
#include "node.h"
#include "simple_bool.h"

void utils_default_deleter(void* data);
void utils_bst_insert(node_t* node, int data);
node_t* utils_bst_find(node_t* node, int key);
bool utils_consolidation_needed(node_t* root);
node_t* utils_bst_delete(node_t* node, int key);
node_t* utils_bst_get_min_value_node(node_t* node);
void utils_bst_print_inorder(node_t* node);
#endif // !__HW05_UTILS_H__
