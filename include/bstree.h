#pragma once
#include <stdint.h>

#ifndef BSTREE_SYMBOL
  #define BSTERE_SYMBOL(in) in
#endif

#ifndef __BSTREE_EXTERN
    #define __BSTREE_EXTERN extern
#endif

struct bstree_node;
struct bstree;

enum bstree_compare {
    bstree_eq,
    bstree_gt,
    bstree_lt
};

enum bstree_color {
    bstree_black = 1,
    bstree_red
};

typedef void    (*bstree_copyfn)(struct bstree_node *, void *key, void *data);
typedef void    (*bstree_freefn)(void *key, void *data);
typedef int     (*bstree_cmpfn)(void *, void *);
typedef int     (*bstree_insertfn)(struct bstree *tree, void *key, void *data);
typedef int     (*bstree_removefn)(struct bstree *tree, void *key);

struct bstree_node {
    void *key;
    void *data;
    
    struct bstree_node *left;
    struct bstree_node *right;
    struct bstree_node *parent;
    
    uint8_t color;
};

struct bstree {
    struct bstree_node *root;
    
    bstree_copyfn copyfn;
    bstree_freefn freefn;
    bstree_cmpfn cmpfn;
    bstree_insertfn insert;
    bstree_removefn remove;
    
    uint8_t is_redblack;
};

struct bstree_traverse {
    struct bstree *tree;
    struct bstree_node *cur;
    struct bstree_node **stack;
    uint32_t stack_size;
    uint32_t stack_used;
};

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
__BSTREE_EXTERN
struct bstree *bstree_new(
            bstree_copyfn copyfn,
            bstree_freefn freefn,
            bstree_cmpfn cmpfn,
            uint8_t redblack);

/**
* Delete a bstree/rbtree, created by bstree_new.
*
* @param    struct bstree *tree
* @return   void
**/
__BSTREE_EXTERN
void bstree_delete(struct bstree *tree);

/**
* Insert item into bstree, replacing existing item if it already exists.
*
* @param    struct bstree *tree
* @param    void *key
* @param    void *data
* @return   0 on error, 1 on success
**/
__BSTREE_EXTERN
int bstree_insert(struct bstree *tree, void *key, void *data);

/**
* Remove item from bstree.
*
* @param    struct bstree *tree
* @param    void *key
* @return   0 on error, 1 on success
**/
__BSTREE_EXTERN
int bstree_remove(struct bstree *tree, void *key);

/**
* Integer compare function
*
* @param    void *A
* @param    void *B
* return    int, see also enum bstree_compare
**/
__BSTREE_EXTERN
int bstree_int_cmpfn(void *A, void *B);

/**
* String compare function
*
* @param    void *A
* @param    void *B
* return    int, see also enum bstree_compare
**/
__BSTREE_EXTERN
int bstree_string_cmpfn(void *A, void *B);

/**
* Perform left rotation, from *x
*
* @param    struct bstree *tree
* @param    struct bstree_node *x
* @return   0 on error, 1 on success
**/
__BSTREE_EXTERN
int bstree_rotate_left(struct bstree *tree, struct bstree_node *x);

/**
* Perform right rotation, from *x
*
* @param    struct bstree *tree
* @param    struct bstree_node *x
* @return   0 on error, 1 on success
**/
__BSTREE_EXTERN
int bstree_rotate_right(struct bstree *tree, struct bstree_node *x);

/**
* Find node by key
*
* @param    struct bstree *tree
* @param    void *key
* @return   struct bstree_node *
*           Returns NULL on error.
**/
__BSTREE_EXTERN
struct bstree_node *bstree_find(struct bstree *tree, void *key);

/**
* Find minimum node in tree
*
* @param    struct bstree *tree
* @return   struct bstree_node *
*           Returns NULL on error.
**/
__BSTREE_EXTERN
struct bstree_node *bstree_find_min(struct bstree *tree);

/**
* Find maximum node in tree
*
* @param    struct bstree *tree
* @return   struct bstree_node *
*           Returns NULL on error.
**/
__BSTREE_EXTERN
struct bstree_node *bstree_find_max(struct bstree *tree);

/**
* Go left in tree/subtree.
*
* @param    struct bstree_node *cur
* @return   struct bstree_node *
*           NULL when end of tree reached
**/
__BSTREE_EXTERN
struct bstree_node *bstree_left(struct bstree_node *cur);

/**
* Go right in tree/subtree.
*
* @param    struct bstree_node *cur
* @return   struct bstree_node *
*           NULL when end of tree reached
**/
__BSTREE_EXTERN
struct bstree_node *bstree_right(struct bstree_node *cur);

/**
* Start in-order traversal
*
* @param    struct bstree *tree
* @return   struct bstree_traverse *
*           NULL on error
**/
__BSTREE_EXTERN
struct bstree_traverse *bstree_traverse_start(struct bstree *tree);

/**
* End in-order traversal
*
* @param    struct bstree_traverse *trv
* @return   void
**/
__BSTREE_EXTERN
void bstree_traverse_end(struct bstree_traverse *trv);

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
__BSTREE_EXTERN
struct bstree_node *bstree_traverse_next(struct bstree_traverse *trv);

/*

rbtree_insert
rbtree_remove

*/
