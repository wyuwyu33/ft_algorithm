typedef struct s_stack{
    int             value;
    struct s_stack  *next;
    struct s_stack  *prev;
    struct s_stack  *top;
} t_stack;

int is_parentheses(char c)
{
    if (c == '(')
        return (1);
    if (c == '{')
        return (2);
    if (c == '[')
        return (3);
    if (c == ')')
        return (4);
    if (c == '}')
        return (5);
    if (c == ']')
        return (6);
    return (0);
}

t_stack   *ft_push(t_stack *stack, int val)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(t_stack));
    if (!new)
        exit(0);
    new->value = val;
    new->next = NULL;
    if (!stack)
    {
        stack = new;
        new->prev = NULL;
        stack->top = new;
    }
    else
    {
        stack->top->next = new;
        new->prev = stack->top;
        stack->top = new;
    }
    return (stack);
}

t_stack   *ft_pop(t_stack *stack)
{
    t_stack *temp;
    
    temp = stack->top->prev;
    if (temp)
        temp->next = NULL;
    if (stack != stack->top)
    {
        free(stack->top);
        stack->top = temp;
    }
    else
    {
        free(stack);
        stack = temp;
    }
    return (stack);
}

bool isValid(char * s){
    int     i;
    t_stack *stack;
    int     type;

    i = 0;
    stack = NULL;
    while (*s)
    {
        type = is_parentheses(*s);
        if (type > 3 && stack)
        {
            if (stack->top->value != type - 3)
                return (false);
            i--;
            stack = ft_pop(stack);
        }
        else if (type)
        {
            i++;
            stack = ft_push(stack, type);
        }
        s++;
    }
    if (i == 0)
        return (true);
    return (false);
}
