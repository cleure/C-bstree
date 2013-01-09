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


    (32)
    /  \
   20   40
  /  \
 15  25
 
ROTATE RIGHT(32)

    20
   /  \
  15  32
      / \
     25 40
     
     20
   /   \
  15x   32
       /  \
      25y 40z

1:
     20
   /   \
  15x  25y    32
             /  \
            25y 40z

2:

              32
             /  \
           20    40z
         /   \
        15x  25y                


ROTATE LEFT(20)

     32
    /  \
   20   40
  /  \
 15  25
     
*/

void test_case1(struct bstree *tree)
{
    struct bstree_node *cur;

    cur = tree->root;
    
    /* Check values */
    assert(*(int*)cur->key == 20);
    assert(*(int*)cur->left->key == 15);
    assert(*(int*)cur->right->key == 32);
    assert(*(int*)cur->right->right->key == 40);
    assert(*(int*)cur->right->left->key == 25);
    
    /* Check tree structure */
    assert(cur == cur->left->parent);
    assert(cur->left->left == NULL);
    assert(cur->left->right == NULL);
    assert(cur == cur->right->parent);
    assert(cur->right->left->parent == cur->right);
    assert(cur->right->left->left == NULL);
    assert(cur->right->left->right == NULL);
    assert(cur->right->right->parent == cur->right);
    assert(cur->right->right->left == NULL);
    assert(cur->right->right->right == NULL);
}

void test_case2(struct bstree *tree)
{
    struct bstree_node *cur;
    
    /* Check values */
    cur = tree->root;
    assert(*(int*)cur->key == 32);
    assert(*(int*)cur->left->key == 20);
    assert(*(int*)cur->left->right->key == 25);
    assert(*(int*)cur->left->left->key == 15);
    assert(*(int*)cur->right->key == 40);
    
    /* Check tree structure */
    assert(cur == cur->left->parent);
    assert(cur->left->right->parent == cur->left);
    assert(cur->left->right->left == NULL);
    assert(cur->left->right->right == NULL);
    assert(cur->left->left->parent == cur->left);
    assert(cur->left->left->left == NULL);
    assert(cur->left->left->right == NULL);
    assert(cur == cur->right->parent);
    assert(cur->right->left == NULL);
    assert(cur->right->right == NULL);
}

int main(int argc, char **argv)
{
    int i;
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);
    
    int test[] = {20, 15, 32, 40, 25};
    for (i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
        bstree_insert(tree, &test[i], NULL);
    }
    
    test_start(argv);
    test_case1(tree);
    
    assert(bstree_rotate_left(NULL, NULL) == 0);
    assert(bstree_rotate_left(NULL, tree->root) == 0);
    assert(bstree_rotate_left(tree, NULL) == 0);
    
    assert(bstree_rotate_left(tree, tree->root) == 1);
    test_case2(tree);
    
    assert(bstree_rotate_right(NULL, NULL) == 0);
    assert(bstree_rotate_right(NULL, tree->root) == 0);
    assert(bstree_rotate_right(tree, NULL) == 0);
    
    assert(bstree_rotate_right(tree, tree->root) == 1);
    test_case1(tree);
    
    test_end();
    bstree_delete(tree);

    return 0;
}
