#include "queue.h"

void Queue_Init(queue_t* queue)
{
	SLL_InitList(queue);
}

void Queue_Enqueue(queue_t* queue, void* item)
{
	SLL_PushBack(queue, item);
}

void* Queue_Dequeue(queue_t* queue)
{
	return SLL_PopFront(queue);
}

bool Queue_IsEmpty(queue_t* queue)
{
	return SLL_IsEmpty(queue);
}
