#ifndef PRIO_QUEUE_H
#define PRIO_QUEUE_H

#include "../static_heap/static_heap.h"

typedef static_heap_t prio_queue_t;
typedef static_heap_comparator_t prio_queue_comparator_t;

void PrioQueue_Init(prio_queue_t* queue, void* queue_array, size_t queue_capacity, size_t item_size, prio_queue_comparator_t comparator);
void PrioQueue_Insert(prio_queue_t* queue, void *item);
void* PrioQueue_ExtractMax(prio_queue_t* queue);

#endif

