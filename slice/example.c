#include <stdio.h>
#include <stdlib.h>

#include "slice.h"

struct slice_int
{
    int SLICE_DATA;
    SLICE_HANDLER;
};

void show(struct slice_int sli)
{
    int i;
    int *a;

    a = &A(sli, 0);
    if (LEN(sli) == 0)
        printf("[] .off(%zu) len(0) cap(%zu)\n", sli.off, CAP(sli));
    else
    {
        printf("[");
        for (i = 0; i < LEN(sli) - 1; i++)
            printf("%d ", a[i]);
        printf("%d] .off(%zu) len(%zu) cap(%zu)\n", a[LEN(sli) - 1], sli.off, LEN(sli), CAP(sli));
    }
}

void show_array_int(int *arr, int arrLen)
{
    int i;

    if (arrLen == 0)
    {
        printf("[]\n");
        return;
    }
    printf("[");
    for (i = 0; i < arrLen - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d]\n", arr[arrLen - 1]);
}

int less(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    struct slice_int sli = {}, t;
    int *arr, arrLen;

    /* APPEND on zero slice is valid. */
    APPEND(sli, 1);
    show(sli);
    APPEND(sli, 2);
    show(sli);
    APPEND(sli, 3);
    show(sli);
    SLICE(sli, 1, 2);
    show(sli);
    SLI_FREE(sli);
    show(sli);
    printf("\n");

    /* Use MAKE to pre-allocate memory */
    SLI_MAKE(sli, 1, 2);
    A(sli, 0) = 1;
    show(sli);
    APPEND(sli, 2);
    show(sli);
    APPEND(sli, 3);
    show(sli);
    SLICE(sli, 1000, 100000);
    show(sli);
    SLI_FREE(sli);
    show(sli);

    /* We can change the owner of the underlying data by just copying it. */
    SLI_MAKE(sli, 10, 20);
    t = sli;
    /* Caution: there should be only one owner because we did not
       use reference counter. By memset to zero to reset the slice. */
    memset(&sli, 0, sizeof sli);
    SLI_MAKE(sli, 5, 10);
    show(t);
    show(sli);
    SLI_FREE(t);
    SLI_FREE(sli);

    /* Example to get the head-pointer and the item-size without accessing "private" fields.
       Caution: the head-pointer maybe not a valid address to `free`. */
    SLI_MAKE(sli, 5, 5);
    arr = &A(sli, 0);
    arr[0] = 3, arr[1] = 5, arr[2] = 2, arr[3] = 1, arr[4] = 4;
    show(sli);
    qsort(&A(sli, 0), LEN(sli), sizeof A(sli, 0), less);
    show(sli);
    SLI_FREE(sli);

    /* works like */
    arr = calloc(5, sizeof *arr);
    arrLen = 5;
    arr[0] = 3, arr[1] = 5, arr[2] = 2, arr[3] = 1, arr[4] = 4;
    show_array_int(arr, arrLen);
    qsort(&arr[0], arrLen, sizeof *arr, less);
    show_array_int(arr, arrLen);
    free(arr);
}
