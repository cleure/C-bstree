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

Test 2


         31
       /    \
     (15)    35
     /  \    /
    10  20  32
        /
       19
       /
      16

Test 3


         31
       /    \
     (15)    35
     /  \    /
    10  20  32
        /
       19
       /
      16
       \
        17
      

Test all 3 delete cases

*/

/*int data[] = {31, 15, 10, 16, 35, 32}; */
/*int data[] = {31, 15, 10, 20, 19, 16, 35, 32}; */
/*int test3[] = {31, 15, 10, 20, 19, 16, 17, 35, 32}; */

void test_case1()
{
    int i;
    int data[] = {31, 15, 10, 16, 35, 32};
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);
    struct bstree_node *cur;
    
    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        bstree_insert(tree, &data[i], NULL);
    }
    
    cur = tree->root;
    assert(*(int*)cur->key == 31);
    assert(*(int*)cur->left->key == 15);
    assert(*(int*)cur->left->left->key == 10);
    assert(*(int*)cur->left->right->key == 16);
    assert(*(int*)cur->right->key == 35);
    assert(*(int*)cur->right->left->key == 32);
    
    i = 15;
    bstree_remove(tree, &i);
    
    assert(*(int*)cur->key == 31);
    assert(*(int*)cur->left->key == 16);
    assert(*(int*)cur->left->left->key == 10);
    assert(*(int*)cur->right->key == 35);
    assert(*(int*)cur->right->left->key == 32);
    
    assert(cur->left->parent == cur);
    assert(cur->left->left->parent == cur->left);
    assert(cur->left->right == NULL);
    
    bstree_delete(tree);
}

void test_case2()
{
    int i;
    int data[] = {31, 15, 10, 20, 19, 16, 35, 32};
    struct bstree *tree = bstree_new(&copyfn, &freefn, &int_cmp, 0);
    struct bstree_node *cur;
    
    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        bstree_insert(tree, &data[i], NULL);
    }
    
    cur = tree->root;
    
    /*
    // FIXME: TODO
    */
    
    bstree_delete(tree);
}

void test_case3()
{
    /*
    // FIXME: TODO
    */
}

int main(int argc, char **argv)
{
    test_start(argv);
    test_case1();
    test_case2();
    test_case3();
    test_end();
    
    return 0;
}
