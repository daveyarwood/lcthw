#ifndef string_algos_h
#define string_algos_h

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>

typedef struct StringScanner {
  bstring in;
  const unsigned char* haystack;
  ssize_t hlen;
  const unsigned char* needle;
  ssize_t nlen;
  size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;

/*
 * Find the first instance of `what` in `in`, doing the entire algorithm in one
 * shot.
 */
int String_find(bstring in, bstring what);

StringScanner* StringScanner_create(bstring in);

/*
 * Use a StringScanner state structure to separate the skip list build from the
 * actual find. (This is convenient for incrementally scanning, etc.)
 */
int StringScanner_scan(StringScanner* scan, bstring tofind);

void StringScanner_destroy(StringScanner* scan);

#endif
