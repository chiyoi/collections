#include <stdlib.h>
#include <string.h>

#define HEAP_HANDLER int (*cmp)(const void *a, const void *b)

#define HEAP_INIT(h, compare) ((h).cmp = (compare), _collections_heap_init(LEN(h), &A(h, 0), (h).cmp, sizeof A(h, 0)))
#define HEAP_PUSH(h, val) (APPEND(h, val), _collections_heap_up(LEN(h) - 1, &A(h, 0), (h).cmp, sizeof A(h, 0)))
#define HEAP_POP(h, out) (_collections_heap_swap(&A(h, 0), &A(h, LEN(h) - 1), sizeof A(h, 0)), _collections_heap_down(0, LEN(h) - 1, &A(h, 0), (h).cmp, sizeof A(h, 0)), out = A(h, LEN(h) - 1), SLICE(h, 0, LEN(h) - 1), out)
#define HEAP_FIX(h, i) (!_collections_heap_down(i, LEN(h), &A(h, 0), (h).cmp, sizeof A(h, 0)) ? _collections_heap_up(i, &A(h, 0), (h).cmp, sizeof A(h, 0)) : (void)0)

void _collections_heap_init(size_t n, void *data, int (*compare)(const void *a, const void *b), size_t item_size);
void _collections_heap_swap(void *a, void *b, size_t size);
void _collections_heap_up(size_t j, void *data, int (*compare)(const void *a, const void *b), size_t item_size);
char _collections_heap_down(size_t i0, size_t n, void *data, int (*compare)(const void *a, const void *b), size_t item_size);
