#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

/**
* Insert cleanup function, for Red-Black Tree
*
* @param    struct bstree *tree
* @param    struct bstree_node *cur
* @return   0 on error, 1 on success
**/
void rbtree_insert_cleanup(struct bstree *tree, struct bstree_node *cur)
{
    struct bstree_node *parent, *grandparent, *uncle, *tmp;
    uint8_t uncle_color;
    
    /* Set color to red */
    cur->color = bstree_red;
    
    /* Loop to root */
    while (cur->parent && cur->parent->color == bstree_red) {
        parent = cur->parent;
        grandparent = parent->parent;
        
        if (parent == grandparent->left) {
            uncle = grandparent->right;
            if (uncle) {
                uncle_color = uncle->color;
            } else {
                uncle_color = bstree_black;
            }
            
            if (uncle_color == bstree_red) {
                uncle->color = bstree_black;
                parent->color = bstree_black;
                grandparent->color = bstree_red;
                cur = grandparent;
                continue;
            }
            
            if (cur == parent->right) {
                bstree_rotate_left(tree, parent);
                
                tmp = parent;
                parent = cur;
                cur = tmp;
            }
            
            parent->color = bstree_black;
            grandparent->color = bstree_red;
            bstree_rotate_right(tree, grandparent);
        } else {
            uncle = grandparent->left;
            if (uncle) {
                uncle_color = uncle->color;
            } else {
                uncle_color = bstree_black;
            }
            
            if (uncle_color == bstree_red) {
                uncle->color = bstree_black;
                parent->color = bstree_black;
                grandparent->color = bstree_red;
                cur = grandparent;
                continue;
            }
            
            if (cur == parent->left) {
                bstree_rotate_right(tree, parent);
                
                tmp = parent;
                parent = cur;
                cur = tmp;
            }
            
            parent->color = bstree_black;
            grandparent->color = bstree_red;
            bstree_rotate_left(tree, grandparent);
        }
    }
    
    tree->root->color = bstree_black;
}
