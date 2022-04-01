typedef struct node {
    int          data;
    struct node* nextNode;
}   Node;

typedef struct {
    Node*   bottom;
    Node*   top;
    int     size;
}   Stack;

// 스택 두개로 구성
typedef struct {
    Stack   *main;
    Stack   *temp;
}   MyQueue;

// 노드 생성
Node* createNode(int data) {
    Node*   node;
    
    node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->nextNode = NULL;
    return (node);
}

// 스택 생성
Stack* createStack() {
    Stack*  stack;
    
    stack = (Stack*)malloc(sizeof(Stack));
    stack->bottom = NULL;
    stack->top = NULL;
    stack->size = 0;
    return (stack);
}

// 큐 생성
MyQueue* myQueueCreate() {
    MyQueue* queue;
    
    queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->main = createStack();
    queue->temp = createStack();
    return (queue);
}

bool isStackEmpty(Stack* stack) {
    return (stack->bottom == NULL);
}

// 메인 스택이 NULL이면 Empty
bool myQueueEmpty(MyQueue* obj) {
    return (isStackEmpty(obj->main));
}

// Stack Push
void push(Stack* stack, Node* newNode) {
    (stack->size)++;
    // 빈 스택일 경우 top과 bottom 새 노드로 지정
    if (isStackEmpty(stack))
    {
        stack->bottom = newNode;
        stack->top = newNode;
        return ;
    }
    stack->top->nextNode = newNode;
    stack->top = newNode;
}

// Stack Pop
Node* pop(Stack* stack) {
    Node*   curr;

    // 빈 스택일 경우
    if (isStackEmpty(stack))
        return (NULL);
    curr = stack->bottom;
    (stack->size)--;
    // 스택에 요소가 하나일 경우
    if (stack->top == stack->bottom)
    {
        stack->top = NULL;
        stack->bottom = NULL;
        return (curr);
    }
    // 노드가 두개 이상이면 top의 이전 노드 찾아서 그걸 top으로 변경
    while (curr->nextNode != stack->top)
        curr = curr->nextNode;
    stack->top = curr;
    curr = curr->nextNode; // top
    stack->top->nextNode = NULL; // top과의 연결 끊음
    return (curr);
}

int top(Stack* stack) {
    return (stack->top->data);
}

// 스택stack의 모든 노드를 스택dest로 옮김
void transferNodes(Stack* stack, Stack* dest) {
    int count;
    
    count = stack->size;
    while (count-- > 0)
        push(dest, pop(stack));
}

// 새 요소는 스택의 bottom으로 가야함(FIFO)
void myQueuePush(MyQueue* obj, int x) {
    // 빈 스택이면 하나 추가하고 종료
    if (myQueueEmpty(obj))
    {
        push(obj->main, createNode(x));
        return ;
    }
    /*
     * 1. 현재 스택의 노드를 temp 스택으로 모두 옮김
     * 2. main 스택에 newNode 추가
     * 3. temp 스택의 노드 모두 main으로 옮김
     */
    transferNodes(obj->main, obj->temp);
    push(obj->main, createNode(x));
    transferNodes(obj->temp, obj->main);
}

// main 스택의 가장 위 요소 삭제 후 값 리턴
int myQueuePop(MyQueue* obj) {
    int data;
    Node* remove;
    
    if (myQueueEmpty(obj))
        return (0);
    remove = pop(obj->main);
    data = remove->data;
    free(remove);
    return (data);
}

// main 스택의 가장 위 요소값 리턴
int myQueuePeek(MyQueue* obj) {
    return (top(obj->main));
}

void destroyStack(Stack* stack) {
    while ((stack->size)-- > 0)
        free(pop(stack));
    free(stack);
}

void myQueueFree(MyQueue* obj) {
    destroyStack(obj->main);
    destroyStack(obj->temp);
    free(obj);
}