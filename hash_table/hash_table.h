#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#include <stddef.h> /* size_t */

typedef struct hash_table hash_table_t;
typedef int (*is_match_func_t)(const void *key_1, const void *key_2);
typedef size_t (*hash_func_t)(const void *key);

typedef enum 
{
	SUCCESS = 0,
	FAILURE = 1,
    MEMORY_ALLOCATION_ERROR = 2
} status_t;   

/*----------------------------------------------------------------------------
Params: capacity - lenght of dll array
        hash_func_p - pointer to the hash function,
        is_match_func_p - match function to compare and match keys in the hash table.
Return: A hash_table_t type pointer to the struct if succeeds, NULL if fails.
Complexity: O(1) or O(capacity) 
*/
hash_table_t *HashTableCreate(size_t capacity, 
                              hash_func_t hash_func_p, 
                              is_match_func_t is_match_func_p);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table
Return: -  
Complexity: O(n), where n is the total number of entries in the hash table. 
*/
void HashTableDestroy(hash_table_t *table);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table.
        key - unique identifier of the entry which will be removed.
Return: SUCCESS when the entry has been removed. 
        FAILURE if the entry couldn't be located and removed.  
Complexity: Average case O(1). Worst case O(n).
*/
status_t HashTableRemove(hash_table_t *table, const void *key);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table.
        key - unique identifier of the entry which will be inserted.
        value - the data which will be stored.
Return: SUCCESS when key added to hash tavle. 
        MEMORY_FAILURE fail to alocate memory for the entry. 
Complexity: Average case O(1). Worst case O(n).
*/
status_t HashTableInsert(hash_table_t *table, const void *key, void *value);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table
Return: The total number of entries in the hash table. 
Complexity: O(n) 
*/
size_t HashTableSize(const hash_table_t *table);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table
Return: 1 if hash table is empty, else 0.
Complexity: O(n) 
*/
int HashTableIsEmpty(const hash_table_t *table);

/*----------------------------------------------------------------------------
Params: hash_table_t type ptr to the table
        key - unique identifier of the entry which will be inserted.
Return: value of key in hash table.
        NULL if key not found.
Complexity: Average case O(1). Worst case O(n).
*/
void *HashTableFind(const hash_table_t *table, const void *key);

/*----------------------------------------------------------------------------*/
/*
	Params: hash_table_t type ptr to the table.
	action_func - function pointer to the action to perform.
	param - void pointer to the parameter to use in the action.
    Return: SUCCESS when key added to hash tavle. 
            MEMORY_FAILURE fail to alocate memory for the entry. 
	Complexity: O(n).
*/
int HashTableForEach(hash_table_t *table,
                        int (*action_func)(void *value, void *param),
                        void *param);

/*-------------------------------Advanced-------------------------------------*/
/*
	Params: hash_table_t type ptr to the table.
	Return: The table's SD value. 
	Complexity: O(1)
*/
double HashTableStandardDeviation(const hash_table_t *table);

/*
	Params: hash_table_t type ptr to the table.
	Return: The table's load factor. 
	Complexity: O(1)
*/
double HashTableLoadFactor(const hash_table_t *table);

/* caching insert */

#endif /* __HASH_TABLE__ */

/* test file */
/*
	Params: hash_table_t type ptr to the dicionary, word is the word we wish to spell check.
	Return: whether the word is spelled correctly or not;
	Complexity: O(1) average case, O(n) worst case.
*/
int HashTableSpellChecker(const hash_table_t *dictionary, const char *word);
