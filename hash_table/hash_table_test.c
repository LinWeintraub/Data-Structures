/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          28/10/22                                        ~
 * Description   Hash Table                                      *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdio.h> /* printf */
#include <ctype.h>
#include <string.h> 
#include <assert.h> /* assert */
#include <stdlib.h>

#include "hash_table.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

#define ASCII_SIZE 256

int HashTableSpellChecker(const hash_table_t *dictionary, const char *word);

void TestHashCreate(void);
void TestRemoveFind(void);
void TestInsertSize(void);
void TestForeach(void);
void TestDict(void);

int IsMatchString(const void *key_1, const void *key_2);
size_t HashFunction(const void *key);
int Print(void *param, void *value);
static int FreeMemory(void *param, void *value);

int main(void)
{
    TestHashCreate();
    TestInsertSize();
    TestRemoveFind();
    TestForeach();

    TestDict();

	return 0;
}

void TestHashCreate(void)
{
    hash_table_t *table = HashTableCreate(10, HashFunction, IsMatchString);

	printf("----------Create & IsEmpty test:----------\n");

    TEST("HashTableCreate", (table != NULL), 1);
    TEST("HashTableIsEmpty", HashTableIsEmpty(table), 1);

    HashTableDestroy(table);
}

void TestRemoveFind(void)
{
    hash_table_t *table = HashTableCreate(10, HashFunction, IsMatchString);

    char data[] = "LIN";
    char key[] = "LIN";
    char bla[] = "hi";

    HashTableInsert(table, key, data);

    TEST("Find Test 1", HashTableFind(table, key), data);
    TEST("Find Test 2", HashTableFind(table, bla), NULL);
    TEST("Size test - 1", HashTableSize(table), 1);

    HashTableRemove(table, key);

    TEST("Remove test 1", HashTableFind(table, key), NULL);
    TEST("Size test - 0", HashTableSize(table), 0);

    HashTableDestroy(table);
}

size_t HashFunction(const void *key)
{
    char *first_char_ptr = (void *) key;
    int first_char = tolower((int)*first_char_ptr) - 'a';

    return first_char;
}

int IsMatchString(const void *key_1, const void *key_2)
{
    return(!strcmp((char *)key_1, (char *)key_2));
}

int Print(void *param, void *value)
{
    (void)param;
    printf("%s \n", (char *)value);

    return 0;
}

void TestInsertSize(void)
{
    hash_table_t *table = HashTableCreate(10, HashFunction, IsMatchString);

    char data[] = "LIN";
    char data_1[] = "LIN_1";
    char key[] = "LIN";

	printf("----------Size & IsEmpty test:----------\n");

    TEST("Size test - 0", HashTableSize(table), 0);
    TEST("IsEmpty test - 1", HashTableIsEmpty(table), 1);

    HashTableInsert(table, key, data);

    TEST("Size test - 1", HashTableSize(table), 1);
    TEST("IsEmpty test - 0", HashTableIsEmpty(table), 0);

    HashTableInsert(table, key, data_1);
    
    TEST("Size test - 2", HashTableSize(table), 2);
    TEST("IsEmpty test - 0", HashTableIsEmpty(table), 0);

    HashTableDestroy(table);
}

void TestForeach(void)
{
    hash_table_t *table = HashTableCreate(10, HashFunction, IsMatchString);

    char data[] = "LIN";
    char data_1[] = "LIN_1";
    char key[] = "LIN";
    int one = 1;

    HashTableInsert(table, key, data);
    HashTableInsert(table, key, data_1);
    HashTableInsert(table, "haha", "haha");
    HashTableInsert(table, "blibla", "blibla");
    HashTableInsert(table, "dov", "dov");
    HashTableInsert(table, "kuala", "kuala");

	printf("----------ForEach test:----------\n");
    HashTableForEach(table, Print, &one);

    HashTableRemove(table,"kuala");

	printf("----------ForEach test after removed kuala:----------\n");
    HashTableForEach(table, Print, &one);

    HashTableDestroy(table);
}

hash_table_t *CreateDict(void)
{
    hash_table_t *dictionary = HashTableCreate(ASCII_SIZE, HashFunction, IsMatchString);

    char buff[ASCII_SIZE] = {0};
    char *str = NULL;

    FILE *dictionary_file = fopen("/usr/share/dict/words", "r");

    while (fgets(buff, ASCII_SIZE, dictionary_file)) 
    {
        buff[strcspn(buff, "\n")] = '\0';

        str = malloc(strlen(buff) + 1); 
        if (NULL == str)
        {
            HashTableDestroy(dictionary);
            return NULL;
        }

        strcpy(str, buff);

        if (SUCCESS != HashTableInsert(dictionary, str, str))
        {
            HashTableDestroy(dictionary);
            return NULL;
        }
    }

    fclose(dictionary_file);

    return(dictionary);
}

int HashTableSpellChecker(const hash_table_t *dictionary, const char *word)
{
    assert(dictionary);
    return (HashTableFind((hash_table_t *)dictionary, (char *)word) ? 1 : 0); 
}

void TestDict(void)
{
    hash_table_t *dictionary = CreateDict();

	printf("----------Spell Check Test:----------\n");

    TEST("hello", HashTableSpellChecker(dictionary, "hello"), 1);
    TEST("kimottti", HashTableSpellChecker(dictionary, "kimottti"), 0);
    TEST("zoo", HashTableSpellChecker(dictionary, "zoo"), 1);
    TEST("zebra", HashTableSpellChecker(dictionary, "zebra"), 1);
    TEST("car", HashTableSpellChecker(dictionary, "car"), 1);
    TEST("cxerrz", HashTableSpellChecker(dictionary, "cxerrz"), 0);

    HashTableForEach(dictionary, FreeMemory,(void *)NULL);

    HashTableDestroy(dictionary);
}

static int FreeMemory(void *param, void *value)
{
    free(value);
    value = NULL;
    (void)param;
    return 0;
}
