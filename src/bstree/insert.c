#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

extern void rbtree_insert_cleanup(struct bstree *tree, struct bstree_node *cur);

/**
* Insert item into bstree, replacing existing item if it already exists.
*
* @param    struct bstree *tree
* @param    void *key
* @param    void *data
* @return   0 on error, 1 on success
**/
int bstree_insert(struct bstree *tree, void *key, void *data)
{
    struct bstree_node *cur, *parent, **node_ptr;
    int res;
    
    if (!tree || !key) return 0;
    if (!tree->root) {
        parent = NULL;
        cur = NULL;
        node_ptr = &tree->root;
        goto insert;
    }
    
    cur = tree->root;
    while (cur) {
        res = tree->cmpfn(key, cur->key);
        
        if (res == bstree_lt) {
            node_ptr = &cur->left;
            parent = cur;
            cur = cur->left;
            continue;
        }
        
        if (res == bstree_gt) {
            node_ptr = &cur->right;
            parent = cur;
            cur = cur->right;
            continue;
        }
        
        if (res == bstree_eq) {
            /* Replace existing */
            if (tree->freefn) {
                tree->freefn(cur->key, cur->data);
            }
            
            if (tree->copyfn) {
                tree->copyfn(cur, key, data);
            } else {
                cur->key = key;
                cur->data = data;
            }
            
            return 1;
        }
    }
    
insert:
    *node_ptr = malloc(sizeof(struct bstree_node));
    if (!*node_ptr) {
        return 0;
    }
    
    if (tree->copyfn) {
        tree->copyfn(*node_ptr, key, data);
    } else {
        (*node_ptr)->key = key;
        (*node_ptr)->data = data;
    }
    
    (*node_ptr)->color = bstree_red;
    (*node_ptr)->parent = parent;
    (*node_ptr)->left = NULL;
    (*node_ptr)->right = NULL;
    
    if (tree->is_redblack) {
        rbtree_insert_cleanup(tree, *node_ptr);
    }

    return 1;
}

