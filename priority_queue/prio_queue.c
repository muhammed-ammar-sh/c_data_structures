#include "prio_queue.h"

void PrioQueue_Init(prio_queue_t *queue, void *queue_array, size_t queue_capacity,
					size_t item_size, prio_queue_comparator_t comparator)
{
	StaticHeap_InitHeap(queue, queue_array, queue_capacity, 0, item_size,
				   NULL /*NULL is passed because remove function (StaticHeap_Remove) isn't used*/,
				   comparator);
}

void PrioQueue_Insert(prio_queue_t *queue, void *item)
{
	StaticHeap_Insert(queue, item);
}

void *PrioQueue_ExtractMax(prio_queue_t *queue)
{
	return StaticHeap_ExtractMax(queue);
}
