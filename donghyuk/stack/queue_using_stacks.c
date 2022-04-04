/*
 * Purpose : 두 개의 스택으로 큐 구현하기
 * link    : https://leetcode.com/problems/implement-queue-using-stacks
 * Notion  : https://graceful-atom-bb0.notion.site/Stack-6f54a284d8564f158f60423e4f316517
 * Author  : donghyuk
 * Date    : 2022.04.01
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{		// 이중연결 리스트
    int val;
    struct s_node *next;	// 다음 노드
    struct s_node *prev;	// 이전 노드
}   t_Node;

typedef struct s_stack {	// stack
    t_Node *top;			// 가장 위의 노드
}   t_Stack;

typedef struct myQueue{
    t_Stack *pushS;			// push 스택
    t_Stack *popS;			// pop 스택
}   MyQueue;

/*
 * Stack Push
 * * 스택이 비어있을 경우, top노드에 new노드 대입
 * * 스택이 비어있지 않을 경우, top노드와 new노드의 이중연결 적용
 * */
void    push(t_Stack *stack, int val)
{
    t_Node * new;

    new = (t_Node*)calloc(1, sizeof(t_Node));
    if (stack->top == NULL)
        stack->top = new;
    else
    {
        stack->top->next = new;
        new->prev = stack->top;
        stack->top = new;
    }
    stack->top->val = val;
}

/*
 * Stack pop
 * * top노드 데이터를 꺼내 반환
 * * top노드 위치를 한 칸 밑으로 이동 및 top노드 할당 해제
 * */
int    pop(t_Stack *stack)
{
	t_Node	*tmp;
    int result;

    result = stack->top->val;
	tmp = stack->top;
    stack->top = stack->top->prev;
	if (stack->top != NULL)
		stack->top->next = NULL;
	free(tmp);
    return (result);
}

/*
 * Stack free
 * * 스택에 연결된 모든 노드 할당 해제
 * */
void	freeStack(t_Stack * stack)
{
	t_Node *tmp;

	while (stack->top != NULL)
	{
		tmp = stack->top;
		stack->top = stack->top->prev;
		free(tmp);
	}
}

/*
 * moveStackData
 * * src 모든 데이터를 dst 스택으로 이동
 * */
void    moveStackData(t_Stack *dst, t_Stack *src)
{
    while (src->top != NULL)
    {
        push(dst, src->top->val);
        pop(src);
    }
}

/*
 * isStackEmpty
 * * 스택이 비어있을 경우 Top노드가 NULL이므로 이를 체크
 * */
int isStackEmpty(t_Stack *s)
{
    return (s->top == NULL);
}

/*
 * myQueueCreate
 * * 스택이 비어있을 경우 Top노드가 NULL이므로 이를 체크
 * */
MyQueue* myQueueCreate() {
    MyQueue *q;

    q = (MyQueue *)calloc(1, sizeof(MyQueue));
	if (q == NULL)
		exit(1);
    q->pushS = (t_Stack *)calloc(1, sizeof(t_Stack));
    q->popS = (t_Stack *)calloc(1, sizeof(t_Stack));
    if (q->pushS == NULL || q->popS == NULL)
        exit(1);
    return (q);
}

/*
 * myQueuePush
 * * push 스택에 노드 추가
 * */
void myQueuePush(MyQueue* q, int val) {
    push(q->pushS, val);
}

/*
 * myQueuePOP
 * * pop 스택의 데이터가 비어있지 않을 경우 데이터 반환 후 제거
 * * pop 스택의 데이터가 비어있을 경우 push 스택의 데이터를 pop 스택으로 전달
 * */
int myQueuePop(MyQueue* q) {
    if (isStackEmpty(q->popS))
    {
        if (isStackEmpty(q->pushS))
            return (-1);
        else
            moveStackData(q->popS, q->pushS);
    }
    return (pop(q->popS));
}

/*
 * myQueuePeek
 * * pop과 처리가 동일하나 데이터 제거는 하지않고 반환만 수행
 * */
int myQueuePeek(MyQueue* q) {
    if (isStackEmpty(q->popS))
    {
        if (isStackEmpty(q->pushS))
            return (-1);
        else
            moveStackData(q->popS, q->pushS);
    }
    return (q->popS->top->val);
}

/*
 * myQueueEmpty
 * * push스택과 pop스택이 둘 다 비었는지 확인
 * */
bool myQueueEmpty(MyQueue* q) {
    return (isStackEmpty(q->popS) && isStackEmpty(q->pushS));
}

/*
 * myQueueEmpty
 * * Push스택, Pop스택 먼저 할당 해제 후 Queue 할당 해제
 * */
void myQueueFree(MyQueue* q) {
	freeStack(q->popS);
	freeStack(q->pushS);
    free(q);
}

int main()
{
	MyQueue* obj = myQueueCreate();
	myQueuePush(obj, 1);
	myQueuePush(obj, 2);
	myQueuePush(obj, 3);
	myQueuePush(obj, 4);
	int param_2 = myQueuePeek(obj);
	param_2 = myQueuePop(obj);
	myQueuePush(obj, 5);
	param_2 = myQueuePop(obj);
	param_2 = myQueuePop(obj);
	param_2 = myQueuePop(obj);
	param_2 = myQueuePop(obj);
	bool param_4 = myQueueEmpty(obj);

	myQueueFree(obj);
}

