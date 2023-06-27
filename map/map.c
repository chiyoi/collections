/* map.h */
#include <stdlib.h>
#include <string.h>

#ifndef MAP_H
#define MAP_H
#define _LOAD_FACTOR_NUM 13
#define _LOAD_FACTOR_DEN 16

#define MAP_KEY (**keys)
#define MAP_VAL (**vals)
#define MAP_HANDLER size_t len, cap, *b_len, flag[2];

#define MAP_MAKE(m, hint) ((m).cap = (hint / _LOAD_FACTOR_DEN + 1) * _LOAD_FACTOR_DEN, _collections_map_alloc((void ***)&(m).keys, (void ***)&(m).vals, (m).cap, &(m).b_len))
#define MAP_FREE(m) (_collections_map_free_all((void **)(m).keys, (m).cap), _collections_map_free_all((void **)(m).vals, (m).cap), free((m).keys), free((m).vals), free((m).b_len), memset(&m, 0, sizeof m), (void)0)

#define E(m, key) *(_collections_map_check_load((void ***)&(m).keys, (void ***)&(m).vals, (m).len, &(m).cap, &(m).b_len, sizeof **(m).keys, sizeof **(m).vals), _collections_map_check_key((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, (m).flag, sizeof **(m).keys, sizeof **(m).vals), &(m).vals[(m).flag[0]][(m).flag[1]])
#define MAP_HAS(m, key) _collections_map_has((void *)&(key), (void **)(m).keys, (m).cap, (m).b_len, sizeof **(m).keys)
#define MAP_DEL(m, key) _collections_map_del((void *)&(key), (void **)(m).keys, (void **)(m).vals, &(m).len, (m).cap, (m).b_len, sizeof **(m).keys, sizeof **(m).vals)

#define MAP_ITER_NEXT(m, it, key, val) ((it).i < (m).cap ? ((key) = (m).keys[(it).i][(it).j], (val) = (m).vals[(it).i][(it).j], _collections_map_iter_next(&(it), (m).cap, (m).b_len), 1) : 0)

#ifndef PROPERTY_ACCESS
#define PROPERTY_ACCESS
#define LEN(c) ((c).len)
#define CAP(c) ((c).cap)
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
void _collections_map_iter_next(struct map_iter *it, size_t cap, size_t *b_len);
#endif
/* end map.h */

#define _FNV_PRIME 0x00000100000001B3
#define _FNV_OFFSET_BASIS 0xcbf29ce484222325

unsigned long int _fnv1a(unsigned char *data, size_t data_size)
{
    size_t i;
    unsigned long hash;

    hash = _FNV_OFFSET_BASIS;
    for (i = 0; i < data_size; i++)
        hash = (hash ^ data[i]) * _FNV_PRIME;
    return hash;
}

char _eq(unsigned char *a, unsigned char *b, size_t size)
{
    int i;

    for (i = 0; i < size; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void _collections_map_alloc(void ***keys, void ***vals, size_t cap, size_t **b_len)
{
    *keys = calloc(cap, sizeof *keys),
    *vals = calloc(cap, sizeof *vals),
    *b_len = calloc(cap, sizeof *b_len);
}

void _collections_map_free_all(void **a, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++)
        free(a[i]);
}

size_t _bucket_index(void *key, size_t cap, size_t key_size)
{
    return _fnv1a(key, key_size) % cap;
}

size_t _find_key(size_t i, void *key, void **keys, size_t *b_len, size_t key_size)
{
    size_t j;

    for (j = 0; j < b_len[i]; j++)
        if (_eq(keys[i] + j * key_size, key, key_size))
            return j;
    return b_len[i];
}

void _bucket_append(size_t i, void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t key_size, size_t val_size)
{
    keys[i] = realloc(keys[i], (b_len[i] + 1) * key_size),
    vals[i] = realloc(vals[i], (b_len[i] + 1) * val_size),
    memcpy(keys[i] + b_len[i] * key_size, key, key_size),
    memset(vals[i] + b_len[i] * val_size, 0, val_size),
    b_len[i]++,
    (*len)++;
}

void _collections_map_check_key(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t flag[2], size_t key_size, size_t val_size)
{
    flag[0] = _bucket_index(key, cap, key_size);
    flag[1] = _find_key(flag[0], key, keys, b_len, key_size);
    if (flag[1] >= b_len[flag[0]])
        _bucket_append(flag[0], key, keys, vals, len, cap, b_len, key_size, val_size);
}

void _move_data(void **keys, void **vals, size_t *b_len, size_t cap, void **old_keys, void **old_vals, size_t *old_b_len, size_t old_cap, size_t key_size, size_t val_size)
{
    size_t i, j, flag[2], t;

    for (i = 0; i < old_cap; i++)
        for (j = 0; j < old_b_len[i]; j++)
        {
            _collections_map_check_key(old_keys[i] + j * key_size, keys, vals, &t, cap, b_len, flag, key_size, val_size);
            memcpy(vals[flag[0]] + flag[1] * val_size, old_vals[i] + j * val_size, val_size);
        }

    _collections_map_free_all(old_keys, old_cap);
    _collections_map_free_all(old_vals, old_cap);
    free(old_keys);
    free(old_vals);
    free(old_b_len);
}

void _collections_map_check_load(void ***keys, void ***vals, size_t len, size_t *cap, size_t **b_len, size_t key_size, size_t val_size)
{
    void **new_keys, **new_vals;
    size_t new_cap, *new_b_len;

    new_cap = *cap;
    if (*cap == 0)
        new_cap = _LOAD_FACTOR_DEN;
    else if (len >= *cap * _LOAD_FACTOR_NUM / _LOAD_FACTOR_DEN)
        new_cap = *cap < 4096 ? *cap * 2 : *cap + _LOAD_FACTOR_DEN;

    if (new_cap != *cap)
    {
        _collections_map_alloc(&new_keys, &new_vals, new_cap, &new_b_len);
        _move_data(new_keys, new_vals, new_b_len, new_cap, *keys, *vals, *b_len, *cap, key_size, val_size);

        *keys = new_keys,
        *vals = new_vals,
        *cap = new_cap,
        *b_len = new_b_len;
    }
}

char _collections_map_has(void *key, void **keys, size_t cap, size_t *b_len, size_t key_size)
{
    size_t i, j;

    if (cap == 0)
        return 0;

    i = _bucket_index(key, cap, key_size),
    j = _find_key(i, key, keys, b_len, key_size);
    return j < b_len[i];
}

void _collections_map_del(void *key, void **keys, void **vals, size_t *len, size_t cap, size_t *b_len, size_t key_size, size_t val_size)
{
    size_t i, j, k;

    if (cap == 0)
        return;
    i = _bucket_index(key, cap, key_size),
    j = _find_key(i, key, keys, b_len, key_size);
    if (j == b_len[i])
        return;

    for (k = j + 1; k < b_len[i]; k++)
    {
        memcpy(keys[i] + (k - 1) * key_size, keys[i] + k * key_size, key_size);
        memcpy(vals[i] + (k - 1) * val_size, vals[i] + k * val_size, val_size);
    }
    b_len[i]--;
    (*len)--;
}

void _collections_map_iter_next(struct map_iter *it, size_t cap, size_t *b_len)
{
    if (it->j + 1 < b_len[it->i])
        it->j++;
    else
        do
            it->i++, it->j = 0;
        while (it->i < cap && b_len[it->i] == 0);
}
