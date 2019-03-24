
#include "map.h"

// Map structure used to keep track
// of the nodes in the graph.
struct Map {
    tree root;
    size_t size;
};

map map_create() {
    map m = (map)malloc(sizeof(struct Map));
    m->root = NULL;
    m->size = 0;
    return m;
}

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

void map_sort(map m) {
    tree_inorder_sort(m->root, 0);
}

void map_clear(map m) {
    tree_destroy(m->root);
    m->root = NULL;
    m->size = 0;
}

void map_destroy(map m) {
    map_clear(m);
    free(m);
}
