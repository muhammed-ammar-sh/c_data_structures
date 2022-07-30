#include <stdint.h>
#include <stdio.h>
#include "bin_tree.h"

typedef struct
{
	bin_tree_node_t _n;
	int value;
} int_node_t;

void ProcessNode(void *node);
void InitSequentialNodeArray(int_node_t *arr, size_t size);

int main(void)
{
	bin_tree_t tree;
	int_node_t node[9];
	InitSequentialNodeArray(node, 9);

	BinTree_InitTree(&tree, &node[0]);
	
	/**
	 * Connect the node in the binary tree as below
	 * 	      0
	 * 		/  \
	 *     /    \
	 * 	  /	     \
	 * 	 1   	  4		
	 * 	/  \     /	\
	 * 2	3   5	 6
	 * 				/ \
	 * 			   7   8
	 */


	BinTree_ConnectToLeft(&node[0], &node[1]);
	BinTree_ConnectToLeftRight(&node[1], &node[2], &node[3]);
	BinTree_ConnectToRight(&node[0], &node[4]);
	BinTree_ConnectToLeftRight(&node[4], &node[5], &node[6]);
	BinTree_ConnectToLeftRight(&node[6], &node[7], &node[8]);

	printf("In order traversal ...\n");
	BinTree_Traverse(&tree, BIN_TREE_IN_ORDER_TRAVERSAL, ProcessNode);

	printf("\n\nPre-order traversal ...\n");
	BinTree_Traverse(&tree, BIN_TREE_PRE_ORDER_TRAVERSAL, ProcessNode);

	printf("\n\nPost-order traversal ...\n");
	BinTree_Traverse(&tree, BIN_TREE_POST_ORDER_TRAVERSAL, ProcessNode);

	return 0;
}

void InitSequentialNodeArray(int_node_t *arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		BinTree_InitNode(&arr[i]);
		arr[i].value = i;
	}
}

void ProcessNode(void *node)
{
	int_node_t *n = (int_node_t *)node;
	printf("Node: %d, ", n->value);
	
	int_node_t * l = BinTree_GetLeft(n);
	if (l)
		printf("Left node: %d, ", l->value);

	
	int_node_t * r = BinTree_GetRight(n);
	if (r)
		printf("Right node: %d, ", r->value);
	
	printf("\n");
}