#include <stdlib.h>
#include <stdio.h>

typedef struct s_stack{
    int             value;
    int             min;
    struct s_stack  *prev;
    struct s_stack  *next;
    struct s_stack  *top;
} MinStack;


MinStack* minStackCreate() {
    MinStack    *stack;
    
    stack = (MinStack *)malloc(sizeof(MinStack));
    if (!stack)
        exit(0);
    stack->prev = NULL;
    stack->next = NULL;
    stack->top = stack;
    return (stack);
}

void minStackPush(MinStack* obj, int val) {
    MinStack    *new;
    MinStack    *top;

    top = obj->top;
    new = (MinStack *)malloc(sizeof(MinStack));
    if (!new)
        exit(0);
    new->prev = top;
    new->next = NULL;
    new->value = val;
    if (!obj->next)
        obj->min = val;
    else if (val < obj->min)
        obj->min = val;
    top->next = new;
    obj->top = new;
}

void minStackPop(MinStack* obj) {
    MinStack    *temp;
    int         min2;
    int         val;

    val = obj->top->value;
    temp = obj->top->prev;
    temp->next = NULL;
    printf("%d\n", val);
    free(obj->top);
    obj->top = temp;
    if (obj-> next && val == obj->min)
    {
        temp = obj->next;
        min2 = temp->value;
        while (temp)
        {
            if (temp->value < min2)
                min2 = temp->value;
            temp = temp->next;
        }
        obj->min = min2;
    }
}

int minStackTop(MinStack* obj) {
    return (obj->top->value);
}

int minStackGetMin(MinStack* obj) {
    return (obj->min);
}

void minStackFree(MinStack* obj) {
    MinStack    *temp;

    while (obj->next)
    {
        temp = obj->next;
        free(obj);
        obj = temp;
    }
    free(obj);
}
