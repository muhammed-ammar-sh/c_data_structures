/**
 * @file sll.h
 * @author Muhammed (Ammar) Sairoglu
 * @brief Singly linked list implementation for static nodes
 * @version 1.0
 * @date 2022-07-29
 *
 * @copyright MIT
 *
 */

#ifndef SLL_H
#define SLL_H

#include <stddef.h>
#include <stdbool.h>

/*
Assign 1 to the next macro if you want to check if the node exists in
the list before any operation (pushing, popping, adding ...)
This can be very helpful to prevent pushing the same static node twice
to the list, removing not existed node ...
 */
#define SLL_CHECK_IF_NODE_EXISTS_BEFORE_OPERATION 0

typedef struct _sll_node
{
	struct _sll_node *next;
} sll_node_t;

typedef struct
{
	sll_node_t *head;
	sll_node_t *tail;
} sll_t;

/// Macro to iterate through all list nodes
#define SLL_FOREACH_NODE(_list, _node_type, _node)           \
	for (_node_type * (_node) = (_node_type *)(_list)->head; \
		 (_node) != NULL;                                    \
		 (_node) = (_node_type *)(((sll_node_t *)(_node))->next))

void SLL_InitList(sll_t *list);

void SLL_PushFront(sll_t *list, void *node);
void *SLL_TopFront(sll_t *list);
void *SLL_PopFront(sll_t *list);

void SLL_PushBack(sll_t *list, void *node);
void *SLL_TopBack(sll_t *list);
void *SLL_PopBack(sll_t *list);

void SLL_AddBefore(sll_t *list, void *node, void *node_to_be_added);
void SLL_AddAfter(sll_t *list, void *node, void *node_to_be_added);

bool SLL_Find(sll_t *list, void *node);
void SLL_Erase(sll_t *list, void *node);

bool SLL_IsEmpty(sll_t *list);

#endif