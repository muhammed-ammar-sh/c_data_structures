#include "sll.h"

static sll_node_t **SLL_GetPtrPointingToNode(sll_t *list, sll_node_t *node);

void SLL_InitList(sll_t *list)
{
	if (list == NULL)
	{
		return;
	}

	list->head = NULL;
	list->tail = NULL;
}

void SLL_PushFront(sll_t *list, void *node)
{
	if (list == NULL || node == NULL
#if SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| SLL_Find(list, node) /* node is already in the list */
#endif
	)
	{
		return;
	}

	sll_node_t *n = node;
	n->next = list->head;
	list->head = n;

	if (list->tail == NULL)
	{
		list->tail = n;
	}
}

void *SLL_TopFront(sll_t *list)
{
	if (list == NULL)
	{
		return NULL;
	}

	return (void *)list->head;
}

void *SLL_PopFront(sll_t *list)
{
	if (list == NULL || list->head == NULL /* Empty list*/)
	{
		return NULL;
	}

	sll_node_t *n = list->head;
	list->head = list->head->next;

	if (list->head == NULL) // Node was the last one in the list ?
	{
		list->tail = NULL;
	}

	return (void *)n;
}

void SLL_PushBack(sll_t *list, void *node)
{
	if (list == NULL || node == NULL
#if SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| SLL_Find(list, node) /* node is already in the list */
#endif
	)
	{
		return;
	}

	sll_node_t *n = (sll_node_t *)node;
	n->next = NULL;
	if (list->tail == NULL /*Empty list*/)
	{
		list->head = n;
	}
	else
	{
		list->tail->next = n;
	}
	list->tail = n;
}

void *SLL_TopBack(sll_t *list)
{
	if (list == NULL)
	{
		return NULL;
	}

	return (void *)list->tail;
}

void *SLL_PopBack(sll_t *list)
{
	if (list == NULL || list->head == NULL /* Empty list*/)
	{
		return NULL;
	}
	sll_node_t *n = list->tail;

	// this is a pointer to the head or a pointer to the "next" variable of the
	// node just behind the last node
	sll_node_t **thing_to_update = SLL_GetPtrPointingToNode(list, list->tail);
	*thing_to_update = NULL;
	list->tail = (sll_node_t*)thing_to_update;

	return (void *)n;
}

void SLL_AddBefore(sll_t *list, void *node, void *node_to_be_added)
{
	if (list == NULL || node == NULL || node_to_be_added == NULL
#if SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| SLL_Find(list, node_to_be_added) || SLL_Find(list, node) == false
#endif
	)
	{
		return;
	}

	// this is a pointer to the head or a pointer to the "next" variable of the
	// node just behind the last node
	sll_node_t **thing_to_update = SLL_GetPtrPointingToNode(list, node);
	*thing_to_update = node_to_be_added;
	((sll_node_t *)node_to_be_added)->next = node;
}

/**
 * @brief This function returns a pointer to the object that is pointing to the 
 *        given node in a single linked list, which can be a pointer to the head 
 * 		  of the list or a pointer to "next" element of the previous node.
 */
static sll_node_t **SLL_GetPtrPointingToNode(sll_t *list, sll_node_t *node)
{
	// ptr could be pointing to the head of the list or the node before node
	sll_node_t **ptr = &list->head;
	while (*ptr != node)
	{
		ptr = &(*ptr)->next;
	}
	return ptr;
}

void SLL_AddAfter(sll_t *list, void *node, void *node_to_be_added)
{
	if (list == NULL || node == NULL || node_to_be_added == NULL
#if SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| SLL_Find(list, node_to_be_added) || !SLL_Find(list, node)
#endif
	)
	{
		return;
	}

	((sll_node_t *)node_to_be_added)->next = ((sll_node_t *)node)->next;
	((sll_node_t *)node)->next = node_to_be_added;

	if (list->tail == node)
	{
		list->tail = node_to_be_added;
	}
}

bool SLL_Find(sll_t *list, void *node)
{
	if (list != NULL && node != NULL)
	{
		SLL_FOREACH_NODE(list, sll_node_t, i)
		{
			if (i == node)
			{
				return true;
			}
		}
	}
	return false;
}

void SLL_Erase(sll_t *list, void *node)
{
	if (list == NULL || node == NULL || list->head == NULL /* Empty list */
#if SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| ! SLL_Find(list, node) /* node is NOT in the list */
#endif
	)
	{
		return;
	}

	sll_node_t **thing_to_update = SLL_GetPtrPointingToNode(list, node);
	*thing_to_update = ((sll_node_t *)node)->next;

	if (list->tail == node)
	{
		list->tail = *thing_to_update;
	}
}

bool SLL_IsEmpty(sll_t *list)
{
	if (list == NULL)
	{
		return false;
	}
	return list->head == NULL;
}
