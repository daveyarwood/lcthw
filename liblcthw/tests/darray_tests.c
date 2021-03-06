#include "minunit.h"
#include <lcthw/darray.h>

char* test_create_destroy() {
  DArray* array = DArray_create(sizeof(int), 100);

  mu_assert(array != NULL, "DArray_create failed.");
  mu_assert(array->contents != NULL, "array->contents is NULL");
  mu_assert(array->end == 0, "array->end should be 0 upon creation");
  mu_assert(array->element_size == sizeof(int), "element size is wrong");
  mu_assert(array->max == 100, "wrong max length on initial size");

  DArray_destroy(array);

  return NULL;
}

char* test_new_set_get() {
  DArray* array = DArray_create(sizeof(int), 100);

  int* val1 = DArray_new(array);
  mu_assert(val1 != NULL, "failed to make a new element");

  int* val2 = DArray_new(array);
  mu_assert(val2 != NULL, "failed to make a new element");


  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
  mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");

  return NULL;
}

char* test_remove() {
  DArray* array = DArray_create(sizeof(int), 100);
  int* val1 = DArray_new(array);
  int* val2 = DArray_new(array);
  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  int* val_check = DArray_remove(array, 0);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val1, "Should get the first value.");
  mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
  DArray_free(val_check);

  val_check = DArray_remove(array, 1);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val2, "Should get the first value.");
  mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
  DArray_free(val_check);

  return NULL;
}

char* test_expand_contract() {
  DArray* array = DArray_create(sizeof(int), 100);

  int old_max = array->max;
  DArray_expand(array);
  mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand.");

  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");

  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");

  return NULL;
}

char* test_push_pop() {
  DArray* array = DArray_create(sizeof(int), 100);
  DArray_contract(array);

  int i = 0;
  for (i = 0; i < 1000; i++) {
    int* val = DArray_new(array);
    *val = i * 333;
    DArray_push(array, val);
  }

  mu_assert(array->max == 1201, "Wrong max size.");

  for (i = 999; i >= 0; i--) {
    int* val = DArray_pop(array);
    mu_assert(val != NULL, "Shouldn't get a NULL.");
    mu_assert(*val == i * 333, "Wrong value.");
    DArray_free(val);
  }

  return NULL;
}

char* all_tests() {
  mu_suite_start();

  mu_run_test(test_create_destroy);
  mu_run_test(test_new_set_get);
  mu_run_test(test_remove);
  mu_run_test(test_expand_contract);
  mu_run_test(test_push_pop);

  return NULL;
}

RUN_TESTS(all_tests);
