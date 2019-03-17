#ifndef MAP
#define MAP

#include "Rii.h"

typedef struct Map * map;

// Creates an empty map.
map map_create();

// Adds an element to the map with it's key and value.
int map_add(map, u32, u32);

// Finds an element in the map given it's key.
u32* map_find(map, u32);

// Size of map
size_t map_size(map);

// Sort the map (change of values)
void map_sort(map);

// Clear the map but doesn't destroy it.
void map_clear(map);

// Deletes the entire map.
void map_destroy(map);

#endif