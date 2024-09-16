#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure for each individual list node
typedef struct ListNode
{
    int value;
    struct ListNode *nextListNode;
}ListNode;

// Structure representing the singly linked list as a whole - keeps track of number of nodes, head node and tail node
typedef struct SinglyLinkedList
{
    int size;
    struct ListNode *head;
    struct ListNode *tail;
}SinglyLinkedList;

void print_list_node_info(ListNode *givenListNode)
{
    printf("address givenListNode: %p\ngivenListNode value : %d\ngivenListNode->next : %p\n", (void*)givenListNode, givenListNode->value, (void*)givenListNode->nextListNode);
}

void removeElement(SinglyLinkedList *singly_linked_list, ListNode *nodeToRemove)
{
    // if nodeToRemove is head of list, move the list head to the element following nodeToRemove, free the nodeToRemove and return
    if(singly_linked_list->head == nodeToRemove)
    {
        singly_linked_list->head = nodeToRemove->nextListNode;
        free(nodeToRemove);
        return;
    }

    ListNode *node_previous_to_nodeToRemove = singly_linked_list->head;//malloc(sizeof(ListNode));
    //node_previous_to_nodeToRemove = singly_linked_list->head;
    while(true)
    {
        if(node_previous_to_nodeToRemove->nextListNode != nodeToRemove)
        {
            node_previous_to_nodeToRemove = node_previous_to_nodeToRemove->nextListNode;
            continue;
        }
        else
        {
            break;
        }
    }

    // if nodeToRemove is list tail, then the node_previous_to_nodeToRemove must be set to point to NULL, and tail variable in SinglyLinkedList must be set to node_previous_to_nodeToRemove
    if(nodeToRemove->nextListNode == NULL)
    {
        singly_linked_list->tail = node_previous_to_nodeToRemove;
        node_previous_to_nodeToRemove->nextListNode = NULL;
    }
    else     // otherwise, if nodeToRemove is just a random node in the middle, ...
    {
        node_previous_to_nodeToRemove->nextListNode = nodeToRemove->nextListNode;   // pointing node_previous_to_nodeToRemove to the node that follows nodeToRemove
    }
    free(nodeToRemove);
}

/* removeElement()
insertNextElement()
insertElement()
destroyList() */


int main()
{
    // Let's try and create 3 list nodes, and populate their value fields
    ListNode *n3 = malloc(sizeof(ListNode));
    n3->value = 3;
    n3->nextListNode = NULL;    // Why is the last node pointing to NULL? Because it is the last node in signly linked list - it is the end.

    ListNode *n2 = malloc(sizeof(ListNode));
    n2->value = 2;
    n2->nextListNode = n3;

    ListNode *n1 = malloc(sizeof(ListNode));
    n1->value = 1;
    n1->nextListNode = n2;

    // Now we will create the structure representing the singly linked list and populate it with necessary information
    SinglyLinkedList *singly_linked_list = malloc(sizeof(SinglyLinkedList));
    singly_linked_list->size = 3;
    singly_linked_list->head = n1;
    singly_linked_list->tail = n3;

    // These prints are to check that all addresses are ok, and that nodes actually do point to the following node in list
    print_list_node_info(n1);
    print_list_node_info(n2);
    print_list_node_info(n3);

    printf("Lets check head and tail\t head : %p  tail : %p", (void*)singly_linked_list->head, (void*)singly_linked_list->tail);

    // Let us now try and access the value of n2 via n1
    /* ListNode *nextNode = malloc(sizeof(ListNode));
    nextNode = n1->nextListNode;
    printf("\nAccessing node following n1 via n1->nextListNode\n");
    print_list_node_info(nextNode);
    free(nextNode); */


    // Now we will remove the n2 node, leaving only n1 and n3
    removeElement(singly_linked_list, n2);
    printf("\n\n\nLets check out how n1 and n2 look now : \n");
    print_list_node_info(n1);
    print_list_node_info(n3);
    printf("And lets check head and tail\t head : %p  tail : %p\n", (void*)singly_linked_list->head, (void*)singly_linked_list->tail);
    // if we try to access n2, junk values get printed because this memory address has been freed
    //print_list_node_info(n2);

    free(singly_linked_list);
    free(n1);
    free(n3);
    return 0;
}