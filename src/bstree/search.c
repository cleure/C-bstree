#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

/**
* Find node by key
*
* @param    struct bstree *tree
* @param    void *key
* @return   struct bstree_node *
*           Returns NULL on error.
**/
struct bstree_node *bstree_find(struct bstree *tree, void *key)
{
    int res;
    struct bstree_node *cur;
    
    if (!tree || !tree->root) return NULL;
    
    cur = tree->root;
    while (cur) {
        res = tree->cmpfn(key, cur->key);
        if (res == bstree_gt) {
            cur = cur->right;
        } else if (res == bstree_lt) {
            cur = cur->left;
        } else {
            break;
        }
    }
    
    return cur;
}

/**
* Find minimum node in tree
*
* @param    struct bstree *tree
* @return   struct bstree_node *
*           Returns NULL on error.
**/
struct bstree_node *bstree_find_min(struct bstree *tree)
{
    struct bstree_node *cur;
    if (!tree || !tree->root) return NULL;
    
    cur = tree->root;
    while (cur->left) cur = cur->left;
    
    return cur;
}

/**
* Find maximum node in tree
*
* @param    struct bstree *tree
* @return   struct bstree_node *
*           Returns NULL on error.
**/
struct bstree_node *bstree_find_max(struct bstree *tree)
{
    struct bstree_node *cur;
    if (!tree || !tree->root) return NULL;
    
    cur = tree->root;
    while (cur->right) cur = cur->right;
    
    return cur;
}
