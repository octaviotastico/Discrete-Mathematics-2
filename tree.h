#ifndef TREE
#define TREE

#include "defs.h"
#include "vector.h"

// Node to struct Tree in tree.c.
typedef struct Tree * tree;

// Creates an AVL Tree.
tree tree_create(u32, u32);
// Adds an element to the tree.
void tree_add(tree, tree);
// Search an element on the tree (O(log(n)))
tree tree_find(tree, u32);
// Balances the tree to keep it an AVL Tree.
tree tree_balance(tree);
// Returns key of a node.
u32 tree_getKey(tree);
// Returns pointer to a node's value.
u32* tree_getValue(tree);
// Sets a given node with the given value.
void tree_setValue(tree, u32);
// Restructure the tree by in-order traversal
int tree_inorder_restructure(tree, int);
// Deletes a the tree.
void tree_destroy(tree);

/* Commentary to understand tree_rotateR, and tree_rotateL

T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side)           
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3

 */

#endif