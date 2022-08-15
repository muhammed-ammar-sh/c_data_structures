#include "dll.h"

void DLL_InitList(dll_t *list)
{
	if (list == NULL)
	{
		return;
	}

	list->head = NULL;
	list->tail = NULL;
}

void DLL_PushFront(dll_t *list, void *node)
{
	if (list == NULL || node == NULL
#if DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| DLL_Find(list, node) /* node is already in the list */
#endif
	)
	{
		return;
	}

	dll_node_t *n = node;
	n->next = list->head;
	n->prev = NULL;

	if (list->tail == NULL)
	{
		list->tail = n;
	}
	else
	{
		list->head->prev = n;
	}
	list->head = n;
}

void *DLL_TopFront(dll_t *list)
{
	if (list == NULL)
	{
		return NULL;
	}

	return (void *)list->head;
}

void *DLL_PopFront(dll_t *list)
{
	if (list == NULL || list->head == NULL /* Empty list*/)
	{
		return NULL;
	}

	dll_node_t *n = list->head;
	list->head = list->head->next;
	if (list->head == NULL)
	{
		list->tail = NULL;
	}

	return (void *)n;
}

void DLL_PushBack(dll_t *list, void *node)
{
	if (list == NULL || node == NULL
#if DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| DLL_Find(list, node) /* node is already in the list */
#endif
	)
	{
		return;
	}

	dll_node_t *n = (dll_node_t *)node;
	n->next = NULL;
	n->prev = list->tail;
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

void *DLL_TopBack(dll_t *list)
{
	if (list == NULL)
	{
		return NULL;
	}

	return (void *)list->tail;
}

void *DLL_PopBack(dll_t *list)
{
	if (list == NULL || list->head == NULL /* Empty list*/)
	{
		return NULL;
	}

	dll_node_t *n = list->tail;
	if (list->head == list->tail)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		n->prev->next = NULL;
		list->tail = n->prev;
	}

	return n;
}

void DLL_AddBefore(dll_t *list, void *node, void *node_to_be_added)
{
	if (list == NULL || node == NULL || node_to_be_added == NULL
#if DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| DLL_Find(list, node_to_be_added) || !SLL_Find(list, node)
#endif
	)
	{
		return;
	}

	dll_node_t *n = (dll_node_t *)node;
	dll_node_t *n_to_be_added = (dll_node_t *)node_to_be_added;

	n_to_be_added->next = n;
	n_to_be_added->prev = n->prev;
	n->prev = n_to_be_added;

	if (n_to_be_added->prev != NULL)
	{
		n_to_be_added->prev->next = n_to_be_added;
	}
	if (list->head == n)
	{
		list->head = n_to_be_added;
	}
}

void DLL_AddAfter(dll_t *list, void *node, void *node_to_be_added)
{
	if (list == NULL || node == NULL || node_to_be_added == NULL
#if DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| DLL_Find(list, node_to_be_added) || DLL_Find(list, node) == false
#endif
	)
	{
		return;
	}

	dll_node_t *n = (dll_node_t *)node;
	dll_node_t *n_to_be_added = (dll_node_t *)node_to_be_added;

	n_to_be_added->prev = n;
	n_to_be_added->next = n->next;
	if (n->next != NULL)
	{
		n->next->prev = n_to_be_added;
	}
	n->next = n_to_be_added;

	if (list->tail = n)
	{
		list->tail = n_to_be_added;
	}
}

bool DLL_Find(dll_t *list, void *node)
{
	if (list != NULL && node != NULL)
	{
		DLL_FOREACH_NODE(list, dll_node_t, i)
		{
			if (i == node)
			{
				return true;
			}
		}
	}
	return false;
}

void DLL_Erase(dll_t *list, void *node)
{
	if (list == NULL || node == NULL || list->head == NULL /* Empty list */
#if DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION == 1
		|| DLL_Find(list, node) == false /* node is NOT in the list */
#endif
	)
	{
		return;
	}

	dll_node_t *n = (dll_node_t *)node;

	if (n->next) // has a next node
	{
		n->next->prev = n->prev;
	}
	else // n is last item in list
	{
		list->tail = n->next;
	}

	if (n->prev) // has a prev node
	{
		n->prev->next = n->next;
	}
	else // n is first item in list
	{
		list->head = n->next;
	}
}

bool DLL_IsEmpty(dll_t *list)
{
	if (list == NULL)
	{
		return false;
	}
	return list->head == NULL;
}
