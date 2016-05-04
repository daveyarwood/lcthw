#include "minunit.h"
#include <lcthw/bstrlib.h>

char* test_bfromcstr() {
  char* c1 = "testing 1 2 3";
  bstring b = bfromcstr(c1);
  mu_assert(biseqcstr(b, c1), "bstring is not equal to cstring");

  char* c2 = bstr2cstr(b, '\0');
  mu_assert(strcmp(c1, c2) == 0, "Round trip conversion from/to C-string didn't work.");

  bdestroy(b);

  return NULL;
}

char* test_blk2bstr() {
  char* c1 = "testing 1 2 3";
  bstring b = blk2bstr(c1, strlen(c1));
  mu_assert(biseqcstr(b, c1), "bstring is not equal to cstring");

  char* c2 = bstr2cstr(b, '\0');
  mu_assert(strcmp(c1, c2) == 0, "Round trip conversion from/to 'block' didn't work.");

  bdestroy(b);

  return NULL;
}

char* test_bstrcpy() {
  bstring b1 = bfromcstr("aoeuaoeuaoeu");
  bstring b2 = bstrcpy(b1);
  mu_assert(biseq(b1, b2), "Copied bstring is not equal to original bstring.");

  bdestroy(b1);
  bdestroy(b2);

  return NULL;
}

char* test_bassign() {
  bstring a = bfromcstr("foobarbaz");
  bstring b = bfromcstr("onetwothree");
  int rc = bassign(a, b);
  mu_assert(rc != BSTR_ERR, "Error using bassign.");
  mu_assert(biseq(a, b), "a != b after bassigning b to a");

  bdestroy(a);
  bdestroy(b);

  return NULL;
}

char* test_bassigncstr() {
  bstring a = bfromcstr("foobarbaz");
  char* b = "onetwothree";
  int rc = bassigncstr(a, b);
  mu_assert(rc != BSTR_ERR, "Error using bassigncstr.");
  mu_assert(biseqcstr(a, b), "a != b after bassigncstr-ing b to a");

  bdestroy(a);

  return NULL;
}

char* test_bassignblk() {
  bstring a = bfromcstr("foobarbaz");
  char* b = "onetwothree";
  int rc = bassignblk(a, b, strlen(b));
  mu_assert(rc != BSTR_ERR, "Error using bassignblk.");
  mu_assert(biseqblk(a, b, strlen(b)), "a != b after bassignblk-ing b to a");

  bdestroy(a);

  return NULL;
}

char* test_bdestroy() {
  bstring x = bfromcstr("heeeeeeeeeeey");
  int rc = bdestroy(x);
  mu_assert(rc != BSTR_ERR, "Error destroying bstring.");

  return NULL;
}

char* test_bconcat() {
  bstring a = bfromcstr("abso");
  bstring b = bfromcstr("lutely");

  int rc = bconcat(a, b);
  mu_assert(rc == BSTR_OK, "Failed to bconcat b to a.");
  mu_assert(biseqcstr(a, "absolutely"), "bconcat didn't work");

  bdestroy(a);
  bdestroy(b);

  return NULL;
}

char* test_bstricmp() {
  bstring a = bfromcstr("cheers");
  bstring b = bfromcstr("cheers");
  bstring c = bfromcstr("CHEERS");
  bstring d = bfromcstr("ChEeRS");
  bstring e = bfromcstr("chores");

  mu_assert(bstricmp(a, a) == 0, "bstricmp a bstring with itself should be true");
  mu_assert(bstricmp(a, b) == 0, "bstricmp not working");
  mu_assert(bstricmp(a, c) == 0, "bstricmp not working");
  mu_assert(bstricmp(a, d) == 0, "bstricmp not working");
  mu_assert(bstricmp(a, e) != 0, "bstricmp not working");

  bdestroy(a);
  bdestroy(b);
  bdestroy(c);
  bdestroy(d);
  bdestroy(e);

  return NULL;
}

char* test_biseq() {
  bstring a = bfromcstr("foo");
  bstring b = bfromcstr("foo");
  bstring c = bfromcstr("bar");

  int rc = biseq(a, b);
  mu_assert(rc != -1, "biseq error");
  mu_assert(rc, "foo should equal foo");

  rc = biseq(a, c);
  mu_assert(rc != -1, "biseq error");
  mu_assert(!rc, "foo should NOT equal bar");

  bdestroy(a);
  bdestroy(b);
  bdestroy(c);

  return NULL;
}

char* test_binstr() {
  bstring helloWorld = bfromcstr("hello world");
  bstring world = bfromcstr("world");
  bstring goodbye = bfromcstr("goodbye");

  int result = binstr(helloWorld, 0, world);
  mu_assert(result != BSTR_ERR, "world not found in hello world");
  mu_assert(result == 6, "world not found at the right index in hello world");

  result = binstr(helloWorld, 8, world);
  mu_assert(result == BSTR_ERR, "world somehow found in rld");

  result = binstr(helloWorld, 0, goodbye);
  mu_assert(result == BSTR_ERR, "goodbye somehow found in hello world");

  bdestroy(helloWorld);
  bdestroy(world);
  bdestroy(goodbye);

  return NULL;
}

char* test_bfindreplace() {
  // example stolen from _why's poignant guide to ruby
  char* song_c = "I swiped your cat / And I stole your cathodes";
  bstring song = bfromcstr(song_c);
  bstring cat = bfromcstr("cat");
  bstring banjo = bfromcstr("banjo");

  int rc = bfindreplace(song, cat, banjo, 0);
  mu_assert(rc != BSTR_ERR, "bfindreplace error");
  mu_assert(biseqcstr(song, "I swiped your banjo / And I stole your banjohodes"),
            "Unexpected bfindreplace result");

  bassigncstr(song, song_c);
  rc = bfindreplace(song, cat, banjo, 20);
  mu_assert(rc != BSTR_ERR, "bfindreplace error");
  mu_assert(biseqcstr(song, "I swiped your cat / And I stole your banjohodes"),
            "Unexpected bfindreplace result");

  bdestroy(song);
  bdestroy(cat);
  bdestroy(banjo);

  return NULL;
}

char* test_bsplit_bjoin() {
  char* c = "one,two,three,four";
  bstring x = bfromcstr(c);
  struct bstrList* split = bsplit(x, ',');

  mu_assert(split->qty == 4, "list created via bsplit has the wrong number of strings");

  bstring comma = bfromcstr(",");
  bstring joined = bjoin(split, comma);
  mu_assert(biseqcstr(joined, c), "round trip bsplit/bjoin failed");

  bdestroy(x);
  bdestroy(comma);
  bdestroy(joined);
  bstrListDestroy(split);

  return NULL;
}

char* test_bformat() {
  bstring x = bformat("My name is %s and I am %d years old.", "Dave", 30);
  mu_assert(biseqcstr(x, "My name is Dave and I am 30 years old."),
            "bformat failed");

  bdestroy(x);

  return NULL;
}

char* test_blength() {
  bstring null_bstr = NULL;
  mu_assert(blength(null_bstr) == 0, "blength of NULL should be 0");

  bstring x = bfromcstr("o hai");
  mu_assert(blength(x) == 5, "unexpected blength result");

  bdestroy(x);

  return NULL;
}

char* test_bdata() {
  bstring null_bstr = NULL;
  mu_assert(bdata(null_bstr) == NULL, "bdata of NULL should be NULL");

  bstring x = bfromcstr("o hai");
  mu_assert(strcmp(bdata(x), "o hai") == 0, "unexpected bdata result");

  bdestroy(x);

  return NULL;
}

char* test_bchar() {
  bstring null_bstr = NULL;
  mu_assert(bchar(null_bstr, 42) == '\0',
            "bchar should return null char for any position of a NULL bstring");

  bstring x = bfromcstr("o hai");
  mu_assert(bchar(x, 0) == 'o', "unexpected bchar result");
  mu_assert(bchar(x, 1) == ' ', "unexpected bchar result");
  mu_assert(bchar(x, 2) == 'h', "unexpected bchar result");
  mu_assert(bchar(x, 3) == 'a', "unexpected bchar result");
  mu_assert(bchar(x, 4) == 'i', "unexpected bchar result");
  mu_assert(bchar(x, 5) == '\0', "unexpected bchar result");
  mu_assert(bchar(x, 42) == '\0', "unexpected bchar result");

  bdestroy(x);

  return NULL;
}

char* all_tests() {
  mu_suite_start();

  mu_run_test(test_bfromcstr);
  mu_run_test(test_blk2bstr);
  mu_run_test(test_bstrcpy);
  mu_run_test(test_bassign);
  mu_run_test(test_bassigncstr);
  mu_run_test(test_bassignblk);
  mu_run_test(test_bdestroy);
  mu_run_test(test_bconcat);
  mu_run_test(test_bstricmp);
  mu_run_test(test_biseq);
  mu_run_test(test_binstr);
  mu_run_test(test_bfindreplace);
  mu_run_test(test_bsplit_bjoin);
  mu_run_test(test_bformat);
  mu_run_test(test_blength);
  mu_run_test(test_bdata);
  mu_run_test(test_bchar);

  return NULL;
}

RUN_TESTS(all_tests);
