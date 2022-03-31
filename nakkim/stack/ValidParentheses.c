typedef struct  stack {
    int     capacity;
    int     top;
    char    *datas;
} Stack;

Stack *createStack(int capacity)
{
    Stack *stack;
    
    stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->datas = (char*)malloc(sizeof(char) * capacity);
    return (stack);
}

void    destroyStack(Stack *stack)
{
    free(stack->datas);
    free(stack);
}

void    push(Stack *stack, char c)
{
    if (stack->top == stack->capacity - 1)
        return ;
    stack->datas[++(stack->top)] = c;
}

char    pop(Stack *stack)
{
    if (isEmpty(stack))
        return (0);
    return (stack->datas[(stack->top)--]);
}

int isOpenParentheses(char c)
{
    if (c == '(')
        return (1);
    if (c == '[')
        return (2);
    if (c == '{')
        return (3);
    return (0);
}

int isCloseParentheses(char c)
{
    if (c == ')')
        return (1);
    if (c == ']')
        return (2);
    if (c == '}')
        return (3);
    return (0);
}

int isEmpty(Stack *stack)
{
    if (stack->top == -1)
        return (1);
    return (0);
}

bool isValid(char * s){
    Stack   *stack;

    stack = createStack(strlen(s));
    while (*s)
    {
				// 닫는 괄호면 스택의 top 꺼내서 짝이 맞지 않는 경우 flase
        if (isCloseParentheses(*s) && isCloseParentheses(*s) != isOpenParentheses(pop(stack)))
            return (false);
        else if (isOpenParentheses(*s)) // 여는 괄호면 스택에 push
            push(stack, *s);
        s++;
    }
		// 괄호 짝이 모두 맞는 경우 스택이 비어 있어야 함
    if (!isEmpty(stack))
        return (false);
    destroyStack(stack);
    return (true);
}