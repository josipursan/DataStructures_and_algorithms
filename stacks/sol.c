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


/*
    stack_init()
    push_data()
    pop_data()
    stack_destroy();
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
    struct StackNode *tail;
}StackStructure;

void stack_init(StackStructure *my_stack)
{
    my_stack->size = 0;
    my_stack->head = NULL;
}

void stack_push(StackStructure *my_stack, void *data)   
{
    StackNode *node = malloc(sizeof(StackNode));
    node->data = *data;
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
    while()
    {
        
    }
}

/*
    stack_push();
    stack_pop();
    stack_destroy();
*/


int main()
{
    
    
    return 0;
}