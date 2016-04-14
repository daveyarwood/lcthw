#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include <stdlib.h>
#include <lcthw/list.h>

// TODO: define List_compare (comparator) type (fn pointer?)
// need to be able to cast things like strcmp to it

/*
 * Sorts `list` in place using the bubble sort algorithm.
 *
 * Returns 0 if successful.
 */
int List_bubble_sort(List* list, List_compare comparator);

/*
 * Sorts `list` without modifying it, returning a new list that has been
 * sorted using the merge sort algorithm.
 */
List* List_merge_sort(List* list, List_compare comparator);

#endif
