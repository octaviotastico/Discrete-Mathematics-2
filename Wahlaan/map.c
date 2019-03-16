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
int map_add(map m, u32 key, u32 value) {
    if(!m->size) {
        tree t = tree_create(key, value);
        if(!t) return 1;
        m->root = t;
        m->size++;
    } else {
        tree n = tree_find(m->root, key);
        if(tree_getKey(n) == key) 
            tree_setValue(n, value);
        else {
            tree t = tree_create(key, value);
            if(!t) return 1;
            tree_add(n, t);
            m->root = tree_balance(t);
            m->size++;
        }
    }
    return 0;
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

size_t map_size(map m) {
    return m->size;
}

void map_restructure(map m) {
    tree_inorder_restructure(m->root, 0);
}

// Deletes the entire map.
void map_destroy(map m) {
    tree_destroy(m->root);
    free(m);
}

// Clear the entire map, but doesn't destroy it.
void map_clear(map m) {
    tree_destroy(m->root);
}
