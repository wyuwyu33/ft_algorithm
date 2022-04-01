#include <stdlib.h>

//스택 정의
typedef struct s_stack{
    int             value;
    struct s_stack  *next;
    struct s_stack  *prev;
    struct s_stack  *top;
} t_stack;

//스택 두 개로 큐 구현(한 개는 푸시 담당, 한 개는 팝 담당)
typedef struct {
    t_stack *stack_push;
    t_stack *stack_pop;
} MyQueue;

//스택에 new를 추가하는 함수
t_stack *push_stack(t_stack *stack, t_stack *new)
{
    if (!stack)
    {
		//stack이 비어 있을 경우 new를 리턴해준다.
        new->top = new;
        return (new);
    }
    stack->top->next = new;
    new->prev = stack->top;
    stack->top = new;
    return (stack);
}

//스택에서 top 제거하는 함수
t_stack *pop_stack(t_stack  *stack)
{
    t_stack *temp;

    temp = stack->top->prev;
    if (temp)
        temp->next = NULL;
    if (stack->top == stack)
    {
				//스택이 한칸짜리인 경우 아래에서 stack->top을 참조하면 에러가 나기 때문에 따로...ㅠㅠ
        free(stack->top);
        return (NULL);
    }
    free(stack->top);
    stack->top = temp;
    return (stack);
}

//src의 스택을 모두 팝해서 순서대로 dest에 담아주는 함수. src의 반대 순서대로 dest에 정렬됨
MyQueue *move_stack(MyQueue *obj, t_stack *dest, t_stack *src)
{
    t_stack *temp;
    t_stack *new;

    while (src)
    {
        new = (t_stack *)calloc(sizeof(t_stack), 1);
        if (!new)
            exit (0);
        new->value = src->top->value;
        dest = push_stack(dest, new);
        src = pop_stack(src);
    }
    obj->stack_pop = dest;
    obj->stack_push = src;
    return (obj);    
}

//할당해주는 함수, calloc 사용
MyQueue* myQueueCreate() {
    MyQueue *que;
    
    que = (MyQueue *)calloc(sizeof(MyQueue), 1);
    if (!que)
        exit(0);
    return (que);
}

//push_stack으로 구현
void myQueuePush(MyQueue* obj, int x) {
    t_stack *new;

    new = (t_stack *)calloc(sizeof(t_stack), 1);
    if (!new)
        exit(0);
    new->value = x;
    obj->stack_push = push_stack(obj->stack_push, new);
}

//큐를 확인해서 pop용 스택이 비어있으면 move_stack함수로 pop용 스택에 채워준다음 pop전용 스택의 top을 리턴, 제거
int myQueuePop(MyQueue* obj) {
    int     val;

    if (obj->stack_pop == NULL)
        obj = move_stack(obj, obj->stack_pop, obj->stack_push);
    val = obj->stack_pop->top->value;
    obj->stack_pop = pop_stack(obj->stack_pop);
    return (val);
}

//pop과 동일하게 pop용 스택을 확인하고 거기서 제일 위에있는 것을 리턴
int myQueuePeek(MyQueue* obj) {
    if (obj->stack_pop == NULL)
        obj = move_stack(obj, obj->stack_pop, obj->stack_push);
    return (obj->stack_pop->top->value);
}

//스택이 둘다 비어있으면 큐가 빈 것이다
bool myQueueEmpty(MyQueue* obj) {
    return (!obj->stack_push && !obj->stack_pop);
}

//pop_stack으로 구현
void myQueueFree(MyQueue* obj) {    
    while (obj->stack_push)
        obj->stack_push = pop_stack(obj->stack_push);
    while (obj->stack_pop)
        obj->stack_pop = pop_stack(obj->stack_pop);
    free(obj);
}
