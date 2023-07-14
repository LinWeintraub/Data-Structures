/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          28/10/22                                        ~
 * Description   Hash Table                                      *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "hash_table.h"
#include "dll.h"

/*----------------------------------------------------------------------------*/
typedef struct key_value
{
    void *key;
    void *value;
} pair_t;

struct hash_table
{
    size_t buckets_amount;
    hash_func_t hash_func_p;
    is_match_func_t is_match_func_p;
    dll_t **buckets;
};

/*---------------------------Function Declarations----------------------------*/
static dll_t **BucketsInit(hash_table_t *table, dll_t **buckets, size_t capacity);
static size_t GetHashIndex(hash_table_t *table, void *key);
static int FreePair(void *param, void *value);
int PairForEach(dll_t *bucket, action_t action_func, void *param);

/*---------------------------------API-Functions------------------------------*/
hash_table_t *HashTableCreate(size_t capacity,
                              hash_func_t hash_func_p,
                              is_match_func_t is_match_func_p)
{
    hash_table_t *hash_table = malloc(sizeof(hash_table_t));
    dll_t **buckets = malloc(capacity * sizeof(dll_t *));
    if (NULL == hash_table || NULL == buckets)
    {
        free(hash_table);
        free(buckets);
        return NULL;
    }

    assert(capacity);
    assert(hash_func_p);
    assert(is_match_func_p);

    buckets = BucketsInit(hash_table, buckets, capacity);
    if (NULL == buckets)
    {
        free(buckets);
        return NULL;
    }

    hash_table->buckets_amount = capacity;
    hash_table->hash_func_p = hash_func_p;
    hash_table->is_match_func_p = is_match_func_p;
    hash_table->buckets = buckets;

    return hash_table;
}

void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0;
    dll_iterator_t from = NULL;
    dll_iterator_t to = NULL;

    assert(table);

    for (i = 0; i < table->buckets_amount; ++i)
    {
        from = DListIteratorFirst(table->buckets[i]);
        to = DListIteratorEnd(table->buckets[i]);

        if (1 != DListIsEmpty(table->buckets[i]))
        {
            DListForEach(from, to, &FreePair, &i);
        }

        DListDestroy(table->buckets[i]);
    }

    free(table->buckets); table->buckets = NULL;
    free(table); table = NULL;
}

status_t HashTableRemove(hash_table_t *table, const void *key)
{
    dll_iterator_t from = NULL;
    dll_iterator_t to = NULL;
    size_t index = 0;
    pair_t *remove_pair = NULL;

    assert(table);
    assert(key);

    index = GetHashIndex(table, (void *)key);
    from = DListIteratorFirst(table->buckets[index]);
    to = DListIteratorEnd(table->buckets[index]);

    while (!DListIsIterEqual(from, to))
    {
        remove_pair = DListGetValue(from);

        if (1 == table->is_match_func_p(remove_pair->key, (void *)key))
        {
                FreePair((void *)key, remove_pair);
                DListRemove(from);
                return SUCCESS;
        }

        from = DListIteratorNext(from);
    }

    return FAILURE;
}

status_t HashTableInsert(hash_table_t *table, const void *key, void *value)
{
    size_t index = 0;
    pair_t *pair = malloc(sizeof(pair_t));
    dll_iterator_t result = 0;

    if (NULL == pair)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    assert(table);
    assert(key);

    pair->key = (void *)key;
    pair->value = (void *)value;

    index = GetHashIndex(table, (void *)key);

    result = DListPushFront(table->buckets[index], pair);
    if (NULL == result)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    return SUCCESS;
}

size_t HashTableSize(const hash_table_t *table)
{
    size_t i = 0;
    size_t counter = 0;

    assert(table);

    for (i = 0; i < table->buckets_amount; ++i)
    {
        counter += DListSize(table->buckets[i]);
    }

    return counter;
    (void)table;
}

int HashTableIsEmpty(const hash_table_t *table)
{
    size_t i = 0;

    assert(table);

    for (i = 0; i < table->buckets_amount; ++i)
    {
        if (!DListIsEmpty(table->buckets[i]))
        {
            return 0;
        }
    }

    return 1;
}

void *HashTableFind(const hash_table_t *table, const void *key)
{
    dll_iterator_t from = NULL;
    dll_iterator_t to = NULL;
    pair_t *find_value = NULL;
    size_t index = 0;

    assert(table);

    index = GetHashIndex((hash_table_t *)table, (void *)key);

    from = DListIteratorFirst(table->buckets[index]);
    to = DListIteratorEnd(table->buckets[index]);
    
    while (!DListIsIterEqual(from, to))
    {
        find_value = DListGetValue(from);
        if (1 == table->is_match_func_p((void *)key, find_value->key))
        {
            return find_value->value;
        }

        from = DListIteratorNext(from);
    }

    return NULL;
}

int HashTableForEach(hash_table_t *table,
                     int (*action_func)(void *value, void *param),
                     void *param)
{
    size_t i = 0;
    int status = 0;

    assert(table);
    assert(action_func);

    for (i = 0; i < table->buckets_amount; ++i)
    {
        status = PairForEach(table->buckets[i], action_func, param);
        if (SUCCESS != status)
        {
            return FAILURE;
        }
    }
       
	return SUCCESS;
}

/*------------------------------Static-Functions------------------------------*/
static dll_t **BucketsInit(hash_table_t *table, dll_t **buckets, size_t capacity)
{
    size_t i = 0;

    assert(table);
    assert(buckets);
    assert(capacity);

    for (i = 0; i < capacity; ++i)
    {
        buckets[i] = DListCreate();

        if (NULL == buckets)
        {
            HashTableDestroy(table); table = NULL;
            return NULL;
        }
    }

    return buckets;
}

static size_t GetHashIndex(hash_table_t *table, void *key)
{
    return (table->hash_func_p(key) % table->buckets_amount);
}

static int FreePair(void *param, void *value)
{
    free(value);
    value = NULL;
    (void)param;
    return 0;
}

int PairForEach(dll_t *bucket, action_t action_func, void *param)
{
	int status = 0;
	dll_iterator_t from = NULL;
    dll_iterator_t to = NULL;
    pair_t *pair = NULL;

	assert(bucket);
	assert(action_func);

    from = DListIteratorFirst(bucket);
    to = DListIteratorEnd(bucket);
	
    for (; from != to; from = DListIteratorNext(from))
								
    {
        pair = DListGetValue(from); 
        status = action_func(param, pair->value);

        if (0 != status)
        {
            return FAILURE;
        }
    }
       
	return SUCCESS;
}
