#include <stdio.h>
#include "sll.h"

typedef struct
{
	sll_node_t _n;
	int x, y;
} point_t;

static void PrintAllPointsInList(sll_t *p_list);

int main(void)
{
	sll_t point_list;
	SLL_InitList(&point_list);

	// Create static points in the stack
	point_t p1 = {.x = 1, .y = 1};
	point_t p2 = {.x = 2, .y = 2};
	point_t p3 = {.x = 3, .y = 3};
	point_t p4 = {.x = 4, .y = 4};

	SLL_PushFront(&point_list, &p1); // list = p1
	SLL_PushFront(&point_list, &p2); // list = p2 -> p1
	SLL_PushBack(&point_list, &p3);	 // list = p2 -> p1 -> p3
	SLL_PushBack(&point_list, &p4);	 // list = p2 -> p1 -> p3 -> p4

	PrintAllPointsInList(&point_list);
	// Points in the list: (2,2) (1,1) (3,3) (4,4)

	point_t *top_back_p = SLL_TopBack(&point_list);
	printf("Top back point is: (%d,%d) \n", top_back_p->x, top_back_p->y);
	// Top back point is: (4,4)

	point_t *popped_p = SLL_PopFront(&point_list); // list = p1 -> p3 -> p4
	printf("Popped point is: (%d,%d) \n", popped_p->x, popped_p->y);
	// Popped point is: (2,2)

	popped_p = SLL_PopBack(&point_list); // list = p1 -> p3
	printf("Popped point is: (%d,%d) \n", popped_p->x, popped_p->y);
	// Popped point is: (4,4)

	PrintAllPointsInList(&point_list);
	// Points in the list: (1,1) (3,3)

	SLL_AddAfter(&point_list, &p1, &p4); // list = p1 -> p4 -> p3
	PrintAllPointsInList(&point_list);
	// Points in the list: (1,1) (4,4) (3,3)

	SLL_AddBefore(&point_list, &p1, &p2); // list = p2 -> p1 -> p4 -> p3
	PrintAllPointsInList(&point_list);
	// Points in the list: (2,2) (1,1) (4,4) (3,3)

	SLL_Erase(&point_list, &p3); // list = p2 -> p1 -> p4
	PrintAllPointsInList(&point_list);
	// Points in the list: (2,2) (1,1) (4,4)

	SLL_Erase(&point_list, &p2); // list = p1 -> p4
	PrintAllPointsInList(&point_list);
	// Points in the list: (1,1) (4,4)

	SLL_Erase(&point_list, &p1); // list = p4
	PrintAllPointsInList(&point_list);
	// Points in the list: (4,4)

	SLL_Erase(&point_list, &p4); // list =
	PrintAllPointsInList(&point_list);
	// Points in the list:

	return 0;
}

static void PrintAllPointsInList(sll_t *p_list)
{
	printf("Points in the list: ");
	SLL_FOREACH_NODE(p_list, point_t, n)
	{
		printf("(%d,%d) ", n->x, n->y);
	}
	printf("\n");
}