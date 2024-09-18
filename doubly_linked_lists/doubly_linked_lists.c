#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    struct ListNode *previousNode;
    int data;
    struct ListNode *nextNode;
}ListNode;

typedef struct DoublyLinkedList
{
    int size;

    struct ListNode *head;
    struct ListNode *tail;
}DoublyLinkedList;

// addElement() adds nodes to the end of list, ie after the current tail node
void addElement(DoublyLinkedList *doubly_linked_list, ListNode *nodeToAdd)
{
    nodeToAdd->previousNode = doubly_linked_list->tail; //the current tail node of list is the previous node for nodeToAdd
    doubly_linked_list->tail->nextNode = nodeToAdd; //because the current tail's nextNode is pointing to NULL, and we will add nodeToAdd after it, we must point this old tail to the new tail
    nodeToAdd->nextNode = NULL;
    doubly_linked_list->tail = nodeToAdd;
    doubly_linked_list->size += 1;
}

// insertNextElement() inserts nodeToAdd after currentNode
void insertNextElement(DoublyLinkedList *doubly_linked_list, ListNode *nodeToAdd, ListNode *currentNode)
{
    if(currentNode->nextNode == NULL)   // if currentNode (the node after which we will add our new node) is tail, call addElement()
    {
        addElement(doubly_linked_list, nodeToAdd);
        return;
    }

    nodeToAdd->previousNode = currentNode;
    nodeToAdd->nextNode = currentNode->nextNode;
    currentNode->nextNode = nodeToAdd;
    nodeToAdd->nextNode->previousNode = nodeToAdd;
    doubly_linked_list->size += 1;
}

// insertPreviousElement() inserts nodeToAdd before currentNode
void insertPreviousElement(DoublyLinkedList *doubly_linked_list, ListNode *nodeToAdd, ListNode *currentNode)
{
    if(currentNode->previousNode == NULL)    //if currentNode is head, nodeToAdd will become the new head
    {
        doubly_linked_list->head = nodeToAdd;
        nodeToAdd->nextNode = currentNode;
        nodeToAdd->previousNode = NULL;
        currentNode->previousNode = nodeToAdd;
        return;
    }

    nodeToAdd->previousNode = currentNode->previousNode;
    currentNode->previousNode = nodeToAdd;
    nodeToAdd->previousNode->nextNode = nodeToAdd;
    nodeToAdd->nextNode = currentNode;
    doubly_linked_list->size += 1;
}

// addToHead() makes the given node new list head
void addToHead(DoublyLinkedList *doubly_linked_list, ListNode *nodeToAdd)
{
    nodeToAdd->previousNode = NULL;
    nodeToAdd->nextNode = doubly_linked_list->head;
    nodeToAdd->nextNode->previousNode = nodeToAdd;
    doubly_linked_list->head = nodeToAdd;
    doubly_linked_list->size += 1;
}

// removeElement() removes the node it was given
void removeElement(DoublyLinkedList *doubly_linked_list, ListNode *nodeToRemove)
{
    doubly_linked_list->size -= 1;
    if(nodeToRemove->nextNode == NULL)  // if nodeToRemove is list tail
    {
        doubly_linked_list->tail = nodeToRemove->previousNode;
        nodeToRemove->previousNode->nextNode = NULL;
        free(nodeToRemove);
        return;
    }

    if(nodeToRemove->previousNode == NULL)  // if nodeToRemove is list head
    {
        doubly_linked_list->head = nodeToRemove->nextNode;
        nodeToRemove->nextNode->previousNode = NULL;
        free(nodeToRemove);
        return;
    }

    nodeToRemove->previousNode->nextNode = nodeToRemove->nextNode;
    nodeToRemove->nextNode->previousNode = nodeToRemove->previousNode;
    free(nodeToRemove);
}

// removeNextElement() removes node which follows currentNode
void removeNextElement(DoublyLinkedList *doubly_linked_list, ListNode *currentNode)
{
    if(currentNode->nextNode == NULL)   // if currentNode is list tail, there are no more elements after it for removal
    {
        printf("Given node is list tail!\nNo more elements after it for removal\n");
        return;
    }

    ListNode *nodeToRemove = currentNode->nextNode; // this is the node we want to remove
    currentNode->nextNode = nodeToRemove->nextNode;
    currentNode->nextNode->previousNode = currentNode;
    free(nodeToRemove);
    doubly_linked_list->size -= 1;
}

// removePreviousElement() removes node preceding currentNode
void removePreviousElement(DoublyLinkedList *doubly_linked_list, ListNode *currentNode)
{
    if(currentNode->previousNode == NULL)   // if currentNode is list head
    {
        printf("Given node is list head!\nThere are no elements before it for removal!\n");
        return;
    }

    ListNode *nodeToRemove = currentNode->previousNode;
    nodeToRemove->previousNode->nextNode = currentNode;
    currentNode->previousNode = nodeToRemove->previousNode;
    free(nodeToRemove);
    doubly_linked_list->size -= 1;
}

void print_node_contents(ListNode *nodeToPrint)
{
    printf("nodeToPrint address : %p\nnodeToPrint data : %d\nnodeToPrint previous node : %p\nnodeToPrint nextNode : %p\n\n", (void*)nodeToPrint, nodeToPrint->data, (void*)nodeToPrint->previousNode, (void*)nodeToPrint->nextNode);
}

int main()
{
    ListNode *arr[3];   // unimportant, just used to mess around a bit with storing pointers to structs in one location, and later accessing these structs using arr[i]->data = ...;

    // create 3 nodes
    ListNode *n1 = malloc(sizeof(ListNode));
    ListNode *n2 = malloc(sizeof(ListNode));
    ListNode *n3 = malloc(sizeof(ListNode));

    //create list struct
    DoublyLinkedList *doubly_linked_list = malloc(sizeof(DoublyLinkedList));

    // populate their fields and connect them
    n1->data = 1;
    n1->previousNode = NULL; //head
    n1->nextNode = n2;

    n2->data = 2;
    n2->previousNode = n1;
    n2->nextNode = n3;

    n3->data = 3;
    n3->previousNode = n2;
    n3->nextNode = NULL; //tail

    doubly_linked_list->size = 3;
    doubly_linked_list->head = n1;
    doubly_linked_list->tail = n3;

    // add pointer to structs to array of pointers
    arr[0] = n1;
    arr[1] = n2;
    arr[2] = n3;

    // Let's check whether everything is ok
    print_node_contents(n1);
    print_node_contents(n2);
    print_node_contents(n3);
    printf("List size : %d\nList head : %p\nList tail : %p\n", doubly_linked_list->size, doubly_linked_list->head, doubly_linked_list->tail);
    printf("arr[0] : %p\narr[1] : %p\narr[2] : %p\n\n", (void*)arr[0], (void*)arr[1], (void*)arr[2]);

    // Let's now try and jump between nodes using their addresses
    ListNode *previousNode = n2->previousNode;  // we are expecting n1 here because we stored n2->previousNode (which is n1)
    printf("This will print n1 contents\n");
    print_node_contents(previousNode);
    ListNode *followingNode = n2->nextNode; // we are expecting n3 here because we stored n2->nextNode (which is n3)
    printf("This will print n3 contents\n");
    print_node_contents(followingNode);

    // Let's try jumping from n1 to n3 by skipping n2
    ListNode *jumpTon3 = n1->nextNode->nextNode;
    printf("This will also print n3 contents because we did n1->nextNode->nextNode\n");
    print_node_contents(jumpTon3);

    // Now we will test addElement()
    /* ListNode *nodeToAdd = malloc(sizeof(ListNode));
    nodeToAdd->data = 4;
    addElement(doubly_linked_list, nodeToAdd);
    print_node_contents(nodeToAdd);
    printf("List size : %d\nList head : %p\nList tail : %p\n", doubly_linked_list->size, doubly_linked_list->head, doubly_linked_list->tail);
    printf("Now we will try navigating through all nodes from n1 to n4 after n4 has been added using addElement()\n");
    print_node_contents(n1);
    print_node_contents(n1->nextNode);
    print_node_contents(n1->nextNode->nextNode);
    print_node_contents(n1->nextNode->nextNode->nextNode); */

    /* ListNode *n4 = malloc(sizeof(ListNode));
    n4->data = 4;
    insertNextElement(doubly_linked_list, n4, n2);  // we want to insert n4 after n2 : n1->n2->n4->n3
    printf("List size : %d\nList head : %p\nList tail : %p\n", doubly_linked_list->size, doubly_linked_list->head, doubly_linked_list->tail);
    printf("Added n4 after n2 : \n");
    print_node_contents(n1);
    print_node_contents(n2);
    print_node_contents(n3);
    print_node_contents(n4);
    printf("List size : %d\nList head : %p\nList tail : %p\n", doubly_linked_list->size, doubly_linked_list->head, doubly_linked_list->tail); */

    return 0;
}