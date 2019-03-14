/*

AVL Tree implementation for map

https://upload.wikimedia.org/wikipedia/commons/f/fd/AVL_Tree_Example.gif


*/

#include <stdlib.h>
typedef unsigned int u32;

typedef struct Node * node;
typedef struct Tree * tree;

struct Node {
    u32 name;
    u32 position;
    u32 height;
    node left;
    node right;
    node parent;
};

struct Tree {
    node first;
};

tree tree_create(u32 name, u32 position);
void tree_add(node n, u32 name, u32 position);
void tree_destroy(tree t);
void tree_rRotate(node y);
void tree_lRotate(node x);
u32 tree_balanced(node n);
node node_create(u32 name, u32 position);
