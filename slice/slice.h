#include <stdlib.h>
#include <string.h>

#ifndef SLICE_H
#define SLICE_H

#define SLICE_DATA (*data)
#define SLICE_HANDLER size_t off, len, cap

#define SLI_MAKE(sli, length, capacity) (0 <= (length) && (length) <= (capacity) && ((sli).data = calloc((capacity), sizeof *(sli).data)) != NULL ? ((sli).off = 0, (sli).len = (length), (sli).cap = (capacity), (void)0) : (void)0)
#define SLI_FREE(sli) (free((sli).data), memset(&(sli), 0, sizeof(sli)), (void)0)

#define A(sli, i) (sli).data[(sli).off + i]
#define APPEND(sli, val) ((sli).off + (sli).len <= (sli).cap && ((sli).off + (sli).len == (sli).cap ? ((sli).data = realloc((sli).data, ((sli).cap > 0 && (sli).cap < 65536 ? ((sli).cap *= 2) : ((sli).cap += 1)) * sizeof *(sli).data)) : (sli).data) != NULL ? ((sli).data[(sli).off + ((sli).len++)] = (val), (void)0) : (void)0)
#define SLICE(sli, a, b) ((a) < 0 ? ((sli).len = (b) < 0 ? 0 : ((b) < (sli).len ? (b) : (sli).len)) : ((a) < (sli).len ? ((sli).off += (a), (sli).len = (b) < (a) ? 0 : ((b) < (sli).len ? (b) - (a) : (sli).len)) : ((sli).off = (sli).len, (sli).len = 0)), (void)0)

#ifndef PROPERTY_ACCESS
#define PROPERTY_ACCESS
#define LEN(c) ((c).len)
#define CAP(c) ((c).cap)
#endif
#endif
