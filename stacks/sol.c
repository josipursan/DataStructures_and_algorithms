#include <stdio.h>
#include <stdlib.h>

/*
    Stacks - LIFO structures
        -LIFO - Last In First Out
        -whatever gets stored last on the stack, gets pulled out first
        -comparable to a can of tennis balls - Last In is the top ball, meaning it gets First Out
        
        -elements are added by pushing them to the top of stack (ie. singly linked list HEAD)
        -elements are taken out (popped) from the top of stack as well

        -quite similar to singly_linked lists, with the exception of tail - tail indicator can be dropped because we care only about the stack head
*/

typedef struct StackNode
{
    int data;

    struct StackNode *nextNode;
}StackNode;

typedef struct StackStructure
{
    int size;

    struct StackNode *head;
}StackStructure;

void stack_init(StackStructure *my_stack)
{
    my_stack->size = 0;
    my_stack->head = NULL;
}

void stack_push(StackStructure *my_stack, void *data)      // This void for data also wasn't necessary considering this is the simple example where we don't have to malloc space for data
{
    StackNode *node = malloc(sizeof(StackNode));
    node->data = *((int*)data);
    node->nextNode = my_stack->head;
    my_stack->head = node;
    my_stack->size += 1;
}

void stack_pop(StackStructure *my_stack)
{
    StackNode *nodeToRemove = my_stack->head;
    my_stack->head = nodeToRemove->nextNode;    //moving the StackStructure->head to point to the node following current node because we are about to remove the HEAD node
    free(nodeToRemove);
    my_stack->size -= 1;
}

void stack_destroy(StackStructure *my_stack)
{
    if(my_stack->size <= 0)
    {
        printf("Stack has no elements, or stack size has been improperly set : %d\n", my_stack->size);
        exit(-1);
    }
    while(my_stack->size > 0)   // while there still are some stacked elements, ...
    {
        StackNode *currentNode = my_stack->head;
        my_stack->head = currentNode->nextNode;
        my_stack->size -= 1;
        free(currentNode);
    }
}

void peek_stack_head(StackStructure *my_stack)
{
    // Realistically this additional local pointer was not necessary, you could've done my_stack->head->data, my_stack->head->nextNode, ...., but hey, this looks maybe a bit cleaner.
    StackNode *stack_head = my_stack->head;
    printf("Stack head : %p\nNode data : %d\nNext node : %p\n", (void*)stack_head, stack_head->data, stack_head->nextNode);
}

int main()
{
    return 0;
}