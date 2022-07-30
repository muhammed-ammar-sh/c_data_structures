#include "static_heap.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Macros to get pointers to the parent, left, right nodes according to the given node index
#define ITEM_PTR(heap, i) ((char *)(heap)->heap_array + ((i) * (heap)->item_size))
#define PARENT_PTR(heap, i) ((char *)(heap)->heap_array + PARENT_IDX(i) * (heap)->item_size)
#define LEFT_CHILD_PTR(heap, i) ((char *)(heap)->heap_array + LEFT_CHILD_IDX(i) * (heap)->item_size)
#define RIGHT_CHILD_PTR(heap, i) ((char *)(heap)->heap_array + RIGHT_CHILD_IDX(i) * (heap)->item_size)

static void swap(static_heap_t *heap, void *v1, void *v2);

/**
 * @brief Initializes a heap object
 *
 * @param heap pointer to the static heap object
 * @param heap_array the array that contains / will contain the heap elements
 * @param heap_capacity the maximum element count of the heap (heap array size)
 * @param current_heap_size the count of the filled element in the heap array
 * @param item_size the size of the heap array element
 * @param infinite_value pointer to an object with the greatest value, used in removing elements
 * @param comparator pointer to function can compare heap elements
 */
void StaticHeap_InitHeap(static_heap_t *heap, void *heap_array, size_t heap_capacity, size_t current_heap_size,
						 size_t item_size, void *infinite_value, static_heap_comparator_t comparator)
{
	if (heap == NULL || heap_array == NULL || comparator == NULL)
	{
		return;
	}
	heap->heap_array = heap_array;
	heap->capacity = heap_capacity;
	heap->item_size = item_size;
	heap->infinite_value = infinite_value;
	heap->comparator = comparator;
	heap->size = current_heap_size;
}

///@brief inserts a new item to the heap array and reorders the heap 
void StaticHeap_Insert(static_heap_t *heap, void *item)
{
	if (heap == NULL)
	{
		return;
	}

	if (heap->size < heap->capacity)
	{
		memcpy(ITEM_PTR(heap, heap->size), item, heap->item_size);
		heap->size++;
		StaticHeap_SiftUp(heap, heap->size - 1);
	}
}

///@brief removes an item with index i from the heap
void StaticHeap_Remove(static_heap_t *heap, size_t i)
{
	if (heap == NULL || i >= heap->size)
	{
		return;
	}
	memcpy(ITEM_PTR(heap, i), heap->infinite_value, heap->item_size);
	StaticHeap_SiftUp(heap, i);
	StaticHeap_ExtractMax(heap);
}

void StaticHeap_SiftUp(static_heap_t *heap, size_t i)
{
	if (heap == NULL || i >= heap->size)
	{
		return;
	}

	while (i > 0 && heap->comparator(PARENT_PTR(heap, i), ITEM_PTR(heap, i)) < 0)
	{
		swap(heap, PARENT_PTR(heap, i), ITEM_PTR(heap, i));
		i = PARENT_IDX(i);
	}
}

///@brief swaps tow nodes' contents from the heap array
static void swap(static_heap_t *heap, void *v1, void *v2)
{
	uint8_t temp[heap->item_size];

	// if compiler doesn't support VLAs
	// void *temp = malloc(heap->item_size);
	memcpy(temp, v1, heap->item_size);
	memcpy(v1, v2, heap->item_size);
	memcpy(v2, temp, heap->item_size);
	// free(temp);
}

void StaticHeap_SiftDown(static_heap_t *heap, size_t i)
{
	if (heap == NULL || i >= heap->size)
	{
		return;
	}

	size_t max_i = i, l, r;
	bool swapped; // flag indicates a node has been swapped so another check procedure is required
	do
	{
		swapped = false;
		// swap the node with the biggest node of its childs
		l = LEFT_CHILD_IDX(i);
		if (l < heap->size && heap->comparator(ITEM_PTR(heap, l), ITEM_PTR(heap, max_i)) > 0)
		{
			max_i = l;
		}

		r = RIGHT_CHILD_IDX(i);
		if (r < heap->size && heap->comparator(ITEM_PTR(heap, r), ITEM_PTR(heap, max_i)) > 0)
		{
			max_i = r;
		}

		if (i != max_i)
		{
			swapped = true;
			swap(heap, ITEM_PTR(heap, i), ITEM_PTR(heap, max_i));
			i = max_i;
		}
	} while (swapped == true);
}

///@brief Extracts the maximum node/item from a sorted heap and returns a pointer to it
void *StaticHeap_ExtractMax(static_heap_t *heap)
{
	if (heap == NULL || heap->size == 0)
	{
		return NULL;
	}
	// put the max node on the last cell of the array
	swap(heap, ITEM_PTR(heap, 0), ITEM_PTR(heap, heap->size - 1));
	// get its pointer
	void *res = ITEM_PTR(heap, heap->size - 1);
	heap->size--;
	// relocate the node that we put in the place of the max node
	StaticHeap_SiftDown(heap, 0);
	return res;
}

///@brief Reorders the heap nodes/items
void StaticHeap_BuildHeap(static_heap_t *heap)
{
	if (heap == NULL || heap->size <= 1)
	{
		return;
	}

	for (int i = (heap->size - 1) / 2; i >= 0; i--)
	{
		StaticHeap_SiftDown(heap, i);
	}
}

///@brief changes the priority (weight) of an item/node with given index i
void StaticHeap_ChangePriority(static_heap_t *heap, size_t i, void *new_priority)
{
	if (heap == NULL || i >= heap->size)
	{
		return;
	}

	// copy current item to temp
	uint8_t temp[heap->item_size];
	// if compiler doesn't support VLAs
	// void* temp = malloc(heap->item_size);

	memcpy(temp, ITEM_PTR(heap, i), heap->item_size);
	// copy new item to current item
	memcpy(ITEM_PTR(heap, i), new_priority, heap->item_size);
	// if the new item is bigger than the old one sift up, else sift down
	if (heap->comparator(new_priority, temp) > 0)
	{
		StaticHeap_SiftUp(heap, i);
	}
	else
	{
		StaticHeap_SiftDown(heap, i);
	}
	// free(temp);
}
