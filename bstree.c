#include "bstree.h"

tree tree_create(u32 name, u32 position){
    tree t = (tree)malloc(sizeof(struct Tree));
    node n = node_create(name, position);
    n->height = 1;
    n->parent = n;
    t->first = n;
    return t;
}

/*

T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side) 

     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3

names in both of the above trees follow the 
following order 
names(T1) < name(x) < names(T2) < name(y) < names(T3)
So BST property is not violated anywhere.

*/

// An utility function to right rotate subtree rooted with y
void tree_rRotate(node y){ 
    node x = y->left; 
    node T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(y->left->height, y->right->height) + 1; 
    x->height = max(x->left->height, x->right->height) + 1; 
  
    // Return new root 
    return x; 
}

// An utility function to left rotate subtree rooted with x
void tree_lRotate(node x){ 
    node y = x->right; 
    node T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(x->left->height, x->right->height) + 1; 
    y->height = max(y->left->height, y->right->height) + 1; 
  
    // Return new root 
    return y; 
}

// Get balance factor of node N 
u32 tree_balanced(node n){ 
    if (n == NULL) 
        return 0; 
    return abs(n->left->height - n->right->height); 
}

// Recursive function to insert a node in the tree.
void tree_add(node n, u32 name, u32 position){
    /* 1.  Perform the normal BST insertion */
    if(n == NULL) {
        node n = node_create(name, position);
    } else if(name > n->name){
        tree_add(n->right, name, position);
    } else if(name < n->name){
        tree_add(n->left, name, position);
    }
  
    /* 2. Update height of this ancestor node */
    n->height = max(n->left->height, n->right->height) + 1;
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    u32 balance = tree_balanced(n); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && name < n->left->name) 
        tree_rRotate(n); 
  
    // Right Right Case 
    if (balance < -1 && name > n->right->name) 
        tree_lRotate(n); 
  
    // Left Right Case 
    if (balance > 1 && name > n->left->name){ 
        tree_lRotate(n->left); 
        tree_rRotate(n); 
    } 
  
    // Right Left Case 
    if (balance < -1 && name < n->right->name){ 
        tree_rRotate(n->right); 
        tree_lRotate(n); 
    }
}

// Recursive function to delete a node with given name 
// from subtree with given root. It returns root of 
// the modified subtree. 
void tree_delete(node root, u32 name) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE 

    if (name < root->name) 
        tree_delete(root->left, name); 
    else if(name > root->name) 
        tree_delete(root->right, name); 
  
    // if name is same as root's name, then This is 
    // the node to be deleted 
    else { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ){ 
            node temp = root->left ? root->left : root->right; 
  
            // No child case 
            if (temp == NULL){ 
                temp = root; 
                root = NULL; 
            } else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } else { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            node temp = tree_min(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->name = temp->name; 
  
            // Delete the inorder successor 
            tree_delete(root->right, temp->name); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(root->left->height, root->right->height); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    u32 balance = tree_balanced(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && tree_balanced(root->left) >= 0) 
        tree_rRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && tree_balanced(root->left) < 0) 
    { 
        tree_lRotate(root->left); 
        tree_rRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && tree_balanced(root->right) <= 0) 
        tree_lRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && tree_balanced(root->right) > 0) 
    { 
        tree_rRotate(root->right); 
        tree_lRotate(root); 
    }
}

// Given a non-empty binary search tree, return the 
// node with minimum name value found in that tree.
node tree_min(node n){
    node m = n;
    while (m->left != NULL) 
        m = m->left; 
    return m; 
}

node node_create(u32 name, u32 position){
    node n = (node)malloc(sizeof(struct Node));
    n->name = name;
    n->position = position;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

