#include <stdio.h>
#include "dll.h"

typedef struct
{
	dll_node_t _n; // node
	char *str;
} str_t;

static void PrintAllStrsInList(dll_t *p_list);

int main(void)
{
	dll_t str_list;
	DLL_InitList(&str_list);

	str_t s1 = {.str = "AAA"};
	str_t s2 = {.str = "BBB"};
	str_t s3 = {.str = "CCC"};
	str_t s4 = {.str = "DDD"};

	DLL_PushFront(&str_list, &s2); // list: s2
	DLL_PushFront(&str_list, &s1); // list: s1 -> s2
	DLL_PushBack(&str_list, &s3);  // list: s1 -> s2 -> s3
	DLL_PushBack(&str_list, &s4);  // list: s1 -> s2 -> s3 -> s4
	PrintAllStrsInList(&str_list);
	// Strings in the list: AAA, BBB, CCC, DDD,

	str_t *popped_str = DLL_PopFront(&str_list); // list: s2 -> s3 -> s4
	printf("Popped string: %s \n", popped_str->str);
	// Popped string: AAA

	popped_str = DLL_PopBack(&str_list); // list: s2 -> s3
	printf("Popped string: %s \n", popped_str->str);
	// Popped string: DDD

	PrintAllStrsInList(&str_list);
	// Strings in the list: BBB, CCC,

	str_t *head_str = DLL_TopFront(&str_list);
	DLL_AddAfter(&str_list, head_str, &s1); // list: s2 -> s1 -> s3
	PrintAllStrsInList(&str_list);
	// Strings in the list: BBB, AAA, CCC,

	str_t *tail_str = DLL_TopBack(&str_list);
	DLL_AddAfter(&str_list, tail_str, &s4); // list: s2 -> s1 -> s4 -> s3
	PrintAllStrsInList(&str_list);
	// Strings in the list: BBB, AAA, DDD, CCC,
	
	return 0;
}

static void PrintAllStrsInList(dll_t *p_list)
{
	printf("Strings in the list: ");
	DLL_FOREACH_NODE(p_list, str_t, n)
	{
		printf("%s, ", n->str);
	}
	printf("\n");
}