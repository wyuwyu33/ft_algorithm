#include<stdlib.h>


typedef struct s_queue{
    int             value;
    struct s_queue  *next;
    struct s_queue  *prev;
} t_queue;

typedef struct s_stack{
    t_queue *front;
    t_queue *rear;
} MyStack;

t_queue *create_queue(int x)
{
    t_queue *new;
    
    new = (t_queue *)malloc(sizeof(t_queue));
    if (!new)
        exit(0);
    new->value = x;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}
    
void    enqueu(MyStack  *stack, t_queue *queue, t_queue *new)
{
    if (queue == stack->front)
    {
        new->prev = stack->front;
        stack->front->next = new;
        stack->front = new;
    }
    else if (queue == stack->rear)
    {
        new->next = stack->rear;
        stack->rear->prev = new;
        stack->rear = new;
    }
}

int dequeu(MyStack  *stack, t_queue *queue)
{
    int     val;
    t_queue *temp;

    val = queue->value;
    if (queue == stack->front)
    {
        temp = stack->front;
        stack->front = stack->front->prev;
        if (stack->front)
            stack->front->next = NULL;
        free(temp);
    }
    else if (queue == stack->rear)
    {
        temp = stack->rear;
        stack->rear = stack->rear->next;
        if (stack->rear)
            stack->rear->prev = NULL;
        free(temp);
    }
    return (val);
}

MyStack* myStackCreate() {
    MyStack *stack;
    
    stack = (MyStack *)malloc(sizeof(MyStack));
    if (!stack)
        exit (0);
    stack->front = NULL;
    stack->rear = NULL;
    return (stack);
}

void myStackPush(MyStack* obj, int x) {
    t_queue *new;
    MyStack *temp;

    new = create_queue(x);
    if (obj->front == NULL || obj->rear == NULL)
    {
        obj->front = new;
        obj->rear = new;
    }
    else
        enqueu(obj, obj->front, new);
}

int myStackPop(MyStack* obj) {
    return (dequeu(obj, obj->front));
}

int myStackTop(MyStack* obj) {
    return (obj->front->value);
}

bool myStackEmpty(MyStack* obj) {
    if (obj->front == NULL || obj->rear == NULL)
        return (true);
    return (false);
}

void myStackFree(MyStack* obj) {
    t_queue *temp1;
    t_queue *temp2;

    temp1 = obj->front;
    while (temp1)
    {
        temp2 = temp1->prev;
        free(temp1);
        temp1 = temp2;
    }
    free(obj);
}
