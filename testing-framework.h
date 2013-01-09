#pragma once

extern int int_cmp(void *AA, void *BB);
extern void freefn(void *key, void *data);
extern void copyfn(struct bstree_node *n, void *k, void *d);
extern struct bstree_node *find_no_children(struct bstree *tree);
extern struct bstree_node *find_one_child(struct bstree *tree);
extern struct bstree_node *find_two_children(struct bstree *tree);

extern void test_start(char **argv);
extern void test_end();
