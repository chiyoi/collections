# map
Hash Map, with FNV-1a hash algorithm.
1. Declare a map.
    ```c
    struct my_map
    {
        my_key_type MAP_KEY;
        my_val_type MAP_VAL;
        MAP_HANDLER;
    } m;
    ```
2. Allocate some memory.
    - Pre-allocate memory and initialize the structure.
        ```c
        MAP_MAKE(m, hint)
        ```
        `hint` is the minimum number of element the map could hold without growing.
    - Free the memory and clear the structure.
        ```c
        MAP_FREE(m)
        ```
3. Use the map.
    - Accessing the entry of a key.
        ```c
        E(m, key) = val
        ```
        works like
        ```go
        m[key] = val
        ```
        `key` should be addressable.
    - Check the existence of a key.
        ```c
        MAP_HAS(m, key)
        ```
    - Delete a key.
        ```c
        MAP_DEL(m, key)
        ```
    - Get Properties.
        ```c
        LEN(sli)
        CAP(sli)
        ```
        The capacity is the bucket count of the map, usually not a usable information.
4. Use map iterator.
    - Declare iterator.
        ```c
        struct map_iter it
        ```
    - Initiate iterator.
        ```c
        MAP_ITER_INIT(m, it)
        ```
    - Fetch next item.
        ```c
        ok = MAP_ITER_NEXT(m, it, key, val)
        ```
        `ok` indicates whether the iterator is exhausted.

---

### Tips
- When using `E(m, key)`, if there is no such key, an entry with zero value will be added into the map for the convince to assignment. But I can not get to know whether an assignment is happened, so if you do not want a zero entry to be inserted, you should check the existence with `MAP_HAS(m, key)` first.
- `MAP_FREE(m)` frees any memory allocated by me, but the memory for each key or value is up to you. Use iterator to free them sequentially if needed.
- When pre-allocating memory, the `hint` provided will be rounded to the nearest multiple of `_LOAD_FACTOR_DEN` which is the denominator of the load-factor, and the bucket count will always be a multiple of it.
