# Cdefer
This library adds defer to C. Well a subset of it, it cannot run functions that take more than 1 argument or functions that dont take a pointer.

# How to use
**defer in main**
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
**defer in other functions**
```c
#include "defer.h"
#include <stdio.h>
#include <stdlib.h>

int foo(int a) {
  int* b = malloc(sizeof(int));
  defer(free, b);
  *b = a;
  return *b + 100;
}

int main(int argc, char** argv) {
  int return_value = 0;
  $(foo(100), &return_value);
  printf("%d\n", return_value); // will print 200
  return 0;
}
```
# Compile
**gcc:** `gcc -o main main.c defer.c`
<br>
**clang:** `clang -o main main.c defer.c`
<br>
Or just run `make` in the project directory.
