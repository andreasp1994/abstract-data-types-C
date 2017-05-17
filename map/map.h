typedef struct map Map;

Map *map_create(void);

int map_insert(Map *theMap, char *theKey, void *theItem);

void *map_lookup(Map *theMap, char *theKey);

int map_remove(Map *theMap, char *theKey, void **item);

void map_destroy(Map *theMap, void (*userFunction)(void *item));