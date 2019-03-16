#ifndef MAP
#define MAP

#include "tree.h"
#include "vector.h"

// Node to struct Map in map.c.
typedef struct Map * map;

// Creates an empty map.
map map_create();
// Adds an element to the map with it's key and value.
int map_add(map, u32, u32);
// Finds an element in the map given it's key.
u32* map_find(map, u32);
// Size of map
size_t map_size(map);
// Restructre the map (change of values)
void map_restructure(map);
// Deletes the entire map.
void map_destroy(map);

#endif