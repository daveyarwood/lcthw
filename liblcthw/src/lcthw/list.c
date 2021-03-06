#include <lcthw/list.h>
#include <lcthw/dbg.h>

ListNode* ListNode_create(void* value) {
  ListNode* node = calloc(1, sizeof(ListNode));
  check_mem(node);
  node->value = value;
  return node;

error:
  return NULL;;
}

List* List_create() {
  return calloc(1, sizeof(List));
}

void List_validate(List* list) {
  check(list != NULL, "List is NULL.");
  check(list->count >= 0, "List has a negative count.");

  if (list->count > 0) {
    check(list->first != NULL, "List has at least one item, but the first item is NULL.");
  }

error:
  return;
}

void _clear_and_or_destroy(List* list, int clear, int destroy) {
  List_validate(list);

  if (List_is_empty(list)) {
    free(list);
    return;
  }

  LIST_FOREACH(list, first->next, next, cur) {
    if (destroy) {
      free(cur->prev);
    } else if (clear) {
      free(cur->prev->value);
    }
  }

  if (destroy) {
    free(list->last);
    free(list);
  } else if (clear) {
    free(list->last->value);
  }
}

void List_clear(List* list) {
  _clear_and_or_destroy(list, 1, 0);
}

void List_destroy(List* list) {
  _clear_and_or_destroy(list, 0, 1);
}

void List_clear_destroy(List* list) {
  _clear_and_or_destroy(list, 1, 1);
}

List* List_copy(List* list) {
  List_validate(list);

  List* list_copy = List_create();

  for (int i = 0; i < List_count(list); i++) {
    List_push(list_copy, List_at(list, i));
  }

  return list_copy;
}

void* List_at(List* list, int i) {
  List_validate(list);

  if (i < 0 || i >= List_count(list)) {
    return NULL;
  }

  ListNode* node = list->first;

  while (i > 0) {
    node = node->next;
    i--;
  }

  return node->value;
}

int List_is_empty(List* list) {
  return List_count(list) == 0;
}

int List_equal(List* a, List* b) {
  if (List_count(a) != List_count(b)) {
    return 0;
  }

  ListNode* a_node = a->first;
  ListNode* b_node = b->first;

  for (int i = 0; i < List_count(a); i++) {
    if (a_node->value != b_node->value) {
      return 0;
    }
    a_node = a_node->next;
    b_node = b_node->next;
  }

  return 1;
}

void List_push(List* list, void* value) {
  List_validate(list);

  ListNode* node = ListNode_create(value);

  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;
}

void* List_pop(List* list) {
  List_validate(list);

  ListNode* node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List* list, void* value) {
  List_validate(list);

  ListNode* node = ListNode_create(value);

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;
}

void* List_shift(List* list) {
  List_validate(list);

  ListNode* node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
}

void List_insert_before(List* list, ListNode* node, void* value) {
  ListNode* new_node = ListNode_create(value);

  if (node->prev != NULL) {
    node->prev->next = new_node;
  } else {
    list->first = new_node;
  }

  new_node->prev = node->prev;
  new_node->next = node;

  node->prev = new_node;

  list->count++;
}

void* List_remove(List* list, ListNode* node) {
  List_validate(list);

  void* result = NULL;

  check(list->first && list->last, "List is empty.");
  check(node, "node can't be NULL");

  if (node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
    list->last->next = NULL;
  } else {
    ListNode* after = node->next;
    ListNode* before = node->prev;
    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

error:
  return result;
}

void List_swap(List* list, ListNode* a, ListNode* b) {
  List_validate(list);
  check(a != NULL && b != NULL, "List_swap failed: one or both nodes is NULL.");

  void* a_value = a->value;
  a->value = b->value;
  b->value = a_value;

error:
  return;
}
