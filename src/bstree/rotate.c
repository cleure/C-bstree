#include <stdio.h>
#include <stdlib.h>

#define __BSTREE_EXTERN
#include "bstree.h"

#include "config.h"

#ifdef DEBUG
    #include "debug.h"
#endif

/**
* Perform left rotation, from *x
*
* @param    struct bstree *tree
* @param    struct bstree_node *x
* @return   0 on error, 1 on success
**/
int bstree_rotate_left(struct bstree *tree, struct bstree_node *x)
{
    struct bstree_node *y;
    
    if (!x || !tree || !tree->root || !x->right) {
        return 0;
    }
    
    /* y is x->right */
    y = x->right;
    
    /* Move y's left subtree to x's right subtree, to free it up */
    x->right = y->left;
    if (x->right) x->right->parent = x;
    
    /* Move x to y's left subtree */
    y->left = x;
    if (x == tree->root) {
        /* If x is the root node */
        y->parent = NULL;
        x->parent = y;
        tree->root = y;
    } else {
        if (x->parent->left == x) {
            /* x is the left subtree of it's parent */
            x->parent->left = y;
        } else {
            /* x is the right subtree of it's parent */
            x->parent->right = y;
        }
        
        /* Setup parent pointers */
        y->parent = x->parent;
        x->parent = y;
    }
    
    return 1;
}

/**
* Perform right rotation, from *x
*
* @param    struct bstree *tree
* @param    struct bstree_node *x
* @return   0 on error, 1 on success
**/
int bstree_rotate_right(struct bstree *tree, struct bstree_node *x)
{
    struct bstree_node *y;
    
    if (!x || !tree || !tree->root || !x->left) {
        return 0;
    }
    
    /* y is x->left */
    y = x->left;
    
    /* Move y's right subtree to x's left subtree, to free it up */
    x->left = y->right;
    if (x->left) x->left->parent = x;
    
    /* Move x to y's right subtree */
    y->right = x;
    if (x == tree->root) {
        /* If x is the root node */
        y->parent = NULL;
        x->parent = y;
        tree->root = y;
    } else {
        if (x->parent->left == x) {
            /* x is the left subtree of it's parent */
            x->parent->left = y;
        } else {
            /* x is the right subtree of it's parent */
            x->parent->right = y;
        }
        
        /* Setup parent pointers */
        y->parent = x->parent;
        x->parent = y;
    }
    
    return 1;
}
