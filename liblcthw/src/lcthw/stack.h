#ifndef _lcthw_stack_h
#define _lcthw_stack_h

#include <lcthw/list.h>

typedef List Stack;

#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_clear List_clear
#define Stack_clear_destroy List_clear_destroy

#define Stack_push List_push
#define Stack_pop List_pop

#define Stack_count List_count
#define Stack_peek List_last

#define STACK_FOREACH(S, V) LIST_FOREACH(S, last, prev, V)

#endif
