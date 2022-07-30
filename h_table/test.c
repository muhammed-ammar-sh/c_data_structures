#include <stdio.h>
#include <string.h>
#include "h_table.h"

/// @brief returns true if the given strings are the same
bool AreStrsEqual(const void *a, const void *b)
{
	return strcmp((const char *)a, (const char *)b) == 0;
}

static void AddName(h_table_t *phone_book, const char *name, uint32_t number);
static void FindName(h_table_t *phone_book, const char *query_name);
static void RemoveName(h_table_t *phone_book, const char *name);

int main(void)
{
	h_table_t phone_book;
	HTable_InitTable(&phone_book, 100, AreStrsEqual, DefaultHashStr, NULL);

	AddName(&phone_book, "John", 11111);
	AddName(&phone_book, "Bill", 22222);
	AddName(&phone_book, "Anna", 33333);
	AddName(&phone_book, "Victoria", 44444);

	FindName(&phone_book, "John");
	// John name is found in the phone book
	// His/Her phone number is: 11111

	FindName(&phone_book, "Anna");
	// Anna name is found in the phone book
	// His/Her phone number is: 33333
	
	FindName(&phone_book, "Noah");
	// Noah name is not found in the phone book

	// Update John number
	AddName(&phone_book, "John", 99999);
	FindName(&phone_book, "John");
	// John name is found in the phone book
	// His/Her phone number is: 99999

	RemoveName(&phone_book, "John");
	FindName(&phone_book, "John");
	// John name is not found in the phone book

	HTable_DeinitTable(&phone_book);
	return 0;
}

static void AddName(h_table_t *phone_book, const char *name, uint32_t number)
{
	HTable_Insert(phone_book, name, strlen(name), &number, sizeof(number));
}

static void FindName(h_table_t *phone_book, const char *name)
{
	bool found = HTable_Find(phone_book, name);
	printf("%s name is %s in the phone book\n", name, found ? "found" : "not found");
	if (found)
	{
		uint32_t *number = HTable_GetValue(phone_book, name);
		printf("His/Her phone number is: %d\n", *number);
	}
}

static void RemoveName(h_table_t *phone_book, const char *name)
{
	HTable_Remove(phone_book, name);
}