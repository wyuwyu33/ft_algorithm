typedef struct node {
    int data;
    struct node *prevNode;
    struct node *nextNode;
} Node;

typedef struct {
    Node *list;
    Node *top;
} MinStack;

MinStack* minStackCreate() {
    MinStack *stack;
    
    stack = (MinStack*)malloc(sizeof(MinStack));
    stack->list = NULL;
    stack->top = NULL;
    return (stack);
}

Node *createNode(int val) {
    Node * node;
    
    node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->nextNode = NULL;
    node->prevNode = NULL;
    return (node);
}

void minStackPush(MinStack* obj, int val) {
    Node *newNode;
    
    newNode = createNode(val);
    if (obj->list == NULL) {
        obj->list = newNode;
        obj->top = newNode;
        return ;
    }
    newNode->prevNode = obj->top;
    obj->top->nextNode = newNode;
    obj->top = newNode;
}

void minStackPop(MinStack* obj) {
    Node *curr;
    Node *top;
    
    top = obj->top;
    if (obj->list == obj->top) {
        free(top);
        obj->list = NULL;
        obj->top = NULL;
        return ;
    }
    obj->top->prevNode->nextNode = NULL;
    obj->top = obj->top->prevNode;
    free(top);
}

int minStackTop(MinStack* obj) {
    return (obj->top->data);
}

int minStackGetMin(MinStack* obj) {
    int min;
    Node *curr;
    
    min = obj->list->data;
    curr = obj->list;
    while (curr != NULL) {
        if (curr->data < min)
            min = curr->data;
        curr = curr->nextNode;
    }
    return (min);
}

void minStackFree(MinStack* obj) {
    Node *next;
    Node *curr;
    
    curr = obj->list;
    while (curr != NULL) {
        next = curr->nextNode;
        free(curr);
        curr = next;
    }
}