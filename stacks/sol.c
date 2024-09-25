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
    if(my_stack->size <= 0) // if there are no elements in stack, it means the current node we are adding will be at the bottom, thus there are no nodes after it
    {
        node->nextNode = NULL;
    }
    else
    {
        node->nextNode = my_stack->head;
    }
    my_stack->head = node;
    my_stack->size += 1;
}

void stack_pop(StackStructure *my_stack)
{
    if(my_stack->size <= 0)
    {
        printf("No elements in stack to pop!\nStack size : %d\n", my_stack->size);
        exit(0);
    }
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

void node_data(StackNode *givenNode)
{
    printf("givenNode addr:  %p\ngivenNode data : %d\ngivenNode nextNode : %p\n\n", givenNode, givenNode->data, (void*)givenNode->nextNode);
}

int main()
{
    StackStructure *stack_structure = malloc(sizeof(StackStructure));
    stack_init(stack_structure);
    printf("And this is the stack_structure after init\nstack_structure : %p\nstack_structure->size : %d\nstack_structure->head : %p\n\n", (void*)stack_structure, stack_structure->size, (void*)stack_structure->head);
    
    int n1 = 1; // imagine this is some woo-woo highly complex data you need to pass (later implementation will have malloced data, probably malloced inside some struct)
    int n2 = 2;
    int n3 = 3;

    stack_push(stack_structure, (void*)&n1);
    stack_push(stack_structure, (void*)&n2);
    stack_push(stack_structure, (void*)&n3);
    printf("stack_structure after pushing all 3 nodes\nstack_structure : %p\nstack_structure->size : %d\nstack_structure->head : %p\n\n", (void*)stack_structure, stack_structure->size, (void*)stack_structure->head);

    // Let's check out stack head now using peek_stack_head()
    printf("\npeek_stack_head(stack_structure) : \n");
    peek_stack_head(stack_structure);

    printf("\n========================================================================\n");
    printf("\nNow let's try navigating through the stack, starting from the head\n\n");
    printf("stack_head : %p\nhead data : %d\nhead->nextNode : %p\n\n", (void*)stack_structure->head, stack_structure->head->data, (void*)stack_structure->head->nextNode);
    printf("node after head : %p\ndata : %d\nnextNode : %p\n\n", (void*)stack_structure->head->nextNode, stack_structure->head->nextNode->data, (void*)stack_structure->head->nextNode->nextNode);
    printf("probably last node : %p\ndata : %d\nnextNode : %p\n\n", (void*)stack_structure->head->nextNode->nextNode, stack_structure->head->nextNode->nextNode->data, (void*)stack_structure->head->nextNode->nextNode->nextNode);

    printf("\n========================================================================\n");
    printf("Now let's pop the stack head!\n");
    stack_pop(stack_structure);
    printf("And verify by checking out the stack head\n");
    peek_stack_head(stack_structure);
    printf("\nstack_head : %p\nhead data : %d\nhead->nextNode : %p\n\n", (void*)stack_structure->head, stack_structure->head->data, (void*)stack_structure->head->nextNode);
    printf("node after head : %p\ndata : %d\nnextNode : %p\n\n", (void*)stack_structure->head->nextNode, stack_structure->head->nextNode->data, (void*)stack_structure->head->nextNode->nextNode);
    
    printf("\n========================================================================\n");
    printf("Last, but not least, stack_destroy()\n");
    stack_destroy(stack_structure);
    //peek_stack_head(stack_structure);     // if uncomment this line, execution will segfault because there is nothing to peek at
    printf("stack_structure : %p\nstack_structure->size : %d\nstack_structure->head : %p\n\n", (void*)stack_structure, stack_structure->size, (void*)stack_structure->head);    // this will return 0 for size and nil for head
    return 0;
}