#include <stdbool.h>
#include <stdlib.h>

typedef struct stack
{
    int  top;
    char vals[]; // Zero-Length Array
}   Stack;

Stack *CreateStack(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack) + (size * sizeof(char)));
    stack->top = -1;
    return (stack);
}

void push(Stack *stack, int val)
{
    stack->top++;
    if(stack->top >= 0)
        stack->vals[stack->top] = val;
}

void pop(Stack *stack)
{
    stack->top--;
}

char stackTop(Stack* stack)
{
    return (stack->vals[stack->top]);
}

bool isOpenBracket(char ch)
{
    return (ch == '(' || ch == '{' || ch =='[');
}

bool isBarcketCorrectOrder(char open, char close)
{
    if (open == '(' && close == ')')
      return true;
    else if (open == '{' && close == '}')
      return true;
    else if (open == '[' && close == ']')
      return true;
    return false;
}

bool isValid(char * s){
    int     len;
    Stack   *stack;

    len = strlen(s);
    stack = CreateStack(len);
    while (*s)
    {
        if (isOpenBracket(*s))
            push(stack, *s);
        else
        {
            if(isBarcketCorrectOrder(stackTop(stack), *s))
                pop(stack);
            else
                return (false);
        }
        s++;
    }
    return (stack->top == -1);
}
