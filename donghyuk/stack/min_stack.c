#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
} Node;

typedef struct {
    Node *bottom;
    Node *top;
} MinStack;

Node *createNode(int val){
    Node *new = (Node *)malloc(sizeof(Node));
    new->val = val;
    new->next = NULL;
    return (new);
}

MinStack* minStackCreate() {
    MinStack *stack = (MinStack *)malloc(sizeof(MinStack));
    stack->bottom = NULL;
    stack->top = NULL;
    return (stack);
}

void minStackPush(MinStack* stack, int val) {
    Node *new;

    new = createNode(val);
    if (stack->top == NULL)
    {
        stack->top = new;
        stack->bottom = new;
    }
    else
    {
        stack->top->next = new;
        stack->top = stack->top->next;
    }
}

void minStackPop(MinStack* stack) {
    Node *curr;

    if (stack->bottom == stack->top)
    {
        free(stack->top);
        stack->top = NULL;
        stack->bottom = NULL;
        return ;
    }
    curr = stack->bottom;
    while (curr->next != stack->top)
        curr = curr->next;
    free(stack->top);
    stack->top = curr;
	  stack->top->next = NULL;
}

int minStackTop(MinStack* stack) {
    return (stack->top->val);
}

int minStackGetMin(MinStack* stack) {
    Node *curr;
    int min;

    curr = stack->bottom;
    min = curr->val;
    while (curr)
    {
        if (min > curr->val)
            min = curr->val;
        curr = curr->next;
    }
    return (min);
}

void minStackFree(MinStack* stack) {
    Node *curr;
    Node *tmp;

    curr = stack->bottom;
    while (curr && curr->next != NULL)
    {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(stack);
}
