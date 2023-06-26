# heap
Heap (Priority Queue), based on slice.
1. Define data structure.
    ```c
    struct my_heap
    {
        my_item_type SLI_DATA;
        SLI_HANDLER;
        HEAP_HANDLER;
    };
2. Deal with memory: Refer to [chiyoi/slice](https://github.com/chiyoi/slice).
3. Initialize the structure.
    ```c
    HEAP_INIT(h, compare)
    ```
    Where `compare` is the compare function for the elements.
4. Access data.
    - Push.
        ```c
        HEAP_PUSH(h, val)
        ```
    - Peak and pop.
        ```c
        val = HEAP_PEAK(h)
        val = HEAP_POP(h, out)
        ```
        Where `out` is an temporary variable to store the pop output.

---

### Tips
- The heap operations are based on a dynamic array from [chiyoi/slice](https://github.com/chiyoi/slice), so the operations for that is available.
- The `compare` function has the same signature as `qsort` in `stdlib.h`. You can store a pointer to the necessary data in each element, like performing capture in other languages.
- The `out` for `HEAP_POP` can be the same as the variable receiving the answer. Example:
    ```c
    val = HEAP_POP(h, val)
    ```
    But in this case, the receiving is redundant. Just use:
    ```c
    HEAP_POP(h, val)
    ```
