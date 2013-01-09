cmake_minimum_required (VERSION 2.6)
project (c_bstree)

set (c_bstree_VERSION_MAJOR 0)
set (c_bstree_VERSION_MINOR 1)
set (c_bstree_VERSION_PATCH 0)
set (CMAKE_C_FLAGS "-Wall -std=c89 -g")

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories(
    "${PROJECT_BINARY_DIR}"
    "./include"
)

set(BSTREE_SOURCES
    src/bstree/bstree.c
    src/bstree/insert.c
    src/bstree/remove.c
    src/bstree/compare.c
    src/bstree/rotate.c
    src/bstree/search.c
    src/bstree/traverse.c
    src/rbtree/insert.c
    src/rbtree/remove.c
    src/debug.c
)

add_library(bstree ${BSTREE_SOURCES})

add_executable(test-01-insert tests/test-01-insert.c tests/framework.c)
target_link_libraries(test-01-insert bstree)

add_executable(test-02-rotate tests/test-02-rotate.c tests/framework.c)
target_link_libraries(test-02-rotate bstree)

add_executable(test-03-remove tests/test-03-remove.c tests/framework.c)
target_link_libraries(test-03-remove bstree)

add_executable(test-05-traverse tests/test-05-traverse.c tests/framework.c)
target_link_libraries(test-05-traverse bstree)

add_executable(test-06-rbtree-insert tests/test-06-rbtree-insert.c tests/framework.c)
target_link_libraries(test-06-rbtree-insert bstree)
