#ifndef BIN_TREE_H
#define BIN_TREE_H

typedef struct _bin_tree_node
{
	struct _bin_tree_node *parent;
	struct _bin_tree_node *left;
	struct _bin_tree_node *right;
} bin_tree_node_t;

typedef struct
{
	bin_tree_node_t *root;
} bin_tree_t;

typedef enum
{
	BIN_TREE_PRE_ORDER_TRAVERSAL,
	BIN_TREE_IN_ORDER_TRAVERSAL,
	BIN_TREE_POST_ORDER_TRAVERSAL,
} bin_tree_traversal_type_t;

typedef void (*bin_tree_traverse_func_t)(void *);

void BinTree_InitTree(bin_tree_t *tree, void *root);
void BinTree_InitNode(void *node);
void BinTree_ConnectToLeft(void *node, void *left_node);
void BinTree_ConnectToRight(void *node, void *right_node);
void BinTree_ConnectToLeftRight(void *node, void *left_node, void *right_node);
void BinTree_Traverse(bin_tree_t *tree, bin_tree_traversal_type_t traversal_type, bin_tree_traverse_func_t func);

static inline void *BinTree_GetLeft(void *node)
{
	return ((bin_tree_node_t*)node)->left;
}

static inline void *BinTree_GetRight(void *node)
{
	return ((bin_tree_node_t*)node)->right;
}

static inline void *BinTree_GetParent(void *node)
{
	return ((bin_tree_node_t*)node)->parent;
}

#endif