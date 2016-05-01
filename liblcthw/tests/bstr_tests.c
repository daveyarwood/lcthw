#include "minunit.h"
#include <lcthw/bstrlib.h>

char* test_bfromcstr() {

  return NULL;
}

char* test_blk2bstr() {

  return NULL;
}

char* test_bstrcpy() {

  return NULL;
}

char* test_bassign() {

  return NULL;
}

char* test_bassigncstr() {

  return NULL;
}

char* test_bassignblk() {

  return NULL;
}

char* test_bdestroy() {

  return NULL;
}

char* test_bconcat() {

  return NULL;
}

char* test_bstricmp() {

  return NULL;
}

char* test_biseq() {

  return NULL;
}

char* test_binstr() {

  return NULL;
}

char* test_bfindreplace() {

  return NULL;
}

char* test_bsplit() {

  return NULL;
}

char* test_bformat() {

  return NULL;
}

char* test_blength() {

  return NULL;
}

char* test_bdata() {

  return NULL;
}

char* test_bchar() {

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
  mu_run_test(test_bsplit);
  mu_run_test(test_bformat);
  mu_run_test(test_blength);
  mu_run_test(test_bdata);
  mu_run_test(test_bchar);

  return NULL;
}

RUN_TESTS(all_tests);
