#include "iterator.h"
#include <stdlib.h>

struct iterator {
	unsigned long next;
	unsigned long size;
	Data *elements;
};

Iterator it_create(long size, Data *elements){
	Iterator it = malloc(sizeof(struct iterator));
	if(it == NULL) return NULL;
	it->next = 0;
	it->size = size;
	it->elements = elements;
	return it;
}

void it_destroy(Iterator it){
	free(it->elements);
	free(it);
}

int it_hasNext(Iterator it){
	return (it->next < it->size);
}

int it_next(Iterator it, Data *element){
	if (it->next < it->size) {
		*element = it->elements[it->next++];
		return 1;
	}
	return 0;
}

