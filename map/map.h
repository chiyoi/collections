#include <stdlib.h>
#include <string.h>

#ifndef MAP_H
#define MAP_H
#define _LOAD_FACTOR_NUM 13
#define _LOAD_FACTOR_DEN 16

#define MAP_KEY (**keys)
#define MAP_VAL (**vals)
#define MAP_HANDLER size_t len, cap, *b_len, flag[2];

#define MAP_MAKE(m, hint) ((m).cap = (hint / _LOAD_FACTOR_DEN + 1) * _LOAD_FACTOR_DEN, _alloc_map((void ***)&(m).keys, (void ***)&(m).vals, (m).cap, &(m).b_len))
#define MAP_FREE(m) (_free_all((void **)(m).keys, (m).cap), _free_all((void **)(m).vals, (m).cap), free((m).keys), free((m).vals), free((m).b_len), memset(&m, 0, sizeof m), (void)0)

#define E(m, key) *(_check_load((void ***)&(m).keys, (void ***)&(m).vals, (m).len, &(m).cap, &(m).b_len, sizeof **(m).keys, sizeof **(m).vals), _check_key((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, (m).flag, sizeof **(m).keys, sizeof **(m).vals), &(m).vals[(m).flag[0]][(m).flag[1]])
#define MAP_HAS(m, key) _map_has((void *)&(key), (void **)(m).keys, (m).cap, (m).b_len, sizeof **(m).keys)
#define MAP_DEL(m, key) _map_del((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, sizeof **(m).keys, sizeof **(m).vals)

#define MAP_ITER_NEXT(m, it, key, val) ((it).i < (m).cap ? ((key) = (m).keys[(it).i][(it).j], (val) = (m).vals[(it).i][(it).j], _next(&(it), (m).cap, (m).b_len), 1) : 0)

#ifndef PROPERTY_ACCESS
#define PROPERTY_ACCESS
#define LEN(m) ((m).len)
#define CAP(m) ((m).cap)
#endif

struct map_iter
{
    size_t i, j;
};

void _alloc_map(void ***keys, void ***vals, size_t cap, size_t **b_len);
void _free_all(void **a, size_t size);
void _check_load(void ***keys, void ***vals, size_t len, size_t *cap, size_t **b_len, size_t key_size, size_t val_size);
void _check_key(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t flag[2], size_t key_size, size_t val_size);
char _map_has(void *key, void **keys, size_t cap, size_t *b_len, size_t key_size);
void _map_del(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t key_size, size_t val_size);
void _next(struct map_iter *it, size_t cap, size_t *b_len);
#endif
