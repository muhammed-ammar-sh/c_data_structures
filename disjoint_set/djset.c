#include "djset.h"

/**
 * @brief creates a singleton set from the given node
 */
void DJSet_InitNode(void *node)
{
	if (node == NULL)
	{
		return;
	}
	((djset_node_t *)node)->parent = node;
	((djset_node_t *)node)->rank = 0;
}

/**
 * @brief returns the parent of the set to which the given node belongs
 */
void *DJSet_Find(void *node)
{
	if (node == NULL)
	{
		return NULL;
	}

	// Use path compression heuristic
	djset_node_t *p = ((djset_node_t *)node)->parent;
	while (p->parent != p)
	{
		p = p->parent;
	}
	return p;
}
/**
 * @brief Merges the sets containing nodes a & b
 *
 * @param a first node
 * @param b second node
 * @return DJSET_CYCLE_DETECTED if the nodes are already in the same set,
 *         DJSET_CYCLE_NOT_DETECTED if they weren't in the same set and
 *         merging operation completed successfully
 */
djset_cycle_detection_t DJSet_Union(void *a, void *b)
{
	if (a == NULL || b == NULL)
	{
		return -1;
	}

	// Check if the nodes are already in the same set
	djset_node_t *pa = DJSet_Find(a), *pb = DJSet_Find(b);
	if (pa == pb)
	{
		return DJSET_CYCLE_DETECTED;
	}

	// Use rank heuristic
	if (pa->rank > pb->rank)
	{
		pb->parent = pa;
	}
	else
	{
		pa->parent = pb;
		if (pa->rank == pb->rank)
		{
			pb->rank++;
		}
	}

	return DJSET_CYCLE_NOT_DETECTED;
}
