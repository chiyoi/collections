#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <slice.h>
#include <heap.h>
#include <map.h>

struct slice_int
{
    int SLICE_DATA;
    SLICE_HANDLER;
};

struct map_int_int
{
    int MAP_KEY;
    int MAP_VAL;
    MAP_HANDLER;
};

struct heap_int
{
    int SLICE_DATA;
    SLICE_HANDLER;
    HEAP_HANDLER;
};

void show_slice(struct slice_int sli)
{
    int i;

    if (LEN(sli) == 0)
        printf("[]\n");
    printf("[%d", A(sli, 0));
    for (i = 0; i < LEN(sli); i++)
        printf(", %d", A(sli, i));
    printf("]\n");
}

void show_map(struct map_int_int m)
{
    int k = 0, v = 0;
    struct map_iter it = {};

    if (!MAP_ITER_NEXT(m, it, k, v))
        printf("[]\n");
    printf("[%d: %d", k, v);
    while (MAP_ITER_NEXT(m, it, k, v))
        printf(", %d: %d", k, v);
    printf("]\n");
}

void show_heap(struct heap_int h)
{
    struct slice_int sli = {};

    memcpy(&sli, &h, sizeof sli);
    show_slice(sli);
}

int main()
{
    int i;
    struct slice_int sli = {};
    struct map_int_int m = {};
    struct heap_int h = {};

    srand(time(NULL));
    for (i = 0; i < 10; i++)
        APPEND(sli, rand() % 10);
    show_slice(sli);

    for (i = 0; i < 10; i++)
        E(m, i) = rand() % 10;
    show_map(m);

    /* FIXME */
    for (i = 0; i < 10; i++)
        HEAP_PUSH(h, rand() % 10);
    show_heap(h);

    SLI_FREE(sli);
    MAP_FREE(m);
    SLI_FREE(h);
}