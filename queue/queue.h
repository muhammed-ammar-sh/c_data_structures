#ifndef QUEUE_H
#define QUEUE_H

#include "../singly_linked_list/sll.h"

typedef sll_t queue_t;
typedef sll_node_t queue_item_t;

void Queue_Init(queue_t* queue);
void Queue_Enqueue(queue_t* queue, void* item);
void* Queue_Dequeue(queue_t* queue);
bool Queue_IsEmpty(queue_t* queue);

#endif