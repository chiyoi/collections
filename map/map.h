#include <stdlib.h>
#include <string.h>

#ifndef MAP_H
#define MAP_H
#define _LOAD_FACTOR_NUM 13
#define _LOAD_FACTOR_DEN 16

#define MAP_KEY (**keys)
#define MAP_VAL (**vals)
#define MAP_HANDLER size_t len, cap, *b_len, flag[2];

#define MAP_MAKE(m, hint) ((m).len = 0, (m).cap = (hint / _LOAD_FACTOR_DEN + 1) * _LOAD_FACTOR_DEN, _collections_map_alloc((void ***)&(m).keys, (void ***)&(m).vals, (m).cap, &(m).b_len))
#define MAP_FREE(m) (_collections_map_free_all((void **)(m).keys, (m).cap), _collections_map_free_all((void **)(m).vals, (m).cap), free((m).keys), free((m).vals), free((m).b_len), RST(m), (void)0)

#define E(m, key) *(_collections_map_check_load((void ***)&(m).keys, (void ***)&(m).vals, (m).len, &(m).cap, &(m).b_len, sizeof **(m).keys, sizeof **(m).vals), _collections_map_check_key((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, (m).flag, sizeof **(m).keys, sizeof **(m).vals), &(m).vals[(m).flag[0]][(m).flag[1]])
#define HAS(m, key) _collections_map_has((void *)&(key), (void **)(m).keys, (m).cap, (m).b_len, sizeof **(m).keys)
#define DEL(m, key) _collections_map_del((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, sizeof **(m).keys, sizeof **(m).vals)

#define MAP_ITER_INIT(m, it) _collections_map_iter_init(&(it), (m).cap, (m).b_len)
#define MAP_ITER_NEXT(m, it, key, val) ((it).i < (m).cap ? ((key) = (m).keys[(it).i][(it).j], (val) = (m).vals[(it).i][(it).j], _collections_map_iter_next(&(it), (m).cap, (m).b_len), 1) : 0)

#ifndef PROPERTY_ACCESS
#define PROPERTY_ACCESS
#define LEN(c) ((c).len)
#define CAP(c) ((c).cap)
#define RST(c) (memset(&(c), 0, sizeof(c)), (void)0)
#endif

struct map_iter
{
    size_t i, j;
};

void _collections_map_alloc(void ***keys, void ***vals, size_t cap, size_t **b_len);
void _collections_map_free_all(void **a, size_t size);
void _collections_map_check_load(void ***keys, void ***vals, size_t len, size_t *cap, size_t **b_len, size_t key_size, size_t val_size);
void _collections_map_check_key(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t flag[2], size_t key_size, size_t val_size);
char _collections_map_has(void *key, void **keys, size_t cap, size_t *b_len, size_t key_size);
void _collections_map_del(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t key_size, size_t val_size);
void _collections_map_iter_init(struct map_iter *it, size_t cap, size_t *b_len);
void _collections_map_iter_next(struct map_iter *it, size_t cap, size_t *b_len);
#endif
