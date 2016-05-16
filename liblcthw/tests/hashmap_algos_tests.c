#include <lcthw/bstrlib.h>
#include <lcthw/hashmap.h>
#include <lcthw/hashmap_algos.h>
#include "minunit.h"

struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");

char* test_fnv1a() {
  uint32_t hash = Hashmap_fnv1a_hash(&test1);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_fnv1a_hash(&test2);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_fnv1a_hash(&test3);
  mu_assert(hash != 0, "Bad hash.");

  return NULL;
}

char* test_adler32() {
  uint32_t hash = Hashmap_adler32_hash(&test1);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_adler32_hash(&test2);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_adler32_hash(&test3);
  mu_assert(hash != 0, "Bad hash.");

  return NULL;
}

char* test_djb() {
  uint32_t hash = Hashmap_djb_hash(&test1);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_djb_hash(&test2);
  mu_assert(hash != 0, "Bad hash.");

  hash = Hashmap_djb_hash(&test3);
  mu_assert(hash != 0, "Bad hash.");

  return NULL;
}

#define BUCKETS 100
#define BUFFER_LEN 20
#define NUM_KEYS BUCKETS * 1000

enum {
  ALGO_FNVIA,
  ALGO_ADLER32,
  ALGO_DJB
};

int gen_keys(DArray* keys, int num_keys) {
  FILE* urand = fopen("/dev/urandom", "r");
  check(urand != NULL, "Failed to open /dev/urandom");

  struct bStream* stream = bsopen((bNread)fread, urand);
  check(stream != NULL, "Failed to open /dev/urandom bStream");

  bstring key = bfromcstr("");

  // FNV1a histogram
  for (int i = 0; i < num_keys; i++) {
    int rc = bsread(key, stream, BUFFER_LEN);
    check(rc >= 0, "Failed to read from /dev/urandom");

    DArray_push(keys, bstrcpy(key));

    bsclose(stream);
    fclose(urand);
    return 0;
  }

error:
  return -1;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_fnv1a);
    mu_run_test(test_adler32);
    mu_run_test(test_djb);
    /* mu_run_test(test_distribution); */

    return NULL;
}

RUN_TESTS(all_tests);
