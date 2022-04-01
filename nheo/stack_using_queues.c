#include<stdlib.h>

//큐 정의
typedef struct s_queue{
    int             value;
    struct s_queue  *next;
    struct s_queue  *prev;
} t_queue;

//스택에 양방향 큐 정의
typedef struct s_stack{
    t_queue *front;
    t_queue *rear;
} MyStack;

//큐 생성 함수
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

//큐에 넣는 함수(front에 넣기, rear에 넣기)
void    enqueu(MyStack  *stack, t_queue *queue, t_queue *new)
{
		//인자로 받은 큐가 front일 경우, front 다음에 붙임.
    if (queue == stack->front)
    {
        new->prev = stack->front;
        stack->front->next = new;
        stack->front = new;
    }
		//rear일 경우 rear다음에 붙임
    else if (queue == stack->rear)
    {
        new->next = stack->rear;
        stack->rear->prev = new;
        stack->rear = new;
    }
}

//큐에서 빼는 함수(front에서 빼기, rear에서 빼기)
int dequeu(MyStack  *stack, t_queue *queue)
{
    int     val;
    t_queue *temp;

    val = queue->value;
		//인자로 받은 큐가 front일 경우 front에서 빼기
    if (queue == stack->front)
    {
        temp = stack->front;
        stack->front = stack->front->prev;
        if (stack->front)
            stack->front->next = NULL;
        free(temp);
    }
		//큐가 rear일 경우 rear에서 빼기
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

//스택에 넣는 함수(맨 처음에는 new)를 직접 넣어줌
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

//dequeu함수로 값을 리턴
int myStackPop(MyStack* obj) {
    return (dequeu(obj, obj->front));
}

//front에 있는 값을 리턴
int myStackTop(MyStack* obj) {
    return (obj->front->value);
}

//front, rear중 하나가 널이면 비어있음
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
