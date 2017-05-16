#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef void *Data;
typedef struct iterator *Iterator;

Iterator it_create(long size, Data *elements);
void it_destroy(Iterator it);

int it_hasNext(Iterator it);

int it_next(Iterator it, Data *element);

#endif