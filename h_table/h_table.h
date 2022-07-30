#ifndef H_TABLE_H
#define H_TABLE_H

#include "../singly_linked_list/sll.h"
#include <stdint.h>
#include <stdbool.h>

typedef sll_t h_table_array_t;

typedef struct
{
	sll_node_t __node;
	void *key;
	void *value;
} h_table_item_t;

typedef size_t (*h_func_t)(const void *input, const void *func_par);
typedef bool (*are_equal_func_t)(const void *a, const void *b);

#define FOREACH_NODE_IN_H_TABLE(_table, _node)              \
	for (size_t __i = 0; __i < (_table)->table_size; ++__i) \
	SLL_FOREACH_NODE(&((_table)->table_array[__i]), h_table_item_t, (_node))

typedef struct
{
	h_table_array_t *table_array;
	size_t table_size;
	are_equal_func_t are_equal_func;
	h_func_t h_func;
	const void *h_func_par;
} h_table_t;

void HTable_InitTable(h_table_t *table, size_t table_size, are_equal_func_t are_equal_func, h_func_t h_func, const void *h_func_par);
void HTable_DeinitTable(h_table_t *table);
void HTable_Insert(h_table_t *table, const void *key, size_t key_size, const void *value, size_t value_size);
void HTable_Remove(h_table_t *table, const void *key);
void *HTable_GetValue(h_table_t *table, const void *key);
bool HTable_Find(h_table_t *table, const void *key);

/******************************************************************************************************************************************/

typedef struct
{
	unsigned int a, b, prime;
} uint_h_func_par_t;

typedef struct
{
	unsigned int x, prime;
} str_h_func_par_t;

size_t DefaultHashUInt(const void *input, const void *func_par);
size_t DefaultHashStr(const void *input, const void *func_par);

#endif