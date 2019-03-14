#include "map.h"

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

void map_add(map m, u32 key, u32 value) {
    if(!m->size) {
        tree t = tree_create(key, value);
        m->root = t;
        m->size++;
    } else {
        tree n = tree_find(m->root, key);
        if(tree_getkey(n) == key) 
            tree_setvalue(n, value);
        else {
            tree t = tree_create(key, value);
            tree_add(n, t);
            m->root = tree_balance(t);
            m->size++;
        }
    }
}

u32* map_find(map m, u32 key) {
    if(m->size == 0) return NULL;

    tree t = tree_find(m->root, key);

    if(tree_getkey(t) == key)
        return tree_getvalue(t);
    else
        return NULL;
}

void map_erase(map m, u32 key) {
    if(m->size == 0) return;

    tree t = tree_find(m->root, key);

    if(tree_getkey(t) == key)
        tree_erase(t);
}


  