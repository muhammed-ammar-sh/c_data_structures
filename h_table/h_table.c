#include <string.h>
#include <stdlib.h>
#include "h_table.h"

static h_table_item_t *GetItemFromTable(h_table_t *table, const void *key, size_t *hash_value);

/*
 * Implementation of hash tables here is done using memory allocation in the heap for keys and values
 * It can be done statically also, but I couldn't find an example where it will be useful if it's implemented statically.
 */

/// default unsigned integer hashing function parameters
const static uint_h_func_par_t default_uint_h_func_par = {.a = 34, .b = 2, .prime = 1000000007ul};

/// default string hashing function parameters
const static str_h_func_par_t default_str_h_func_par = {.x = 263, .prime = 1000000007ul};

/**
 * @brief Initializes a h table object
 *
 * @param table pointer to the table object
 * @param table_size size of h table array
 * @param are_equal_func pointer to function that will be used to compare keys
 * @param h_func pointer to keys hashing function, you can use the default hashing functions that are provided
 * @param h_func_par pointer to hashing function parameters,
 * 				     pass NULL if you want to use the default parameters of the default hashing functions
 */
void HTable_InitTable(h_table_t *table, size_t table_size, are_equal_func_t are_equal_func, h_func_t h_func, const void *h_func_par)
{
	if (table == NULL || h_func == NULL || are_equal_func == NULL)
	{
		return;
	}

	table->table_size = table_size;
	// allocate table array
	table->table_array = malloc(sizeof(h_table_array_t) * table_size);
	// initialize all lists in the array
	for (size_t i = 0; i < table_size; ++i)
	{
		SLL_InitList(&table->table_array[i]);
	}
	table->are_equal_func = are_equal_func;
	table->h_func = h_func;
	if (h_func_par != NULL)
	{
		table->h_func_par = h_func_par;
	}
	else // use default parameters for default hashing functions?
	{
		if (h_func == DefaultHashUInt)
		{
			table->h_func_par = (const void *)&default_uint_h_func_par;
		}
		else if (h_func == DefaultHashStr)
		{
			table->h_func_par = (const void *)&default_str_h_func_par;
		}
		else
		{
			table->h_func_par = NULL;
		}
	}
}

///@brief Insert a new key with its value to the table, it updates the value only if the key already exists
void HTable_Insert(h_table_t *table, const void *key, size_t key_size, const void *value, size_t value_size)
{
	if (table == NULL || key_size == 0)
	{
		return;
	}
	size_t hash_value;
	h_table_item_t *item = GetItemFromTable(table, key, &hash_value);
	bool push_item_to_SLL = false;
	if (item == NULL)
	{
		item = malloc(sizeof(h_table_item_t));
		item->key = malloc(key_size);
		memcpy(item->key, key, key_size);
		item->value = NULL;
		push_item_to_SLL = true;
	}
	free(item->value);
	if (value_size == 0)
	{
		item->value = NULL;
	}
	else
	{
		item->value = malloc(value_size);
		memcpy(item->value, value, value_size);
	}
	// don't push existed nodes again to the list
	if (push_item_to_SLL)
		SLL_PushFront(&table->table_array[hash_value], item);
}

void HTable_Remove(h_table_t *table, const void *key)
{
	if (table == NULL)
	{
		return;
	}

	size_t hash_value;
	h_table_item_t *item = GetItemFromTable(table, key, &hash_value);
	if (item != NULL)
	{
		SLL_Erase(&table->table_array[hash_value], item);
		free(item->value);
		free(item->key);
		free(item);
	}
}

void *HTable_GetValue(h_table_t *table, const void *key)
{
	if (table == NULL || key == NULL)
	{
		return NULL;
	}
	h_table_item_t *item = GetItemFromTable(table, key, NULL);
	return item == NULL ? NULL : item->value;
}

bool HTable_Find(h_table_t *table, const void *key)
{
	if (table == NULL || key == NULL)
	{
		return false;
	}
	return GetItemFromTable(table, key, NULL) != NULL;
}

/**
 * @brief returns a pointer to an item from table object according to a given key
 *         and returns the hash value of the key through return_hash_value pointer
 */
static h_table_item_t *GetItemFromTable(h_table_t *table, const void *key, size_t *return_hash_value)
{

	size_t hash_value = table->h_func(key, table->h_func_par) % table->table_size;
	if (return_hash_value != NULL)
	{
		*return_hash_value = hash_value;
	}

	SLL_FOREACH_NODE(&table->table_array[hash_value], h_table_item_t, item)
	{
		if (table->are_equal_func(key, item->key))
		{
			return item;
		}
	}
	return NULL;
}

void HTable_DeinitTable(h_table_t *table)
{
	if (table == NULL)
	{
		return;
	}

	FOREACH_NODE_IN_H_TABLE(table, n)
	{
		free(n->key);
		free(n->value);
		free(n);
	}
	free(table->table_array);
	table->table_size = 0;
}

/***********************************************************************************************/

///@brief default implementation of unsigned integer hashing function
size_t DefaultHashUInt(const void *input, const void *func_par)
{
	uint_h_func_par_t *par = (uint_h_func_par_t *)func_par;
	return (((par->a * (*(const unsigned int *)input)) + par->b) % par->prime);
}

///@brief default implementation of string hashing function
size_t DefaultHashStr(const void *input, const void *func_par)
{
	const char *str = (char *)input;
	size_t str_len = strlen(str);
	str_h_func_par_t *par = (str_h_func_par_t *)func_par;

	size_t hash = 0;
	for (int i = str_len - 1; i >= 0; --i)
	{
		hash = (hash * par->x + str[i]) % par->prime;
	}
	return hash;
}