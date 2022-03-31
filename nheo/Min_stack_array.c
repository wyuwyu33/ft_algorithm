#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int index;
    int min;
    int *value;
} MinStack;


MinStack* minStackCreate() {
    MinStack    *minstack;
    
    minstack = (MinStack *)malloc(sizeof(MinStack));
    if (!minstack)
        exit(1);
    minstack->index = -1;
    minstack->value = (int *)malloc(sizeof(int) * 30000);
    if (!minstack->value)
        exit(1);
    return (minstack);
}

void minStackPush(MinStack* obj, int val) {
    obj->index++;
    obj->value[obj->index] = val;
    if (obj->index == 0)
        obj->min = val;
    else if (val < obj->min)
        obj->min = val;
}

void minStackPop(MinStack* obj) {
    int i;
    
    i = -1;
    printf("%d\n", obj->value[obj->index]);
    obj->index--;
    if (obj->value[obj->index + 1] == obj->min)
    {
        obj->min = obj->value[0];
        while (++i <= obj->index)
            if (obj->value[i] < obj->min)
                obj->min = obj->value[i];
    }
}

int minStackTop(MinStack* obj) {
    return (obj->value[obj->index]);
}

int minStackGetMin(MinStack* obj) {
    return (obj->min);
}

void minStackFree(MinStack* obj) {
    free(obj->value);
    free(obj);
}
