#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char* name;
  int age;
  int height;
  int weight;
};

struct Person* Person_create(char* name, int age, int height, int weight) {
  struct Person* p = malloc(sizeof(struct Person));
  assert(p != NULL);

  p->name = strdup(name);
  p->age  = age;
  p->height = height;
  p->weight = weight;

  return p;
}

void Person_destroy(struct Person* p) {
  assert(p != NULL);

  free(p->name);
  free(p);
}

void Person_print(struct Person* p) {
  printf("Name: %s\n", p->name);
  printf("\tAge: %d\n", p->age);
  printf("\tHeight: %d\n", p->height);
  printf("\tWeight: %d\n", p->weight);
}

int main(int argc, char* argv[]) {
  struct Person* joe = Person_create("Joe Alex", 32, 64, 140);
  struct Person* frank = Person_create("Frank Blank", 20, 72, 180);

  printf("Joe is at memory location %p\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p\n", frank);
  Person_print(frank);

  Person_destroy(joe);
  Person_destroy(frank);
}
