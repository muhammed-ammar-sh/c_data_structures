#ifndef STACK_H
#define STACK_h

#include "../singly_linked_list/sll.h"

typedef sll_t stack_t;
typedef sll_node_t stack_item_t;

void Stack_Init(stack_t* stack);
void Stack_Push(stack_t* stack, void* item);
void* Stack_Top(stack_t* stack);
void* Stack_Pop(stack_t* stack);
bool Stack_IsEmpty(stack_t* stack);

#endif