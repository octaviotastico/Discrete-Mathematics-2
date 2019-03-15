
#include "tree.h"

// Struct of the tree. Used by map to keep track of all
// nodes position in the graph with the key and value.
struct Tree {
    u32 key;
    u32 value;
    u32 height;
    tree parent;
    tree right;
    tree left;
};

// Auxiliar max value function.
static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

// Creates an empty tree.
tree tree_create(u32 key, u32 value) {
    tree t = (tree)malloc(sizeof(struct Tree));
    t->key = key;
    t->value = value;
    t->height = 0;
    t->parent = NULL;
    t->right = NULL;
    t->left = NULL;
    return t;
}

// Returns height of a node.
static u32 tree_height(tree t) {
	if(!t || (!t->left && !t->right))
		return 0;
    if(t->left && t->right)
        return max(t->left->height, t->right->height) + 1;
    else if(t->right)
        return t->right->height + 1;
    else if(t->left) 
        return t->left->height + 1;
}

// Returns the difference between the height of the left and right subtrees
static int tree_factor(tree t) {
	return tree_height(t->left) - tree_height(t->right);
}

// Rotates a node to the right (see tree.h commentarys)
static void tree_rotateR(tree Q) { 
    tree P = Q->left;

    Q->left = P->right;
    if(Q->left) Q->left->parent = Q;

    P->right = Q;

    if(Q->parent && Q->parent->left == Q) Q->parent->left = P;
    if(Q->parent && Q->parent->right == Q) Q->parent->right = P;

    P->parent = Q->parent;

    Q->parent = P;

    Q->height = tree_height(Q);
    P->height = tree_height(P);
}

// Rotates a node to the left (see tree.h commentarys)
static void tree_rotateL(tree P) { 
    tree Q = P->right;

    P->right = Q->left;
    if(P->right) P->right->parent = P;

    Q->left = P;

    if(P->parent && P->parent->right == P) P->parent->right = Q;
    if(P->parent && P->parent->left == P) P->parent->left = Q;


    Q->parent = P->parent;

    P->parent = Q;

    P->height = tree_height(P);
    Q->height = tree_height(Q);
}

// Rotates the tree to keep it an AVL Tree.
tree tree_balance(tree t) {
    u32 key = t->key;
    tree root = NULL;
    while(t) {
        t->height = tree_height(t);
        int balance = tree_factor(t);

        assert(abs(balance) <= 2);

        // Left Left Case 
        if (balance > 1 && key < t->left->key) {
            tree_rotateR(t); 
            t = t->parent;
        }
    
        // Right Right Case 
        if (balance < -1 && key > t->right->key) {
            tree_rotateL(t);
            t = t->parent;
        }
    
        // Left Right Case 
        if (balance > 1 && key > t->left->key) { 
            tree_rotateL(t->left);
            tree_rotateR(t);
            t = t->parent;
        } 
    
        // Right Left Case 
        if (balance < -1 && key < t->right->key) { 
            tree_rotateR(t->right);
            tree_rotateL(t);
            t = t->parent;
        }
        root = t;
        t = t->parent;
    }
    return root;
}

// Search an element on the tree (O(log(n)))
tree tree_find(tree t, u32 key) {
    while(1) {
        if(key > t->key)
            if(t->right) t = t->right;
            else return t;
        if(key < t->key)
            if(t->left) t = t->left;
            else return t;
        if(key == t->key)
            return t;
    }
}

// Adds an element to the tree, then balances it.
void tree_add(tree p, tree n) {
    if(n->key > p->key)
        p->right = n;
    else
        p->left = n;
    n->parent = p;
	tree_balance(n);
}

// Returns key of a node.
u32 tree_getKey(tree t) {
	return t->key;
}

// Returns pointer to a node's value.
u32* tree_getValue(tree t) {
	return &t->value;
}

// Sets a given node with the given value.
void tree_setValue(tree t, u32 value) {
	t->value = value;
}

// Deletes the entire tree and frees the memory.
void tree_delete(tree t) {
    if(t->left)
        tree_delete(t->left);
    if(t->right)
        tree_delete(t->right);
    free(t); t = NULL;
}