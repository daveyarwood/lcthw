#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int List_bubble_sort(List* list, List_compare comparator) {
  if (List_is_empty(list)) {
    return 0;
  }

  int swapped_something = 0;

  // When we swap two list nodes, we're modifying the list in place. On the
  // next iteration, we'll end up on the node we just swapped. We want to skip
  // it though, and move on to the next node.
  //
  // So, when we swap, we set just_swapped = 1 for the next iteration, so that
  // the next node will be skipped.
  int just_swapped = 0;

  LIST_FOREACH(list, first->next, next, cur) {
    if (!just_swapped) {
      if (comparator(cur->value, cur->prev->value) < 0) {
        List_swap(list, cur, cur->prev);
        just_swapped = 1;
        swapped_something = 1;
      }
    } else {
      just_swapped = 0;
    }
  }

  // Recursively bubble sort the list until it's in order.
  if (swapped_something) {
    List_bubble_sort(list, comparator);
  }

  return 0;
}

void _split_list_in_half(List* list, List** a, List** b) {
  *a = List_create();
  *b = List_create();

  for (int i = 0; i < List_count(list); i++) {
    if (i % 2 == 0) {
      List_push(*a, List_shift(list));
    } else {
      List_push(*b, List_shift(list));
    }
  }

  List_destroy(list);
}

List* _merge_sorted_lists(List* result, List* a, List* b, List_compare comparator) {
  if (List_is_empty(a) && List_is_empty(b)) {
    List_destroy(a);
    List_destroy(b);
    return result;
  }

  if (List_is_empty(a)) {
    while (!List_is_empty(b)) {
      List_push(result, List_shift(b));
    }
    List_destroy(a);
    List_destroy(b);
    return result;
  }

  if (List_is_empty(b)) {
    while (!List_is_empty(a)) {
      List_push(result, List_shift(a));
    }
    List_destroy(a);
    List_destroy(b);
    return result;
  }

  if (comparator(a->first->value, b->first->value) < 0) {
    List_push(result, List_shift(a));
  } else {
    List_push(result, List_shift(b));
  }

  return _merge_sorted_lists(result, a, b, comparator);
}

List* List_merge_sort(List* list, List_compare comparator) {
  List* list_copy = List_copy(list);

  if (List_count(list_copy) <= 1) {
    return list;
  }

  List* a;
  List* b;
  _split_list_in_half(list_copy, &a, &b);

  a = List_merge_sort(a, comparator);
  b = List_merge_sort(b, comparator);

  return _merge_sorted_lists(List_create(), a, b, comparator);
}

void List_insert_sorted(List* list, void* value, List_compare comparator) {
  if (List_is_empty(list)) {
    List_push(list, value);
    return;
  }

  ListNode* node = list->first;

  while (comparator(value, node->value) > 0 && node->next != NULL) {
    node = node->next;
  }

  if (comparator(value, node->value) > 0 && node->next == NULL) {
    List_push(list, value);
  } else {
    List_insert_before(list, node, value);
  }
}
