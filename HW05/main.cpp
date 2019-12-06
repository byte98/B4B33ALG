#include<stdio.h> 
#include<stdlib.h> 
#include <math.h>
#include "config.h"
#include <vector>

using namespace std;

static int nodes_count = 0;
static int consolidations = 0;

//Sources:
/* https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 * https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
 * https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
*/

struct node
{
	int key;
	struct node* left, * right;
};

// A utility function to create a new BST node 
struct node* newNode(int item)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST 
void inorder(struct node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key);

	/* Otherwise, recur down the tree */
	if (key <= node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);

	nodes_count++;

	/* return the (unchanged) node pointer */
	return node;
}

// C function to search a given key in a given BST 
struct node* search(struct node* root, int key)
{
	// Base Cases: root is null or key is present at root 
	if (root == NULL || root->key == key)
		return root;

	// Key is greater than root's key 
	if (root->key < key)
		return search(root->right, key);

	// Key is smaller than root's key 
	return search(root->left, key);
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node* minValueNode(struct node* node)
{
	struct node* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, int key)
{
	// base case 
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->left == NULL)
		{
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node* temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node 
		root->key = temp->key;

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->key);
	}
	nodes_count--;
	return root;
}

/* Compute the "maxDepth" of a tree -- the number of
	nodes along the longest path from the root node
	down to the farthest leaf node.*/
int maxDepth(struct node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

/* Function to do preorder traversal of tree */
void preOrder(struct node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->key);
	preOrder(node->left);
	preOrder(node->right);
}

/* Checks, whether consolidation of binary search tree is needed*/
bool consolidation_needed(struct  node* root, int count)
{
	bool reti = true;
	if ((int)pow((double)2, (double)maxDepth(root) - (double)1) <= (int)2 * (int)count)
	{
		reti = false;
	}
	return reti;
}

/* This function traverse the skewed binary tree and
   stores its nodes pointers in vector nodes[] */
void storeBSTNodes(struct node* root, vector<struct node*>& nodes)
{
	// Base case 
	if (root == NULL)
		return;

	// Store nodes in Inorder (which is sorted 
	// order for BST) 
	storeBSTNodes(root->left, nodes);
	nodes.push_back(root);
	storeBSTNodes(root->right, nodes);
}

/* Recursive function to construct binary tree */
struct node* buildTreeUtil(vector<struct node*>& nodes, int start,
	int end)
{
	// base case 
	if (start > end)
		return NULL;

	/* Get the middle element and make it root */
	int mid = (start + end) / 2;
	struct node* root = nodes[mid];

	/* Using index in Inorder traversal, construct
	   left and right subtress */
	root->left = buildTreeUtil(nodes, start, mid - 1);
	root->right = buildTreeUtil(nodes, mid + 1, end);

	return root;
}

// This functions converts an unbalanced BST to 
// a balanced BST 
struct node* buildTree(struct node* root)
{
	// Store nodes of given BST in sorted order 
	vector<struct node*> nodes;
	storeBSTNodes(root, nodes);

	// Constucts BST from nodes[] 
	int n = nodes.size();
	return buildTreeUtil(nodes, 0, n - 1);
}

static node* root = NULL;

/* Utility to count nodes inorder */
int countNodes(struct node* root)
{
	unsigned int count = 1;
	if (root->left != NULL) {
		count += countNodes(root->left);
	}
	if (root->right != NULL) {
		count += countNodes(root->right);
	}
	return count;
	
	
}

/*Function to get largewr power of two than number */
int getLargerTwoPow(int number)
{
	int reti = 0;
	while (pow(2, reti) < number)
	{
		reti++;
	}
	return reti;
}

/* Utiltiy to store tree as array*/
int AddToArray(struct node* node, int* arr, int i)
{
	if (node == NULL)
		return i;

	if (node->left != NULL)
		i = AddToArray(node->left, arr, i);
	arr[i] = node->key;
	i++;
	if (node->right != NULL)
		i = AddToArray(node->right, arr, i);

	return i;
}

/* Computes middle index between two indexes */
int getMiddle(int start, int end)
{
	return ceil(((end - start) / 2) + start);
}

/* Recursive function for tree consolidation */
void consolidate_recur(int* array, int start, int end, struct node* node, int count)
{
#ifdef DEBUG
	printf("\tConsolidating from: %d to: %d\n", start, end);
#endif // DEBUG

	if (start == end )
	{
		insert(node, array[start]);
#ifdef DEBUG
		printf("\tInserted: %d [%d]\n", array[start], start);
#endif // DEBUG
		return;
	}
	if (start > end)
	{
		return;
	}
	int idx = getMiddle(start, end);
#ifdef DEBUG
	printf("\tInserted: %d [%d]\n", array[idx], idx);
#endif // DEBUG

	insert(node, array[idx]);
	consolidate_recur(array, start, idx - 1, node, count);
	consolidate_recur(array, idx + 1, end, node, count);

}

/* Utility to consolidate tree*/
struct node* consolidate(struct node* root)
{
	int* array = (int*)malloc(countNodes(root) * sizeof(int));
	int last = AddToArray(root, array, 0);
	int maximal = pow((double)2, (double)getLargerTwoPow(countNodes(root))) - 1;
	int idx = getMiddle(0, maximal - 1);
	struct  node* reti = newNode(array[idx]);
	consolidate_recur(array, 0, idx - 1, reti, countNodes(root));
	consolidate_recur(array, idx + 1, last - 1, reti, countNodes(root));
	return reti;
}







// Driver Program to test above functions 
int main()
{
	int operations = 0;
	scanf("%d", &operations);
	for (int i = 0; i < operations; i++)
	{
		int value = 0;
		scanf("%d", &value);
		if (value > 0)
		{
			root = insert(root, value);
#ifdef DEBUG
			printf(" --- INSERT %d ---\n", value);
			printf("I: ");
			inorder(root);
			printf("\n");
			printf("P: ");
			preOrder(root);
			printf("\n\n");
#endif // DEBUG			
			if (consolidation_needed(root, countNodes(root)))
			{
				root = consolidate(root);
				consolidations++;
#ifdef DEBUG
				printf("=== CONSOLIDATING ===\n");
#endif // DEBUG

			}
#ifdef DEBUG
			printf("I: ");
			inorder(root);
			printf("\n");
			printf("P: ");
			preOrder(root);
			printf("\n\n");
#endif // DEBUG

		}
		else if (value < 0)
		{
#ifdef DEBUG
			printf(" --- REMOVE %d ---\n", abs(value));
#endif // DEBUG

			root = deleteNode(root, abs(value));
#ifdef DEBUG
			printf("[%d] >%d>\n", countNodes(root), maxDepth(root) - 1);
			printf("I: ");
			inorder(root);
			printf("\n");
			printf("P: ");
			preOrder(root);
			printf("\n\n");
#endif // DEBUG
			if (consolidation_needed(root, countNodes(root)))
			{
				root = consolidate(root);
				consolidations++;
#ifdef DEBUG
				printf("===CONSOLIDAING===\n");
				printf("[%d] >%d>\n", countNodes(root), maxDepth(root) - 1);
				printf("I: ");
				inorder(root);
				printf("\n");
				printf("P: ");
				preOrder(root);
				printf("\n\n");
#endif // DEBUG

			}

		}
	}
	printf("%d %d\n", consolidations, maxDepth(root) - 1);
	return 0;
}
