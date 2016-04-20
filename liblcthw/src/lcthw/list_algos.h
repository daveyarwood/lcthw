#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include <stdlib.h>
#include <lcthw/list.h>

/*
 * Function pointer to a comparator function which compares two things `a`
 * and `b` and returns < 0 if `a` comes before `b` in sort order, 0 if the
 * strings are equivalent in sort order, or > 0 if `b` comes before `a` in sort
 * order.
 */
typedef int (*List_compare)(void* a, void* b);

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

/*
 * Inserts a `value` into a `list` at the right position so that the list is in
 * sort order.
 *
 * Assumes the list is already sorted.
 */
void List_insert_sorted(List* list, void* value, List_compare comparator);

#endif
