/* slice.h */
#include <stdlib.h>
#include <string.h>

#ifndef SLICE_H
#define SLICE_H

#define SLICE_DATA (*data)
#define SLICE_HANDLER size_t off, len, cap

#define SLI_MAKE(sli, length, capacity) (0 <= (length) && (length) <= (capacity) && ((sli).data = calloc((capacity), sizeof *(sli).data)) != NULL ? ((sli).off = 0, (sli).len = (length), (sli).cap = (capacity), (void)0) : (void)0)
#define SLI_FREE(sli) (free((sli).data), memset(&(sli), 0, sizeof(sli)), (void)0)

#define A(sli, i) (sli).data[(sli).off + i]
#define APPEND(sli, val) ((sli).off + (sli).len <= (sli).cap && ((sli).off + (sli).len == (sli).cap ? ((sli).data = realloc((sli).data, ((sli).cap > 0 && (sli).cap < 65536 ? ((sli).cap *= 2) : ((sli).cap += 1)) * sizeof *(sli).data)) : (sli).data) != NULL ? ((sli).data[(sli).off + ((sli).len++)] = (val), (void)0) : (void)0)
#define SLICE(sli, a, b) ((a) < 0 ? ((sli).len = (b) < 0 ? 0 : ((b) < (sli).len ? (b) : (sli).len)) : ((a) < (sli).len ? ((sli).off += (a), (sli).len = (b) < (a) ? 0 : ((b) < (sli).len ? (b) - (a) : (sli).len)) : ((sli).off = (sli).len, (sli).len = 0)), (void)0)

#ifndef PROPERTY_ACCESS
#define PROPERTY_ACCESS
#define LEN(c) ((c).len)
#define CAP(c) ((c).cap)
#endif
#endif
/* end slice.h */

/* heap.h */
#include <stdlib.h>
#include <string.h>

#define HEAP_HANDLER int (*compare)(const void *a, const void *b)

#define HEAP_INIT(h, compare) ((h).compare = (compare))
#define HEAP_PUSH(h, val) (APPEND(h, val), _up(LEN(h) - 1, &A(h, 0), LEN(h), (h).compare, sizeof A(h, 0)))
#define HEAP_PEAK(h) A(h, 0)
#define HEAP_POP(h, out) (_swap(&A(h, 0), &A(h, LEN(h) - 1), sizeof A(h, 0)), _down(0, LEN(h) - 1, &A(h, 0), (h).compare, sizeof A(h, 0)), out = A(h, LEN(h) - 1), SLICE(h, 0, LEN(h) - 1), out)

void _swap(void *a, void *b, size_t size);
void _up(int j, void *data, size_t data_size, int (*compare)(const void *a, const void *b), size_t item_size);
char _down(size_t i0, size_t n, void *data, int (*compare)(const void *a, const void *b), size_t item_size);
/* end heap.h */

void _swap(void *a, void *b, size_t size)
{
    void *t;

    t = malloc(size),
    memcpy(t, a, size),
    memcpy(a, b, size),
    memcpy(b, t, size),
    free(t);
}

void _up(int j, void *data, size_t data_size, int (*compare)(const void *a, const void *b), size_t item_size)
{
    size_t i;

    while (0 == 0)
    {
        i = (j - 1) / 2; /* parent */
        if (i == j || compare(data + j * item_size, data + i * item_size) >= 0)
            break;

        _swap(data + i * item_size, data + j * item_size, item_size);
        j = i;
    }
}

char _down(size_t i0, size_t n, void *data, int (*compare)(const void *a, const void *b), size_t item_size)
{
    size_t i, j, j1, j2;

    i = i0;
    while (0 == 0)
    {
        j1 = 2 * i + 1;
        if (j1 >= n || j1 < 0) /* j1 < 0 after int overflow */
            break;

        j = j1, j2 = j1 + 1; /* left child */
        if (j2 < n && compare(data + j2 * item_size, data + j1 * item_size) < 0)
            j = j2; /* = 2*i + 2  // right child */

        if (compare(data + j * item_size, data + i * item_size) >= 0)
            break;

        _swap(data + i * item_size, data + j * item_size, item_size);
        i = j;
    }
    return i > i0;
}
