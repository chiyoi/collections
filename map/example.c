#include <stdio.h>

#include "map.c"

struct map_int_int
{
    int MAP_KEY;
    int MAP_VAL;
    MAP_HANDLER;
};

void show(struct map_int_int m)
{
    struct map_iter it = {};
    int k = 0, v = 0;

    if (!MAP_ITER_NEXT(m, it, k, v))
        return printf("[]\n"), (void)0;

    printf("[%d: %d", k, v);
    while (MAP_ITER_NEXT(m, it, k, v))
        printf(", %d: %d", k, v);
    printf("]\n");
}

int main()
{
    struct map_int_int m = {};
    int k = 1;
    int i;

    printf("%zu %zu %d\n", LEN(m), CAP(m), HAS(m, k));
    E(m, k) = 2;
    printf("%zu %zu %d %d\n", LEN(m), CAP(m), HAS(m, k), E(m, k));
    E(m, k) = 3;
    printf("%zu %zu %d\n", LEN(m), CAP(m), E(m, k));
    DEL(m, k);
    printf("%zu %zu %d\n", LEN(m), CAP(m), E(m, k));

    for (i = 0; i < 20; i++)
    {
        E(m, i) = i;
        printf("put (%d) len (%zu) cap (%zu)\n", i, LEN(m), CAP(m));
    }
    k = 3;
    for (i = 0; i < CAP(m); i++)
        printf("bucket (%d) has length (%zu)\n", i, m.b_len[i]);
    show(m);
    MAP_FREE(m);

    MAP_MAKE(m, 20);
    printf("%zu %zu\n", LEN(m), CAP(m));
    MAP_FREE(m);
}
