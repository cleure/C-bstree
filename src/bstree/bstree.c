#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

/**
* Create a new bstree to rbtree.
*
* @param    bstree_copyfn copyfn    - Pointer to copy function
* @param    bstree_freefn freefn    - Pointer to free function
* @param    bstree_cmpfn cmpfn      - Pointer to compare function
* @param    uint8_t redblack        - If non-zero, initialize as Red-Black Tree
*
* @return   struct bstree *, NULL on error
**/
struct bstree *bstree_new(
            bstree_copyfn copyfn,
            bstree_freefn freefn,
            bstree_cmpfn cmpfn,
            uint8_t redblack) {
    
    struct bstree *tree;
    tree = malloc(sizeof(*tree));
    if (!tree) {
        return NULL;
    }
    
    memset(tree, 0, sizeof(*tree));
    tree->copyfn = copyfn;
    tree->freefn = freefn;
    tree->cmpfn = cmpfn;
    tree->root = NULL;
    
    if (redblack) {
        tree->is_redblack = 1;
        tree->insert = NULL;
        tree->remove = NULL;
    } else {
        tree->insert = NULL;
        tree->remove = NULL;
    }
    
    return tree;
}

/**
* Delete a bstree/rbtree, created by bstree_new.
*
* @param    struct bstree *tree
* @return   void
**/
void bstree_delete(struct bstree *tree)
{
    struct bstree_node *cur, **node_ptr;
    
    if (!tree->root) {
        free(tree);
        return;
    }
    
    cur = tree->root;
    while (tree->root->left || tree->root->right) {
        if (cur->left) {
            node_ptr = &cur->left;
            cur = cur->left;
            continue;
        }
        
        if (cur->right) {
            node_ptr = &cur->right;
            cur = cur->right;
            continue;
        }
        
        cur = cur->parent;
        if (tree->freefn) {
            tree->freefn((*node_ptr)->key, (*node_ptr)->data);
        }
        
        free(*node_ptr);
        *node_ptr = NULL;
        
        if (cur->parent) {
            if (cur->parent->left == cur) {
                node_ptr = &(cur->parent)->left;
            } else {
                node_ptr = &(cur->parent)->right;
            }
        }
    }
    
    if (tree->freefn) {
        tree->freefn(tree->root->key, tree->root->data);
    }
    
    free(tree->root);
    free(tree);
}
