# heap
Heap (Priority Queue), based on slice.
1. Define the heap.
    ```c
    struct my_heap
    {
        my_item_type SLI_DATA;
        SLI_HANDLER;
        HEAP_HANDLER;
    };
2. Manage memory: Refer to [chiyoi/slice](https://github.com/chiyoi/slice).
3. Use the heap.
    - Initialization.
        ```c
        HEAP_INIT(h, compare)
        ```
        Where `compare` is the compare function for the elements.
    - Push.
        ```c
        HEAP_PUSH(h, val)
        ```
    - Pop.
        ```c
        val = HEAP_POP(h, out)
        ```
        Where `out` is an temporary variable to store the pop output.
    - Fix a position to maintain the heap.
        ```c
        HEAP_FIX(h, i)
        ```

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
- The top element will appear on the `0` index, so you can use the interface from [chiyoi/slice](https://github.com/chiyoi/slice) to perform peek. Example:
    ```c
    val = A(h, 0)
    ```
