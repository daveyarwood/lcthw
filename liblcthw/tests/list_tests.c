#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

char* test1 = "test1 data";
char* test2 = "test2 data";
char* test3 = "test3 data";

char* test_create() {
  List* list = List_create();
  mu_assert(list != NULL, "Failed to create list.");

  return NULL;
}

char* test_destroy() {
  List* list = List_create();
  List_clear_destroy(list);

  return NULL;
}

char* test_push_pop() {
  List* list = List_create();
  mu_assert(List_count(list) == 0, "Initial count isn't zero.");

  List_push(list, test1);
  mu_assert(List_last(list) == test1, "Wrong last value.");
  mu_assert(List_count(list) == 1, "Wrong count on push.");

  List_push(list, test2);
  mu_assert(List_last(list) == test2, "Wrong last value.");
  mu_assert(List_count(list) == 2, "Wrong count on push.");

  List_push(list, test3);
  mu_assert(List_last(list) == test3, "Wrong last value.");
  mu_assert(List_count(list) == 3, "Wrong count on push.");

  char* val = List_pop(list);
  mu_assert(val == test3, "Wrong value on pop.");
  mu_assert(List_count(list) == 2, "Wrong count after pop.");

  val = List_pop(list);
  mu_assert(val == test2, "Wrong value on pop.");
  mu_assert(List_count(list) == 1, "Wrong count after pop.");

  val = List_pop(list);
  mu_assert(val == test1, "Wrong value on pop.");
  mu_assert(List_count(list) == 0, "Wrong count after pop.");

  return NULL;
}

char* test_unshift() {
  List* list = List_create();

  List_unshift(list, test1);
  mu_assert(List_first(list) == test1, "Wrong first value.");
  mu_assert(List_count(list) == 1, "Wrong count on unshift.");

  List_unshift(list, test2);
  mu_assert(List_first(list) == test2, "Wrong first value.");
  mu_assert(List_count(list) == 2, "Wrong count on unshift.");

  List_unshift(list, test3);
  mu_assert(List_first(list) == test3, "Wrong first value.");
  mu_assert(List_count(list) == 3, "Wrong count on unshift.");

  return NULL;
}

char* test_remove() {
  List* list = List_create();
  List_unshift(list, test1);
  List_unshift(list, test2);
  List_unshift(list, test3);

  char* val = List_remove(list, list->first->next);
  mu_assert(val == test2, "Wrong removed element.");
  mu_assert(List_count(list) == 2, "Wrong count after remove.");
  mu_assert(List_first(list) == test3, "Wrong first after remove.");
  mu_assert(List_last(list) == test1, "Wrong last after remove.");

  return NULL;
}

char* test_shift() {
  List* list = List_create();
  List_unshift(list, test1);
  List_unshift(list, test3);

  mu_assert(List_count(list) == 2, "Wrong count before shift.");

  char* val = List_shift(list);
  mu_assert(val == test3, "Wrong value on shift.");
  mu_assert(List_count(list) == 1, "Wrong count after shift.");

  val = List_shift(list);
  mu_assert(val == test1, "Wrong value on shift.");
  mu_assert(List_count(list) == 0, "Wrong count after shift.");

  return NULL;
}

char* test_is_empty() {
  List* list = List_create();
  mu_assert(List_is_empty(list), "Empty list incorrectly reported as not empty.");

  List_push(list, "some value");
  mu_assert(!List_is_empty(list), "Non-empty list incorrectly reported as empty.");

  return NULL;
}

char* test_swap() {
  List* list = List_create();
  List_push(list, "one");
  List_push(list, "two");
  List_push(list, "three");

  printf("count before: %d\n", List_count(list));

  List_swap(list, list->first, list->last);
  printf("count after: %d\n", List_count(list));

  LIST_FOREACH(list, first, next, cur) {
    printf("%s\n", cur->value);
    if (cur->next && cur->next->value) {
      printf("next: %s\n", cur->next->value);
    }
  }

  mu_assert(list->first->value == "three", "List swap failed.");
  mu_assert(list->first->next->value == "two", "List swap failed.");
  mu_assert(list->last->value == "one", "List swap failed.");

  return NULL;
}

char* all_tests() {
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_destroy);
  mu_run_test(test_push_pop);
  mu_run_test(test_unshift);
  mu_run_test(test_remove);
  mu_run_test(test_shift);
  mu_run_test(test_is_empty);
  mu_run_test(test_swap);

  return NULL;
}

RUN_TESTS(all_tests);
