#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function)(int data_len, const char* data);

int main(int argc, char* argv[]) {
  int rc = 0;
  check(argc == 5, "USAGE: ex29 libex29.so function data_len data");

  char* lib_file    = argv[1];
  char* func_to_run = argv[2];
  int data_len      = strtol(argv[3], (char **)NULL, 10);
  char* data        = argv[4];

  void* lib = dlopen(lib_file, RTLD_NOW);
  check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

  lib_function func = dlsym(lib, func_to_run);
  check(func != NULL, "Did not find %s function in the library %s: %s",
        func_to_run, lib_file, dlerror());

  rc = func(data_len, data);
  check(rc == 0, "Function %s returned %d for data_len %d, data: %s",
        func_to_run, rc, data_len, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_file);

  return 0;

error:
  return -1;
}
