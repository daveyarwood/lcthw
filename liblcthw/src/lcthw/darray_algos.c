#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray* array, DArray_compare comparator) {
  qsort(array->contents, DArray_count(array), sizeof(void*), comparator);
  return 0;
}

int DArray_heapsort(DArray* array, DArray_compare comparator) {
  heapsort(array->contents, DArray_count(array), sizeof(void*), comparator);
  return 0;
}

int DArray_mergesort(DArray* array, DArray_compare comparator) {
  mergesort(array->contents, DArray_count(array), sizeof(void*), comparator);
  return 0;
}

