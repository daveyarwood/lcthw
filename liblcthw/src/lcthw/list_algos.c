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

List* List_merge_sort(List* list, List_compare comparator) {

}
