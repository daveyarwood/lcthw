#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char* values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

List* create_words() {
  List* words = List_create();

  for (int i = 0; i < NUM_VALUES; i++) {
    List_push(words, values[i]);
  }

  return words;
}

int is_sorted(List* words) {
  LIST_FOREACH(words, first, next, cur) {
    if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
      debug("Out of order: %s %s",
            (char*)cur->value, (char*)cur->next->value);
      return 0;
    }
  }

  return 1;
}

char* test_bubble_sort() {
  List* words = create_words();

  // should work on a list that needs sorting
  int rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort failed.");
  mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

  // should work on an already sorted list
  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort of already sorted list failed.");
  mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

  List_destroy(words);

  // should work on an empty list
  words = List_create();
  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort failed on empty list.");
  mu_assert(is_sorted(words), "Words should be sorted if empty.");

  List_destroy(words);

  return NULL;
}

char* test_merge_sort() {
  List* words = create_words();

  // should work on a list that needs sorting
  List* res = List_merge_sort(words, (List_compare)strcmp);
  mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

  List* res2 = List_merge_sort(res, (List_compare)strcmp);
  mu_assert(is_sorted(res2), "Words are not sorted after merge sort.");

  List_destroy(res2);
  List_destroy(res);
  List_destroy(words);

  return NULL;
}

char* test_insert_sorted() {
  List* list = List_create();

  // should insert into an empty list
  List_insert_sorted(list, "xxxx", (List_compare)strcmp);
  mu_assert(List_count(list) == 1, "List_insert_sorted didn't increment the count from 0 to 1.");
  mu_assert(List_first(list) == "xxxx", "List_insert_sorted didn't insert \"xxxx\" into the list.");

  // should insert values into the list in sort order
  List_insert_sorted(list, "zzzz", (List_compare)strcmp);
  List_insert_sorted(list, "f", (List_compare)strcmp);
  List_insert_sorted(list, "abcd", (List_compare)strcmp);
  List_insert_sorted(list, "aaaa", (List_compare)strcmp);
  List_insert_sorted(list, "dddd", (List_compare)strcmp);
  List_insert_sorted(list, "zxyw", (List_compare)strcmp);

  mu_assert(is_sorted(list), "Items out of order after List_insert_sorted.");

  return NULL;
}

char* all_tests() {
  mu_suite_start();

  mu_run_test(test_bubble_sort);
  mu_run_test(test_merge_sort);
  mu_run_test(test_insert_sorted);

  return NULL;
}

RUN_TESTS(all_tests);
