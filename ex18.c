#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char* message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// fake function pointer "type"
typedef int (*fn)(int a, int b);

// A classic bubble sort function that uses `cmp` (a fn pointer) to do the
// sorting
int* bubble_sort(int* numbers, int count, fn cmp) {
  int* target = malloc(count * sizeof(int));
  if (!target) { die("Memory error."); }
  memcpy(target, numbers, count * sizeof(int));

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count - 1; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        int temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }

  return target;
}

int sorted_order(int a, int b) {
  return a - b;
}

int reverse_order(int a, int b) {
  return b - a;
}

int strange_order(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

void test_sorting(int* numbers, int count, fn cmp) {
  int* sorted = bubble_sort(numbers, count, cmp);
  if (!sorted) { die("Failed to sort."); }

  for (int i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  putchar('\n');

  free(sorted);
}

int main(int argc, char* argv[]) {
  if (argc < 2) { die("USAGE: ex18 4 3 1 5 6"); }

  int count = argc - 1;
  char** inputs = argv + 1;

  int* numbers = malloc(count * sizeof(int));
  if (!numbers) { die("Memory error."); }

  for (int i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strange_order);

  free(numbers);

  return 0;
}
