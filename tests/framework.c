#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

extern char *basename(char *);

int int_cmp(void *AA, void *BB)
{
    int a = *(int *)AA;
    int b = *(int *)BB;
    
    if (a < b) {
        return bstree_lt;
    }
    
    if (a > b) {
        return bstree_gt;
    }
    
    return bstree_eq;
}

void freefn(void *key, void *data)
{
    free(key);
}

void copyfn(struct bstree_node *n, void *k, void *d)
{
    int *tmp = malloc(sizeof(*tmp));
    *tmp = *(int *)k;
    n->key = tmp;
    n->data = d;
}

struct bstree_node *find_no_children(struct bstree *tree)
{
    struct bstree_node *cur = tree->root;
    while (cur && (cur->left || cur->right)) {
        if (cur->left) {
            cur = cur->left;
            continue;
        }
        
        if (cur->right) cur = cur->right;
    }
    
    return cur;
}

struct bstree_node *find_one_child(struct bstree *tree)
{
    struct bstree_node *cur = tree->root;
    int which = 0;
    while (cur) {
        if (cur->left) which |= 1;
        if (cur->right) which |= 2;
        
        if (which == 0) {
            cur = NULL;
            break;
        } else if (which < 3) {
            break;
        } else {
            if (rand() % 2) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
            
            which = 0;
        }
    }
    
    return cur;
}

struct bstree_node *find_two_children(struct bstree *tree)
{
    struct bstree_node *cur = tree->root;
    int which = 0;
    while (cur) {
        if (cur->left) which |= 1;
        if (cur->right) which |= 2;
        
        if (which == 0) {
            cur = NULL;
            break;
        } else if (which == 1) {
            cur = cur->left;
            which = 0;
        } else if (which == 2) {
            cur = cur->right;
            which = 0;
        } else {
            break;
        }
    }
    
    return cur;
}

void test_start(char **argv)
{
    printf("Running Test \"%s\": ", basename(argv[0]));
}

void test_end()
{
    printf("Passed\n");
}
