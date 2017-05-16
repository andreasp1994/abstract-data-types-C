typedef struct arraylist ArrayList;

ArrayList *al_create(long capacity);

void al_destroy(ArrayList *al, void (*userFunction)(void *element));

long al_size(ArrayList *al);

int al_add(ArrayList *al, void *element);

int al_get(ArrayList *al_long, long i, void **element);

int al_insert(ArrayList *al, long i, void *element);

int al_remove(ArrayList *al, long i, void **elements);

int al_set(ArrayList *al, void *element, long i, void **previous);

