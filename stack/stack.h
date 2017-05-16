#ifndef _STACK_H_
#define _STACK_H_
#include "iterator.h"

typedef void *Data;
typedef struct stack *Stack;

Stack stack_create(long capacity);
void stack_destroy(Stack st, void (*freeF)(Data element));
void stack_purge(Stack st, void (*freeF)(Data element));

int stack_push(Stack st, Data element);
int stack_pop(Stack st, Data *element);

int stack_peek(Stack st, Data *element);
int stack_isEmpty(Stack st);
long stack_size(Stack st);

Data *stack_toArray(Stack st, long *len);
Iterator stack_it_create(Stack st);

#endif