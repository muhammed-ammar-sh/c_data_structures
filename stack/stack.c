#include "stack.h"

void Stack_Init(stack_t* stack)
{
	SLL_InitList(stack);
}

void Stack_Push(stack_t* stack, void* item)
{
	SLL_PushFront(stack, item);
}

void* Stack_Top(stack_t* stack)
{
	return SLL_TopFront(stack);
}

void* Stack_Pop(stack_t* stack)
{
	return SLL_PopFront(stack);
}

bool Stack_IsEmpty(stack_t* stack)
{
	return SLL_IsEmpty(stack);
}
