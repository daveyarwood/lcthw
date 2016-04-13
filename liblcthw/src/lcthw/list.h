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

/* Helper macro for iterating through the items in a list. */
#define LIST_FOREACH(L, S, M, V) \
  ListNode* _node = NULL; \
  ListNode* V = NULL; \
  for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
