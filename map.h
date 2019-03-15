/*

AVL Map implementation for map

https://upload.wikimedia.org/wikipedia/commons/f/fd/AVL_Tree_Example.gif


*/

#include "tree.h"

// Node to struct Map in map.c.
typedef struct Map * map;

// Creates an empty map.
map map_create();
// Adds an element to the map with it's key and value.
void map_add(map, u32, u32);
// Finds an element in the map given it's key.
u32* map_find(map, u32);
// Size of map
size_t map_size(map);
// Deletes the entire map.
void map_destroy(map);