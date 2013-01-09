#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

void rbtree_remove_cleanup(struct bstree *tree, struct bstree_node *cur)
{
    /* FIXME */
}
