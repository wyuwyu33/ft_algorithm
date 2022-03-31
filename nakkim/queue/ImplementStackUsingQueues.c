typedef struct node {
    int         data;
    struct node *nextNode;
}   Node;

typedef struct {
    Node    *front;
    Node    *rear;
    int     size;
}   MyStack;

// 스택 비었니
bool myStackEmpty(MyStack* obj) {
    if (obj->front == NULL)
        return (true);
    return (false);
}

// 큐 연산(Enqueue)
void    pushToBack(MyStack *obj, Node *newNode)
{
    (obj->size)++;
    if (myStackEmpty(obj))
    {
        obj->front = newNode;
        obj->rear = newNode;
        return ;
    }
    obj->rear->nextNode = newNode;
    obj->rear = newNode;
}

// 큐 연산(Dequeue)
Node    *popFromFront(MyStack *obj)
{
    Node    *remove;
    
    (obj->size)--;
    remove = obj->front;
    obj->front = obj->front->nextNode;
    remove->nextNode = NULL;
    if (obj->front == NULL)
        obj->rear = NULL;
    return (remove);
}

MyStack* myStackCreate() {
    MyStack *stack;
    
    stack = (MyStack*)malloc(sizeof(MyStack));
    stack->front = NULL;
    stack->rear = NULL;
    stack->size = 0;
    return (stack);
}

Node* createNode(int data) {
    Node    *node;
    
    node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->nextNode = NULL;
    return (node);
}

/**
 * 스택 연산
 * Enqueue 후 방금 추가한 노드가 front에 오도록
 * 노드 수 - 1 만큼 회전
 */
void myStackPush(MyStack* obj, int x) {
    Node    *newNode;
    int     count;
    
    newNode = createNode(x);
    pushToBack(obj, newNode);
    count = obj->size;
    while (--count > 0)
        pushToBack(obj, popFromFront(obj));
}

// front 제거하면 됨(가장 최근에 추가한 노드)
int myStackPop(MyStack* obj) {
    Node    *remove;
    int     data;
    
    remove = popFromFront(obj);
    data = remove->data;
    free(remove);
    return (data);
}

int myStackTop(MyStack* obj) {
    return (obj->front->data);
}

void myStackFree(MyStack* obj) {
    while (obj->size)
        myStackPop(obj);
    free(obj);
}