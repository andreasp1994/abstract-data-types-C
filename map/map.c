#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct linked_kv_pair {
	char *key;
	void *value;
	struct linked_kv_pair *next;
};

struct map {
	struct linked_kv_pair *head;
};

Map *map_create(){
	Map *m = (Map*) malloc(sizeof(Map));
	if(m != NULL){
		m->head = NULL;
		return m;
	}
	return NULL;
}

void *map_lookup(Map *theMap, char *theKey){
	struct linked_kv_pair *entry = theMap->head;
	while(entry != NULL){
		if((strcmp(entry->key, theKey)) == 0) return entry->value;
		entry = entry->next;
	}
	return NULL;
}

void map_destroy(Map *theMap, void (*userFunction)(void *item)){
	struct linked_kv_pair *current = theMap->head;
	struct linked_kv_pair *to_be_freed;
	while(current != NULL){
		if(userFunction != NULL) userFunction(current->value);
		to_be_freed = current;
		current = current->next;
		free(to_be_freed);
	}
	free(theMap);
}

int map_insert(Map *theMap, char *theKey, void *theItem){
	struct linked_kv_pair *entry = (struct linked_kv_pair*) malloc(sizeof(struct linked_kv_pair));
	if(entry != NULL){
		entry->key = theKey;
		entry->value = theItem;
		entry->next = NULL;
		if(theMap->head != NULL){
			entry->next = theMap->head;
		}
		theMap->head = entry;
	}
	return 0;
}

void str_map_print(Map *theMap){
	struct linked_kv_pair *current = theMap->head;
	while(current != NULL){
		printf("%s -> %s\n", current->key, (char *) current->value);
		current = current->next;
	}
	return;
}
	
int main(){
	Map *map = map_create();

	char *key = "barack";
	char *value = "obama";

	map_insert(map, key, value);

	str_map_print(map);

	map_destroy(map, NULL);
}

