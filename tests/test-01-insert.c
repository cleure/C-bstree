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

Test 1

         31
       /    \
     (15)    35
     /  \    /
    10  16  32

*/

void test_case1()
{
    int i;
    int data[] = {31, 15, 10, 16, 35, 32};
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);
    struct bstree_node *cur;
    
    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        assert(bstree_insert(tree, &data[i], NULL) == 1);
    }
    
    cur = tree->root;
    assert(*(int*)cur->key == 31);
    assert(*(int*)cur->left->key == 15);
    assert(*(int*)cur->left->left->key == 10);
    assert(*(int*)cur->left->right->key == 16);
    assert(*(int*)cur->right->key == 35);
    assert(*(int*)cur->right->left->key == 32);
    
    assert(cur->left->parent == cur);
    assert(cur->left->left->parent == cur->left);
    assert(cur->left->right->parent == cur->left);
    assert(cur->right->parent == cur);
    assert(cur->right->left->parent == cur->right);
    
    bstree_delete(tree);
}

void test_case2()
{
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);

    assert(bstree_insert(NULL, NULL, NULL) == 0);
    assert(bstree_insert(tree, NULL, NULL) == 0);
    bstree_delete(tree);
}

int main(int argc, char **argv)
{
    /*int data[] = {31, 15, 10, 20, 19, 16, 35, 32}; */
    /*int test3[] = {31, 15, 10, 20, 19, 16, 17, 35, 32}; */
    
    test_start(argv);
    test_case1();
    test_case2();
    test_end();
    
    return 0;
}
