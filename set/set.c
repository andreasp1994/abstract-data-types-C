#include "set.h"
#include <stdlib.h>
#include <stdio.h>

struct set {
	struct set_item *first_item;
	struct set_item *last_item;
	isEqual eq_func;
	SetIterator *it;
};

struct set_item {
	Item item;
	struct set_item *next;
};

struct set_iterator {
	struct set_item *current;
};

SetIterator *set_iterCreate(Set *s){
	SetIterator *it = (SetIterator*)  malloc(sizeof(SetIterator));
	if (it != NULL){
		it->current = s->first_item;
		return it;
	}
	return NULL;
}

void set_iterDestroy(SetIterator *iter){
	free(iter);
}

Item set_iterNext(SetIterator *iter){
	Item result = iter->current;
	if(result != NULL) iter->current = iter->current->next;
	return result;
}

Set *set_create(isEqual f){
	Set *set = (Set*) malloc(sizeof(Set));
	if(set != NULL){
		set->eq_func = f;
		return set;
	}
	return NULL;
}

void set_destroy(Set *s){
	s->it = set_iterCreate(s);
	struct set_item* current = set_iterNext(s->it);
	while(current != NULL){
		struct set_item* temp = current;
		current = set_iterNext(s->it);
		free(temp);
	}
	set_iterDestroy(s->it);
	free(s);
} 

int set_isElement(Set *s, Item i){
	s->it = set_iterCreate(s);
	struct set_item *current = set_iterNext(s->it);
	while(current != NULL){
		if(s->eq_func(current->item, i) == 0) {
			set_iterDestroy(s->it);
			return 1;
		}
		current = set_iterNext(s->it);
	}
	set_iterDestroy(s->it);
	return 0;
}

int set_add(Set *s, Item i){
	int result = 0;
	struct set_item *s_item = (struct  set_item*) malloc(sizeof(struct set_item));
	if(s_item == NULL) return result;
	s_item->item = i;
	if(!set_isElement(s, i)){
		if(s->first_item == NULL){
			s->first_item = s_item;
		} else {
			s->last_item->next = s_item;
		}
		s->last_item = s_item;
		return 1;
	}
	free(s_item);
	return 0;
}

void set_remove(Set *s, Item i){
	struct set_item *current = s->first_item;
	if(current == NULL) {
		return ;
	}
	struct set_item *next = current->next;
	if ((s->eq_func(i, current->item))==0){
		if(next == NULL){
			s->first_item = NULL;
			s->last_item = NULL;
		} else{
			s->first_item = next;
		}
		free(current);
		return;
	}
	while(next != NULL) {
		if ((s->eq_func(i, next->item)) == 0){
			current->next=next->next;
			free(next);
			if((current->next) ==NULL) s->last_item=current;
			return;
		}
		current = current->next;
		next = current->next;
	}
	return;
}

void int_set_print(Set *s){
	s->it = set_iterCreate(s);
	struct set_item *current = set_iterNext(s->it);
	while(current != NULL){
		int a = *((int*) current->item);
		printf("%d, ", a);
		current = set_iterNext(s->it);
	}
	printf("\n");
	set_iterDestroy(s->it);
}

/* 
* isEqual function for integers
*/
int intEquality(Item i1, Item i2){
	int int1 = *((int *) i1);
	int int2 = *((int *) i2);
	return int1 - int2;
}

int main(){

	Set *myset = set_create(&intEquality);
	int a = 10;
	int b = 3;
	int c = 4;
	int d = 5;

	set_add(myset, &a);
	set_add(myset, &b);
	set_add(myset, &c);
	set_add(myset, &d);

	int_set_print(myset);

	// set_remove(myset, &d);
	// int_set_print(myset);

	// set_remove(myset, &b);
	int_set_print(myset);
}

