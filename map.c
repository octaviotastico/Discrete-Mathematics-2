
#include "map.h"

// Map structure used to keep track
// of the nodes in the graph.
struct Map {
    tree root;
    size_t size;
};

// Creates an empty map.
map map_create() {
    map m = (map)malloc(sizeof(struct Map));
    m->root = NULL;
    m->size = 0;
    return m;
}

// Adds an element to the map with it's key and value.
void map_add(map m, u32 key, u32 value) {
    if(!m->size) {
        tree t = tree_create(key, value);
        m->root = t;
        m->size++;
    } else {
        tree n = tree_find(m->root, key);
        if(tree_getKey(n) == key) 
            tree_setValue(n, value);
        else {
            tree t = tree_create(key, value);
            tree_add(n, t);
            m->root = tree_balance(t);
            m->size++;
        }
    }
}

// Finds an element in the map given it's key.
u32* map_find(map m, u32 key) {
    if(m->size == 0) return NULL;

    tree t = tree_find(m->root, key);

    if(tree_getKey(t) == key)
        return tree_getValue(t);
    else
        return NULL;
}

// Deletes the entire map.
void map_delete(map m, u32 key) {
    if(m->size == 0) return;

    tree t = tree_find(m->root, key);

    if(tree_getKey(t) == key)
        tree_erase(t);
}