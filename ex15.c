#include <stdio.h>

void separator() {
  printf("---\n");
}

void print_via_indexing(int count, char** names, int* ages) {
  for (int i = 0; i < count; i++) {
    printf("%s is %d.\n", names[i], ages[i]);
  }
}

void print_via_pointers(int count, char** names, int* ages) {
  for (int i = 0; i < count; i++) {
    printf("%s is %d.\n", *(names + i), *(ages + i));
  }
}

void print_addresses(int count, char** names, int* ages) {
  for (int i = 0; i < count; i++) {
    printf("name %p, age %p\n", &(names[i]), &(ages[i]));
  }
}

int main(int argc, char* argv[]) {
  // arrays
  char* names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};
  int ages[] = {23, 43, 12, 89, 2};

  // pointers
  int count = sizeof(ages) / sizeof(int);
  char** cur_name = names;
  int* cur_age = ages;

  print_via_indexing(count, cur_name, cur_age);
  separator();

  print_via_pointers(count, cur_name, cur_age);
  separator();

  print_addresses(count, cur_name, cur_age);

  return 0;
}
