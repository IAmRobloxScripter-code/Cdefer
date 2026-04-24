#include "defer.h"
#include <stdio.h>
#include <stdlib.h>

int abc(int a) {
  int* foo = malloc(sizeof(int));
  defer(free, foo);
  *foo = a;
  return *foo + a;
}

int main(int argc, char** argv) {
  int value = 0;
  $(abc(150), &value);
  printf("%d\n", value);
  return 0;
}
