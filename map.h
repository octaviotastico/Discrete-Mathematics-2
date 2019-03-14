/*

AVL Map implementation for map

https://upload.wikimedia.org/wikipedia/commons/f/fd/AVL_Tree_Example.gif


*/

#include "tree.h"

typedef struct Map * map;

map map_create();
void map_add(map, u32, u32);
u32* map_find(map, u32);
void map_delete(map, u32);