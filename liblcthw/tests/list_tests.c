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
  List_push(list, test1);
  List_push(list, test2);
  List_push(list, test3);

  List_swap(list, list->first, list->last);

  mu_assert(list->first->value == test3, "List swap failed.");
  mu_assert(list->first->next->value == test2, "List swap failed.");
  mu_assert(list->last->value == test1, "List swap failed.");

  return NULL;
}

char* test_at() {
  List* list = List_create();
  List_push(list, test1);
  List_push(list, test2);
  List_push(list, test3);

  mu_assert(List_at(list, 0) == test1, "List_at(list, 0) should be test1");
  mu_assert(List_at(list, 1) == test2, "List_at(list, 1) should be test2");
  mu_assert(List_at(list, 2) == test3, "List_at(list, 2) should be test3");
  mu_assert(List_at(list, 3) == NULL, "List_at(list, 3) should be NULL");
  mu_assert(List_at(list, 42) == NULL, "List_at(list, 42) should be NULL");

  return NULL;
}

char* test_equal() {
  List* list1 = List_create();
  List* list2 = List_create();

  mu_assert(List_equal(list1, list2), "Empty lists should be equal.");

  List_push(list1, test1);
  List_push(list1, test2);
  List_push(list1, test3);

  List_push(list2, test1);
  List_push(list2, test2);
  List_push(list2, test3);

  mu_assert(List_equal(list1, list2), "Lists with the same items should be equal.");

  List_pop(list1);

  mu_assert(!List_equal(list1, list2), "Lists with differing counts should not be equal.");

  List_push(list1, test3);

  mu_assert(List_equal(list1, list2), "Lists with the same items should be equal.");

  list1->last->value = "applesauce";

  mu_assert(!List_equal(list1, list2), "Lists with differing values should not be equal.");

  return NULL;
}

char* test_copy() {
  List* list = List_create();
  List_push(list, test1);
  List_push(list, test2);
  List_push(list, test3);

  List* list_copy = List_copy(list);

  mu_assert(List_equal(list, list_copy), "A copy of a list should be equal the list.");

  List* empty_list = List_create();
  List* empty_list_copy = List_copy(empty_list);

  mu_assert(List_equal(empty_list, empty_list_copy), "A copy of an empty list should be equal to the empty list.");

  return NULL;
}

char* test_insert_before() {
  List* list = List_create();
  List_push(list, test1);
  List_push(list, test2);
  List_push(list, test3);

  List_insert_before(list, list->first, "one");
  mu_assert(List_first(list) == "one", "\"one\" should have been inserted at the beginning of the list.");
  mu_assert(list->first->next->value == test1, "\"one\" should have been inserted before test1.");

  List_insert_before(list, list->first->next->next, "two");
  mu_assert(list->first->next->next->value == "two", "\"two\" should have been inserted before test2.");
  mu_assert(list->first->next->next->next->value == test2, "\"two\" should have been inserted before test2.");

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
  mu_run_test(test_at);
  mu_run_test(test_equal);
  mu_run_test(test_copy);
  mu_run_test(test_insert_before);

  return NULL;
}

RUN_TESTS(all_tests);
