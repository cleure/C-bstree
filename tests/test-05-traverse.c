#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

#include "testing-framework.h"

/*

                     16
                   /    \
                  10    18
                 /  \   / \
                5   12 17  22
               / \ /  \    / \
              3  6 11  14  20 30
             / \      /     \   \
            1   4    13      21  41
                                 /
                                38

*/

int data[] = {
    16, 10, 18, 5, 12, 17, 22, 3, 6, 11, 14, 20, 30, 1, 4, 13, 21, 41, 38
};

int sorted[] = {
    1, 3, 4, 5, 6, 10, 11, 12, 13, 14, 16, 17, 18, 20, 21, 22, 30, 38, 41
};

int main(int argc, char **argv)
{
    int i;
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);
    struct bstree_traverse *trv;
    struct bstree_node *cur;

    test_start(argv);
    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        assert(bstree_insert(tree, &data[i], NULL) == 1);
    }
    
    assert((trv = bstree_traverse_start(tree)) != NULL);
    
    i = 0;
    while ((cur = bstree_traverse_next(trv))) {
        assert(*(int*)cur->key == sorted[i]);
        i++;
    }
    
    assert(i == sizeof(data)/sizeof(data[0]));
    
    bstree_traverse_end(trv);
    test_end();
    
    bstree_delete(tree);
    return 0;
}
