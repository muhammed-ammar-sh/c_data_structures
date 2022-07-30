#include <stdint.h>
#include "bin_tree.h"

static void TraverseNodePostOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func);
static void TraverseNodePreOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func);
static void TraverseNodeInOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func);

void BinTree_InitTree(bin_tree_t *tree, void *root)
{
	if (tree == NULL)
	{
		return;
	}
	tree->root = root;
}

void BinTree_InitNode(void *node)
{
	if (node == NULL)
	{
		return;
	}
	((bin_tree_node_t *)node)->parent = NULL;
	BinTree_ConnectToLeft(node, NULL);
	BinTree_ConnectToRight(node, NULL);
}

void BinTree_ConnectToLeft(void *node, void *left_node)
{
	if (node == NULL)
	{
		return;
	}

	((bin_tree_node_t *)node)->left = left_node;
	if (left_node != NULL)
	{
		((bin_tree_node_t *)left_node)->parent = node;
	}
}

void BinTree_ConnectToRight(void *node, void *right_node)
{
	if (node == NULL)
	{
		return;
	}

	((bin_tree_node_t *)node)->right = right_node;
	if (right_node != NULL)
	{
		((bin_tree_node_t *)right_node)->parent = node;
	}
}

void BinTree_ConnectToLeftRight(void *node, void *left_node, void *right_node)
{
	BinTree_ConnectToLeft(node, left_node);
	BinTree_ConnectToRight(node, right_node);
}

void BinTree_Traverse(bin_tree_t *tree, bin_tree_traversal_type_t traversal_type, bin_tree_traverse_func_t func)
{
	if (tree == NULL || func == NULL)
	{
		return;
	}

	switch (traversal_type)
	{
	case BIN_TREE_IN_ORDER_TRAVERSAL:
		TraverseNodeInOrder(tree->root, func);
		break;

	case BIN_TREE_PRE_ORDER_TRAVERSAL:
		TraverseNodePreOrder(tree->root, func);
		break;

	case BIN_TREE_POST_ORDER_TRAVERSAL:
		TraverseNodePostOrder(tree->root, func);
		break;
	}
}

static void TraverseNodeInOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func)
{
	if (node == NULL)
	{
		return;
	}
	TraverseNodeInOrder(node->left, func);
	func(node);
	TraverseNodeInOrder(node->right, func);
}

static void TraverseNodePreOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func)
{
	if (node == NULL)
	{
		return;
	}
	func(node);
	TraverseNodePreOrder(node->left, func);
	TraverseNodePreOrder(node->right, func);
}

static void TraverseNodePostOrder(bin_tree_node_t *node, bin_tree_traverse_func_t func)
{
	if (node == NULL)
	{
		return;
	}
	TraverseNodePostOrder(node->left, func);
	TraverseNodePostOrder(node->right, func);
	func(node);
}