# slice
Dynamic Array, which can be sliced into parts.
1. Declare a slice.
    ```c
    struct my_slice
    {
        my_item_type SLICE_DATA;
        SLICE_HANDLER;
    };
    ```
2. Allocate some memory.
    - Pre-allocate memory and initialize the structure.
        ```c
        SLI_MAKE(sli, len, cap)
        ```
    - Free the memory and clear the structure.
        ```c
        SLI_FREE(sli)
        ```
3. Use the slice.
    - Accessing from array header.
        ```c
        A(sli, i) = val
        ```
        works like
        ```go
        sli[i] = val
        ```
    - Get properties.
        ```c
        LEN(sli)
        CAP(sli)
        ```
    - Append.
        ```c
        APPEND(sli, val)
        ```
    - Slicing.
        ```c
        SLICE(sli, a, b)
        ```
        works like
        ```go
        sli = sli[a:b]
        ```

---

### Tips
- It is valid to take address of any accessing `A(sli, i)`, for future indexing with brackets. Example:
    ```c
    a = &A(sli, 0);
    a[1] = 2;
    ```
    But the pointer may be invalidate as soon as next modification, like `APPEND(sli, val)` and `SLICE(sli, a, b)`.
- The memory allocated for each item is up to you, iterate over it and free them if necessary.