/*

AVL Map implementation for map

https://upload.wikimedia.org/wikipedia/commons/f/fd/AVL_Tree_Example.gif


*/

#include <stdlib.h>
#include "assert.h"
typedef unsigned int u32;

typedef struct Tree * tree;
typedef struct Map * map;

struct Tree {
    u32 key;
    u32 value;
    u32 height;
    tree parent;
    tree right;
    tree left;
};

struct Map {
    tree root;
    size_t size;
};

map map_create();
void map_add(map, u32, u32);