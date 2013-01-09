#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

#define STACK_SIZE 64

/**
* Go left in tree/subtree.
*
* @param    struct bstree_node *cur
* @return   struct bstree_node *
*           NULL when end of tree reached
**/
struct bstree_node *bstree_left(struct bstree_node *cur) {
    return !cur ? NULL : cur->left;
}

/**
* Go right in tree/subtree.
*
* @param    struct bstree_node *cur
* @return   struct bstree_node *
*           NULL when end of tree reached
**/
struct bstree_node *bstree_right(struct bstree_node *cur) {
    return !cur ? NULL : cur->right;
}

/**
* Start in-order traversal
*
* @param    struct bstree *tree
* @return   struct bstree_traverse *
*           NULL on error
**/
struct bstree_traverse *bstree_traverse_start(struct bstree *tree)
{
    struct bstree_traverse *trv;
    struct bstree_node **stack;
    
    trv = malloc(sizeof(*trv));
    if (!trv) return NULL;
    
    stack = malloc(sizeof(*stack) * STACK_SIZE);
    if (!stack) {
        free(trv);
        return NULL;
    }
    
    memset(trv, 0, sizeof(*trv));
    memset(stack, 0, sizeof(*stack) * STACK_SIZE);
    
    trv->tree = tree;
    trv->cur = tree->root;
    trv->stack = stack;
    trv->stack_size = STACK_SIZE;
    trv->stack_used = 0;
    
    return trv;
}

/**
* End in-order traversal
*
* @param    struct bstree_traverse *trv
* @return   void
**/
void bstree_traverse_end(struct bstree_traverse *trv)
{
    free(trv->stack);
    free(trv);
}

/**
* Get next node in traversal (in-order).
*
* @param    struct bstree_traverse *trv
* @return   struct bstree_node *
*           NULL when end of traversal reached.
*           NULL on memory reallocation error.
*               In both cases, bstree_traverse_end() needs to
*               be called afterwards.
**/
struct bstree_node *bstree_traverse_next(struct bstree_traverse *trv)
{
    struct bstree_node *cur;
    struct bstree_node **tmp;
    
    if (!trv) return NULL;
    
    cur = trv->cur;
    while (cur) {
        if (!(trv->stack_used < trv->stack_size)) {
            /* Allocate more space for stack */
            if (trv->stack_size < 2) {
                trv->stack_size = 32;
            }
            
            trv->stack_size *= 2;
            tmp = realloc(trv->stack, sizeof(*trv->stack) * trv->stack_size);
            if (!tmp) {
                return NULL;
            }
            
            trv->stack = tmp;
        }
        
        /* Push */
        trv->stack[trv->stack_used++] = cur;
        cur = cur->left;
    }
    
    if (trv->stack_used == 0) {
        return NULL;
    }
    
    /* Pop */
    cur = trv->stack[--trv->stack_used];
    trv->cur = cur->right;
    return cur;
}
