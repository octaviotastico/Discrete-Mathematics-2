#include "tree.h"

struct Tree {
    u32 key;
    u32 value;
    u32 height;
    tree parent;
    tree right;
    tree left;
};

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

static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

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

static int tree_factor(tree t) {
	return tree_height(t->left) - tree_height(t->right);
}

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

void tree_add(tree p, tree n) {
    if(n->key > p->key)
        p->right = n;
    else
        p->left = n;
    n->parent = p;
	tree_balance(n);
}

void tree_erase(tree t) {

}


u32 tree_getkey(tree t) {
	return t->key;
}

u32* tree_getvalue(tree t) {
	return &t->value;
}

void tree_setvalue(tree t, u32 value) {
	t->value = value;
}