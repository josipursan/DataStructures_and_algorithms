/*
    This file contains C implementation of hash tables found at :
        https://medium.com/@theodoretsori/a-beginners-guide-to-hash-tables-in-c-concept-implementation-and-use-cases-7ea0609d918c

    This implementation is the most basic implementation - no collision handling is present.
    
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct HashTable
{
    int key;
    int value;
}HashTable;

HashTable hash_table[MAX_SIZE];

int hashing_function(int key)
{
    return key % MAX_SIZE;
}

void insert(int key, int value)
{
    int index = hashing_function(key);
    hash_table[index].key = key;
    hash_table[index].value = value;
}

int retrieve(int key)
{
    int index = hashing_function(key);
    return hash_table[index].value;
}

int main()
{
    int i = 0;

    for(i; i<101; i++)
    {
        insert(i, 2*i);
    }

    for(i = 0; i<101; i++)
    {
        printf("key : %d\nvalue : %d\n\n", i, retrieve(i));
    }
}