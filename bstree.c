#include "bstree.h"
#include "stdio.h"

map map_create() {
    map m = (map)malloc(sizeof(struct Map));
    m->root = NULL;
    m->size = 0;
    return m;
}

tree tree_create(u32 key, u32 value) {
    tree t = (tree)malloc(sizeof(struct Tree));
    t->key = key;
    t->value = value;
    t->height = 1;
    t->parent = NULL;
    t->right = NULL;
    t->left = NULL;
    return t;
}

static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

static void tree_height(tree t) {
    if(t->left && t->right)
        t->height = max(t->left->height, t->right->height) + 1;
    else if(t->right)
        t->height = t->right->height + 1;
    else if(t->left) 
        t->height = t->left->height + 1;
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

    tree_height(Q);
    tree_height(P);
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

    tree_height(P);
    tree_height(Q);
}


static tree tree_find(tree t, u32 key) {
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

static void tree_add(tree p, tree n) {
    if(n->key > p->key)
        p->right = n;
    else
        p->left = n;
    n->parent = p;
}

static int tree_factor(tree t) {
    if(t->left && t->right)
        return t->left->height - t->right->height;
    else if(t->right)
        return -t->right->height;
    else if(t->left)
        return t->left->height;
    else
        return 0;
}

static tree tree_balance(tree t) {
    u32 key = t->key;
    tree root;
    while(t) {
        tree_height(t);
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

// Function to print binary tree in 2D  
// It does reverse inorder traversal  
void print2DUtil(tree root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += 10;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current tree fter space  
    // 10  
    printf("\n");
    for (int i = 10; i < space; i++)  
        printf(" ");
        printf("%u\n", root->key);
  
    // Process left child  
    print2DUtil(root->left, space);  
}  
  
// Wrapper over print2DUtil()  
void print2D(tree root)  
{  
    // Pass initial space 10 as 0  
    print2DUtil(root, 0);  
}  

void map_add(map m, u32 key, u32 value) {
    if(!m->size) {
        tree t = tree_create(key, value);
        m->root = t;
        m->size++;
    } else {
        tree n = tree_find(m->root, key);
        if(n->key == key) 
            n->value = value;
        else {
            tree t = tree_create(key, value);
            tree_add(n, t);
            m->root = tree_balance(t);

            m->size++;
        }
    }
}


  