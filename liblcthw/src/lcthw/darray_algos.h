#ifndef darray_algos_h
#define darray_algos_h

#include <lcthw/darray.h>

typedef int (*DArray_compare)(const void* a, const void* b);

int DArray_qsort(DArray* array, DArray_compare comparator);

int DArray_heapsort(DArray* array, DArray_compare comparator);

int DArray_mergesort(DArray* array, DArray_compare comparator);

#endif
