#ifndef TREE
#define TREE

#include "Rii.h"

typedef struct Tree * tree;

// Creates a node
tree tree_create(u32, u32);

// Add an element to another tree.
void tree_add(tree, tree);

// Search an element on the tree (O(log(n)))
tree tree_find(tree, u32);

// Balances the tree
tree tree_balance(tree);

// Returns key of a node.
u32 tree_getKey(tree);

// Returns pointer to a node's value.
u32* tree_getValue(tree);

// Sets a given node with the given value.
void tree_setValue(tree, u32);

// Sort the tree
u32 tree_inorder_sort(tree, u32);

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