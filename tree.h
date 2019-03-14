
#include "defs.h"

typedef struct Tree * tree;

tree tree_create(u32, u32);
void tree_add(tree, tree);
tree tree_find(tree, u32);
void tree_erase(tree);
tree tree_balance(tree);
u32 tree_getkey(tree);
u32* tree_getvalue(tree);
void tree_setvalue(tree, u32);