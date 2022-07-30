#ifndef STATIC_HEAP_H
#define STATIC_HEAP_H

#include <stdint.h>

// Macros to get the index of the parent, left, right nodes according to the given node index
#define PARENT_IDX(i) (((i)-1) / 2)
#define LEFT_CHILD_IDX(i) (((i)*2) + 1)
#define RIGHT_CHILD_IDX(i) (((i)*2) + 2)

/// the comparator should return positive value if a is greater / heavier than b
typedef int (*static_heap_comparator_t)(const void *a, const void *b);

typedef struct
{
	void *heap_array;
	size_t size;
	size_t capacity;
	size_t item_size;
	void *infinite_value;
	static_heap_comparator_t comparator;
} static_heap_t;

void StaticHeap_InitHeap(static_heap_t *heap, void *heap_array, size_t heap_capacity, size_t current_heap_size,
						 size_t item_size, void *infinite_value, static_heap_comparator_t comparator);
void StaticHeap_Insert(static_heap_t *heap, void *item);
void StaticHeap_Remove(static_heap_t *heap, size_t i);
void StaticHeap_SiftUp(static_heap_t *heap, size_t i);
void StaticHeap_SiftDown(static_heap_t *heap, size_t i);
void *StaticHeap_ExtractMax(static_heap_t *heap);

void StaticHeap_BuildHeap(static_heap_t *heap);
void StaticHeap_ChangePriority(static_heap_t *heap, size_t i, void *new_priority);

#endif