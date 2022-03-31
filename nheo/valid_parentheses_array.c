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

bool isValid(char * s){
    int     i;
		//문제 요구 조건에서 s 길이가 10000 이하로 설정되어있음
    char    stack[10001];
    int     type;

    i = 0;
    while (*s)
    {
        type = is_parentheses(*s);
        if (type > 3)
        {
            if (stack[i] != type - 3)
                return (false);
            i--;
        }
        else if (type)
        {
            i++;
            stack[i] = type;
        }
        s++;
    }
    if (i == 0)
        return (true);
    return (false);
}
