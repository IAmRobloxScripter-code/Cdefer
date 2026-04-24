# Cdefer
This library adds defer to C. Well a subset of it, it cannot run functions that take more than 1 argument or functions that dont take a pointer.

# How to use
```c
#include "defer.h"
#include <stdio.h>
#include <stdlib.h>

// main must have int argc and char** argv
int main(int argc, char** argv) {
  int* ptr = malloc(sizeof(int));
  defer(free, ptr);
  *ptr = 100;
  printf("%d\n", *ptr); // will print 100
  return 0;
}
```

# Compile
`gcc -o main main.c defer.c`
`clang -o main main.c defer.c`
