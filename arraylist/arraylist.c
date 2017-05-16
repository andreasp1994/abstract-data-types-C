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
	for(i = 0; i < al->capacity; i++){
		void *item = al->items[i];
		if(item != NULL) {
			if (userFunction != NULL) userFunction(item);
			// free(item); //Not sure if needed
		}
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
		ArrayList *new_al = al_create((al->capacity)*2);
		long i;
		for(i = 0 ;i < al->size; i++){
			al_add(new_al, al->items[i]);
		}
		al_add(new_al, element);
		ArrayList temp;
		temp = *al;
		*al = *new_al;
		//TODO:Fix memory leak here
		free(temp.items);
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
	int result = 0;
	if( i > al->size) return result;
	else if( i == al->size) {
		al_add(al, element);
		result = 1;
	} else if (i < al->size){
		ArrayList *new_al = al_create(al->capacity);
		int n;
		for(n = 0;n <= al->size;n++){
			if(n==i){
				al_add(new_al, element);
			} else if (n < i){
				al_add(new_al, al->items[n]);
			} else if (n > i){
				al_add(new_al, al->items[n-1]);
			}
		}
		//TODO:Fix memory leak here.(old list is leaked)
		*al = *new_al;
		result = 1;
	}
	return result;
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

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	al_add(al, &a);
	al_add(al, &b);
	al_add(al, &c);
	// al_add(al, &d);

	al_int_print(al);

	void *item;
	int found = al_get(al, 3, &item);
	int i = *((int*) item);
	printf("f:%d i:%d\n",found, i );

	al_insert(al, 3, &d);
	al_int_print(al);

	al_insert(al, 2, &d);
	al_int_print(al);

	al_destroy(al, NULL);
}