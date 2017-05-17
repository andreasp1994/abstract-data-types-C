#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 10

struct arraylist {
	void **items;
	long capacity;
	long size;
};

ArrayList *al_create(long capacity){
	if(capacity <= 0) capacity = DEFAULT_CAPACITY;
	void **items = (void**) malloc(sizeof(void*)*capacity);
	if(items != NULL){
		ArrayList *al = (ArrayList*) malloc(sizeof(ArrayList));
		if(al != NULL){
			al->size = 0;
			al->items = items;
			al->capacity = capacity;
			return al;
		}
	}
	return NULL;
}

void al_destroy(ArrayList *al, void (*userFunction)(void *element)){
	int i;
	for(i = 0; i < al->size && (userFunction != NULL); i++){
		void *item = al->items[i];
		userFunction(item);
	}
	free(al->items);
	free(al);
}

long al_size(ArrayList *al){
	return al->size;
}

int al_add(ArrayList *al, void *element){
	int result = 1;
	if(al->size==al->capacity){
		long new_capacity =  (al->capacity)*2;
		al->items = (void**) realloc(al->items, new_capacity * sizeof(void*));
		if (al->items == NULL) {
			result = 0;
		}  else {
			al->capacity = new_capacity;
			al_add(al, element);
		}
	} else {
		al->items[al->size] = element;
		(al->size)++;
	}
	return result;
}

int al_get(ArrayList *al_long, long i, void **element){
	void* item = al_long->items[i];
	if(item != NULL){
		*element = item;
		return 1;
	} 
	return 0;
}

/*
* only works if elements are ints
*/
void al_int_print(ArrayList *al){
	long i;
	for(i = 0; i < al->capacity;i++){
		if(i < al->size){
			void *m = al->items[i];
			int n = *((int*) m);
			printf("%d ", n);
		} else {
			printf("%s ", "_");
		}
		
	}
	printf("\n");
}

int al_insert(ArrayList *al, long i, void *element){
	if( i > al->size) return 0;
	else if( i == al->size) {
		al_add(al, element);
	} else if (i < al->size){ // have to shift here
		void **old_item_structure = al->items;
		void **new_item_structure = (void**) malloc(sizeof(void *)*al->capacity);
		if(new_item_structure == NULL) return 0;
		int old_size = al->size;
		al->size = 0;
		al->items = new_item_structure;
		int n;
		for(n = 0;n <= old_size;n++){
			if(n==i){
				al_add(al, element);
			} else if (n < i){
				al_add(al, old_item_structure[n]);
			} else if (n > i){
				al_add(al, old_item_structure[n-1]);
			}
		}

		free(old_item_structure);
	}
	return 1;
}

// int al_remove(ArrayList *al, long i, void **elements){
// 	int result = 0;
// 	if(al->items[i] == NULL) return result;
// 	else {
// 		ArrayList 
// 	}
// }

int main(){
	ArrayList *al = al_create(2);

	// int a = 1;
	// int b = 2;
	// int c = 3;
	// int d = 4;
	char *s1 = "barack";
	char *s2 = "obama";

	al_add(al, s1);
	al_add(al, s2);
	// al_add(al, &c);
	// al_add(al, &d);

	// al_int_print(al);

	// void *item;
	// int found = al_get(al, 3, &item);
	// int i = *((int*) item);
	// printf("f:%d i:%d\n",found, i );

	// al_insert(al, 3, &d);
	// al_int_print(al);

	// al_insert(al, 2, &d);
	// al_int_print(al);

	al_destroy(al, NULL);
}