#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
  struct ListNode* next;
  struct ListNode* prev;
  void* value;
} ListNode;

typedef struct List {
  int count;
  ListNode* first;
  ListNode* last;
} List;

/* Creates a new list. */
List* List_create();

/*
 * Validates that `list` is a valid list.
 *
 * Validations include that the list is not NULL, that its count is a
 * non-negative number, and that if count > 0, the first item in the list is not
 * NULL.
 */
void List_validate(List* list);

/*
 * Frees the value of each item in `list`.
 */
void List_clear(List* list);

/*
 * Frees `list` along with all of its nodes.
 */
void List_destroy(List* list);

/*
 * Frees `list` along with all of its nodes and their values.
 */
void List_clear_destroy(List* list);

/*
 * Returns the number of items in the list.
 */
#define List_count(A) ((A)->count)

/* Returns the first item in the list. */
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)

/* Returns the last item in the list. */
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

/* Returns 1 if `list` is empty, else returns 0. */
int List_is_empty(List* list);

/* Adds a new item with the given `value` to the end of the `list`. */
void List_push(List* list, void* value);

/* Removes the last item in `list` and returns its value. */
void* List_pop(List* list);

/* Adds a new item with the given `value` onto the front of the `list`. */
void List_unshift(List* list, void* value);

/* Removes the first item in `list` and returns its value. */
void* List_shift(List* list);

/* Removes `node` from `list`. */
void* List_remove(List* list, ListNode* node);

/* Swaps the positions of list nodes `a` and `b` in `list`. */
void List_swap(List* list, ListNode* a, ListNode* b);

/*
 * Helper macro for iterating through the items in a list.
 *
 * L: the list being iterated through
 * S: the starting point, e.g. `first` (== list->first)
 * M: the point gone to on each iteration, e.g. `next` (== _node->next)
 * V: the local variable assigned to the current node on each iteration
 */

#define LIST_FOREACH(L, S, M, V) \
  ListNode* _node = NULL; \
  ListNode* V = NULL; \
  for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
