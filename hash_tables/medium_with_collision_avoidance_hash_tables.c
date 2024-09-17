#include <stdio.h>
#include <stdlib.h>

typedef struct HashTable
{
    int key;
    int value;
}HashTable;

typedef struct ListNode
{
    HashTable *hashTableElement;
    ListNode *nextNode;
}ListNode;

int hashing_algorithm(int key, int array_size)
{
    return (key % array_size);
}

void insert_element()
{

}



int main()
{
    int arr_size = 10;
    ListNode **hash_table = (ListNode*)malloc(10*sizeof(ListNode));
    




    return 0;
}