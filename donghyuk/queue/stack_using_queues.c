/*
 * Name    : https://leetcode.com/problems/implement-stack-using-queues/
 * Purpose : 두 개의 큐로 스택 구현하기
 * Author  : donghyuk
 * Date    : 2022.03.31
 * Notion  : https://graceful-atom-bb0.notion.site/Stack-6f54a284d8564f158f60423e4f316517
 */

#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_SIZE 100

typedef struct s_queue{
    int front;     // Queue front 인덱스
    int rear;      // Queue rear 인덱스
    int max_size;  // Queue 최대 사이즈
    int vals[];    // Queue 데이터 배열
}   t_Queue;

typedef struct s_myStack{
    t_Queue *mainQ;
    t_Queue *subQ;
} t_MyStack;

t_Queue *QueueCreate(int size)
{
    t_Queue *q;

    q = (t_Queue*)malloc(sizeof(t_Queue) + (sizeof(int) * size));
    q->front = -1;
    q->rear = -1;
    q->max_size = size;
    return (q);
}

/*
 * Queue가 비어있는지 확인
 * * 초기 생성 시 또는 pop 처리 후 Queue에 데이터가 없을 시 -1로 저장이 되고 이를 체크한다.
 * */
bool isQueueEmpty(t_Queue *q)
{
    return (q->front == -1);
}

/*
 * srcQ의 데이터를 dstQ의 데이터로 옮기고 srcQ는 초기화
 * * push함수 호출 시 mainQ의 데이터를 subQ의 데이터로 옮기는데 사용된다.
 * */
void moveQueueData(t_Queue *dst, t_Queue *src, int size)
{
	int	idx;

    if (!isQueueEmpty(src))
    {
		idx = -1;
        while (idx++ <= src->rear)
            dst->vals[idx + size] = src->vals[idx];
        dst->front = 0;
        dst->rear = src->rear + size;
        src->front = -1;
        src->rear = -1;
    }
}

/*
 * queue 데이터 입력
 * */
void enQueue(t_Queue *q, int val)
{
    if (isQueueEmpty(q))
        q->front = 0;
    q->rear++;
    q->vals[q->rear] = val;
}

/*
 * queue 데이터 출력
 * */
int deQueue(t_Queue *q)
{
    int result;

    result = q->vals[q->front++];
    if(q->front == q->rear + 1)
    {
        q->front = -1;
        q->rear = -1;
    }
    return (result);
}

/*
 * Queue 데이터 크기 확인
 * */
bool isQueueFull(t_Queue *q)
{
    return (q->max_size == q->rear);
}

/*
 * Stack Create
 * */
t_MyStack* myStackCreate() {
    t_MyStack *stack;

    stack = (t_MyStack *)malloc(sizeof(t_MyStack));
    stack->mainQ = QueueCreate(QUEUE_SIZE);
    stack->subQ = QueueCreate(QUEUE_SIZE);
    return (stack);
}

/*
 * Stack Push
 * * 데이터 입력 전
 * *   Stack 내부의 mainQ의 사이즈가 MAX일 경우 현재 사이즈에서 2배로 늘려준다.
 * * 데이터 입력
 * *   mainQ의 데이터를 모두 subQ로 넘겨준다.
 * *   그 후 빈 mainQ에 데이터를 입력한다. 그러면 해당 데이터는 front에 위치하게 한다.
 * *   subQ의 데이터를 다시 mainQ에 넘겨준다.
 * */
void myStackPush(t_MyStack* stack, int val) {
    t_Queue *tempQ;
    int    max_size;

    if (isQueueFull(stack->mainQ))
    {
        max_size = stack->mainQ->max_size;
        tempQ = QueueCreate(max_size * 2);
        moveQueueData(tempQ, stack->mainQ, 0);
        free(stack->mainQ);
        free(stack->subQ);
        stack->mainQ = QueueCreate(max_size * 2);
        stack->subQ = tempQ;
        moveQueueData(stack->mainQ, stack->subQ, 1);
    }
    else
    {
        moveQueueData(stack->subQ, stack->mainQ, 0);
        enQueue(stack->mainQ, val);
        moveQueueData(stack->mainQ, stack->subQ, 1);
    }
}

/*
 * Stack Pop
 * 큐에서 데이터 반환 후 제거
 * */
int myStackPop(t_MyStack* stack) {
    return (deQueue(stack->mainQ));
}

/*
 * Stack Top
 * 큐에서 데이터 반환
 * */
int myStackTop(t_MyStack* stack) {
    t_Queue *mainQ;

    mainQ = stack->mainQ;
    return (mainQ->vals[mainQ->front]);
}

/*
 * Stack Empty
 * mainQ가 비었는지 확인
 * */
bool myStackEmpty(t_MyStack* stack) {
    return (stack->mainQ->front == -1);
}

/*
 * Stack Free
 * */
void myStackFree(t_MyStack* stack) {
    free(stack->mainQ);
    free(stack->subQ);
    free(stack);
}
