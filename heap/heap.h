#include <stdlib.h>
#include <string.h>

#define HEAP_HANDLER int (*compare)(const void *a, const void *b)

#define HEAP_INIT(h, compare) (memset(&h, 0, sizeof h), (h).compare = (compare))
#define HEAP_PUSH(h, val) (APPEND(h, val), _up(LEN(h) - 1, &A(h, 0), LEN(h), (h).compare, sizeof A(h, 0)))
#define HEAP_PEAK(h) A(h, 0)
#define HEAP_POP(h, out) (_swap(&A(h, 0), &A(h, LEN(h) - 1), sizeof A(h, 0)), _down(0, LEN(h) - 1, &A(h, 0), (h).compare, sizeof A(h, 0)), out = A(h, LEN(h) - 1), SLICE(h, 0, LEN(h) - 1), out)

void _swap(void *a, void *b, size_t size);
void _up(int j, void *data, size_t data_size, int (*compare)(const void *a, const void *b), size_t item_size);
char _down(size_t i0, size_t n, void *data, int (*compare)(const void *a, const void *b), size_t item_size);
