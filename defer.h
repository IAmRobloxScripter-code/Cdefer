#pragma once

typedef struct fn_type {
  void (*fn)(void*);
  void* ptr;
} fn_type;

typedef struct stack_frame {
  fn_type defers[100];
  unsigned int size;
} stack_frame;

extern stack_frame call_stack[100];
extern unsigned int call_stack_pointer;

#define defer(fn_value, ptr_value) \
  call_stack[call_stack_pointer].defers[call_stack[call_stack_pointer].size++] = (fn_type){.fn = fn_value, .ptr = ptr_value}

#define init_stack \
  call_stack[call_stack_pointer++] = (stack_frame){.defers = {}, .size = 0};

#define call_with_dest(fn_value, dest) \
  init_stack \
  *dest = fn_value; \
  for (int index = 0; index < call_stack[call_stack_pointer].size; ++index) { \
      call_stack[call_stack_pointer].defers[index].fn(call_stack[call_stack_pointer].defers[index].ptr);     \
  } \
  call_stack_pointer--;

#define call_without_dest(fn_value) \
  init_stack \
  fn_value; \
  for (int index = 0; index < call_stack[call_stack_pointer].size; ++index) { \
      call_stack[call_stack_pointer].defers[index].fn(call_stack[call_stack_pointer].defers[index].ptr);     \
  } \
  call_stack_pointer--;

#define call1(fn, dest) call_with_dest(fn, dest)
#define call2(fn) call_without_dest(fn)

#define call_select(_1, _2, NAME, ...) NAME
#define $(...) call_select(__VA_ARGS__, call1, call2)(__VA_ARGS__)
int __main__(int argc, char** argv);

#define main(...) \
  main(int argc, char** argv) { \
    int return_value = 0;  \
    $(__main__(argc, argv), &return_value);\
    return return_value; \
  } \
  int __main__(__VA_ARGS__)
