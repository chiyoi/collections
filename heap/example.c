#include <stdio.h>
#include <stdlib.h>

#include "heap.c"

struct heap_int
{
    int SLICE_DATA;
    SLICE_HANDLER;
    HEAP_HANDLER;
};

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    struct heap_int h = {};
    int t;

    HEAP_INIT(h, compare);
    HEAP_PUSH(h, 3);
    HEAP_PUSH(h, 1);
    HEAP_PUSH(h, 4);
    HEAP_PUSH(h, 2);
    printf("%zu\n", LEN(h));
    printf("%d\n", HEAP_PEAK(h));
    printf("%d\n", HEAP_POP(h, t));
    printf("%d\n", HEAP_POP(h, t));
    printf("%zu\n", LEN(h));
    SLI_FREE(h);
    return 0;
}
