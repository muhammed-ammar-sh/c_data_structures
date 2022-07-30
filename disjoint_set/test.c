#include <stdio.h>
#include <stdbool.h>
#include "djset.h"

typedef struct
{
	djset_node_t _n;
	char *str;
} str_set_node_t;

static bool NodesInTheSameSet(void *a, void *b);

int main(void)
{
	str_set_node_t s1 = {.str = "AAA"};
	str_set_node_t s2 = {.str = "BBB"};
	str_set_node_t s3 = {.str = "CCC"};
	str_set_node_t s4 = {.str = "DDD"};
	str_set_node_t s5 = {.str = "EEE"};

	DJSet_InitNode(&s1);
	DJSet_InitNode(&s2);
	DJSet_InitNode(&s3);
	DJSet_InitNode(&s4);
	DJSet_InitNode(&s5);

	DJSet_Union(&s1, &s2); // {s1, s2}
	DJSet_Union(&s3, &s4); // {s3, s4}
	DJSet_Union(&s2, &s5); // {s1, s2, s5}

	printf("Strings %s and %s are in the same set: %s\n",
		   s1.str, s2.str, NodesInTheSameSet(&s1, &s2) ? "true" : "false");
	// Strings AAA and BBB are in the same set: true

	printf("Strings %s and %s are in the same set: %s\n",
		   s2.str, s4.str, NodesInTheSameSet(&s2, &s4) ? "true" : "false");
	// Strings BBB and DDD are in the same set: false

	printf("Strings %s and %s are in the same set: %s\n",
		   s1.str, s5.str, NodesInTheSameSet(&s1, &s5) ? "true" : "false");
	// Strings AAA and EEE are in the same set: true
	return 0;
}

static bool NodesInTheSameSet(void *a, void *b)
{
	return DJSet_Find(a) == DJSet_Find(b);
}