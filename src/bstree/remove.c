#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

extern void rbtree_remove_cleanup(struct bstree *tree, struct bstree_node **cur);

/* Case 1: No Children */
static void remove_case1(struct bstree *tree, struct bstree_node **node)
{
    if (tree->freefn) {
        tree->freefn((*node)->key, (*node)->data);
    }
    
    free(*node);
    *node = NULL;
}

/* Case 2: One Child */
static void remove_case2(struct bstree *tree, struct bstree_node **node)
{
    struct bstree_node *left, *right, *parent;
    
    left = (*node)->left;
    right = (*node)->right;
    parent = (*node)->parent;
    
    if (tree->freefn) {
        tree->freefn((*node)->key, (*node)->data);
    }
    
    free(*node);
    if (left) {
        *node = left;
    } else {
        *node = right;
    }
    
    (*node)->parent = parent;
}

/* Case 3: Two Children */
static void remove_case3(struct bstree *tree, struct bstree_node **node)
{
    struct bstree_node *cur;
    
    if (tree->freefn) {
        tree->freefn((*node)->key, (*node)->data);
    }
    
    /* Go right one */
    cur = (*node)->right;
    
    /* Find left most in sub-tree */
    while (cur->left) {
        cur = cur->left;
    }
    
    (*node)->key = cur->key;
    (*node)->data = cur->data;
    if ((*node)->right == cur) {
        (*node)->right = NULL;
    } else {
        if (cur->right) {
            cur->right->parent = cur->parent;
            cur->parent->left = cur->right;
        } else {
            cur->parent->left = NULL;
        }
    }
    
    free(cur);
}

/**
* Remove item from bstree.
*
* @param    struct bstree *tree
* @param    void *key
* @return   0 on error, 1 on success
**/
int bstree_remove(struct bstree *tree, void *key)
{
    int     cmp = 0,
            whichcase = 1;
    
    struct bstree_node *cur, **node;
    
    cur = tree->root;
    node = &tree->root;
    
    while (cur) {
        cmp = tree->cmpfn(key, cur->key);
        if (cmp == bstree_gt) {
            node = &cur->right;
            cur = cur->right;
        } else if (cmp == bstree_lt) {
            node = &cur->left;
            cur = cur->left;
        } else {
            if (cur->left) whichcase <<= 1;
            if (cur->right) whichcase <<= 1;
    
            if (whichcase == 1) {
                remove_case1(tree, node);
            } else if (whichcase == 2) {
                remove_case2(tree, node);
            } else {
                remove_case3(tree, node);
            }
            
            if (tree->is_redblack) {
                rbtree_remove_cleanup(tree, node);
            }
    
            return 1;
        }
    }
    
    return 0;
}
