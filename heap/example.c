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
    const int *va = a, *vb = b;

    return *va - *vb;
}

void show(struct heap_int h)
{
    size_t i;

    if (LEN(h) == 0)
        return printf("[]\n"), (void)0;
    printf("[%d", A(h, 0));
    for (i = 1; i < LEN(h); i++)
        printf(", %d", A(h, i));
    printf("]\n");
}

int main()
{
    struct heap_int h = {};
    int t;
    const int a0[5] = {3, 5, 4, 1, 2};

    SLI_MAKE(h, 5, 5);
    memcpy(&A(h, 0), a0, sizeof a0);
    show(h);
    HEAP_INIT(h, compare);
    show(h);
    PUSH(h, 3);
    PUSH(h, 1);
    PUSH(h, 4);
    PUSH(h, 2);
    show(h);
    A(h, 0) = 6, FIX(h, 0);
    show(h);
    printf("%d\n", POP(h, t));
    printf("%d\n", POP(h, t));
    show(h);
    SLI_FREE(h);
}
