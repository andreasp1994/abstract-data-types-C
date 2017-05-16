// NOTE: This file uses features of the C99 standard; compile with -std=c99

#include "stack.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 50L
#define MAX_INIT_CAPACITY 1000L

struct stack {
	unsigned long capacity;
	unsigned long delta;
	unsigned long next;
	Data *theArray;
};

Stack stack_create(long capacity){
	Stack st = malloc(sizeof(struct stack));
	if( st == NULL) return NULL;

	long cap = (capacity <= 0) ? DEFAULT_CAPACITY : capacity;
	cap = (cap > MAX_INIT_CAPACITY) ? MAX_INIT_CAPACITY : cap;

	st->capacity = cap;
	st->delta = cap;
	st->next = 0;
	if((st->theArray = malloc(cap * sizeof(Data))) == NULL){
		free(st);
		return NULL;
	}
	return st;
}

static void purge(Stack st, void (*freeF)(Data element)){
	if(freeF == NULL) return;
	for(unsigned long i = 0; i < st->next; i++){
		(*freeF)(st->theArray[i]);
	}
}

void stack_destroy(Stack st, void (*freeF)(Data element)){
	purge(st, freeF);
	free(st->theArray);
	free(st);
}

void stack_purge(Stack st, void (*freeF)(Data element)){
	purge(st, freeF);
	st->next = 0;
}

int stack_push(Stack st, Data element){
	if(st->capacity <= st->next) {
		size_t bytes = (st->capacity +st->delta) * sizeof(Data);
		Data *tmp = realloc(st->theArray, bytes);
		if (tmp != NULL) return 0;
		st->theArray = tmp;
		st->capacity += st->delta;
	}
	st->theArray[st->next++] = element;
	return 1;
}

int stack_pop(Stack st, Data *element){
	if(st->next > 0){
		*element = st->theArray[--st->next];
		return 1;
	}
	return 0;
}

int stack_peek(Stack st, Data *element){
	if(st->next > 0){
		*element = st->theArray[st->next - 1];
		return 1;
	}
	return 0;
}

int stack_isEmpty(Stack st){
	return (st->next == 0);
}

long stack_size(Stack st){
	return st->next;
}

int main(){

}