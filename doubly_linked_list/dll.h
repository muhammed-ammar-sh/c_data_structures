#ifndef DLL_H
#define DLL_H

#include <stddef.h>
#include <stdbool.h>

#define DLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION 0

typedef struct _dll_node
{
	struct _dll_node *next;
	struct _dll_node *prev;
} dll_node_t;

typedef struct
{
	dll_node_t *head;
	dll_node_t *tail;
} dll_t;

/// Macro to iterate through all list nodes
#define DLL_FOREACH_NODE(_list, _node_type, _node)        \
	for (_node_type * (_node) = (_node_type *)(_list)->head; \
		 (_node) != NULL;                                    \
		 (_node) = (_node_type *)(((dll_node_t *)(_node))->next))

void DLL_InitList(dll_t *list);

void DLL_PushFront(dll_t *list, void *node);
void *DLL_TopFront(dll_t *list);
void *DLL_PopFront(dll_t *list);

void DLL_PushBack(dll_t *list, void *node);
void *DLL_TopBack(dll_t *list);
void *DLL_PopBack(dll_t *list);

void DLL_AddBefore(dll_t *list, void *node, void *node_to_be_added);
void DLL_AddAfter(dll_t *list, void *node, void *node_to_be_added);

bool DLL_Find(dll_t *list, void *node);
void DLL_Erase(dll_t *list, void *node);

bool DLL_IsEmpty(dll_t *list);

#endif