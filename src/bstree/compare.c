#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"

#define __BSTREE_EXTERN
#include "bstree.h"

#ifdef DEBUG
    #include "debug.h"
#endif

static const char string_table[] = {95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 2, 105, 106, 1, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 3, 32, 7, 18, 19, 20, 22, 6, 11, 12, 23, 24, 30, 5, 0, 9, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 125, 126, 28, 25, 29, 31, 17, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 13, 8, 14, 21, 4, 26, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 15, 10, 16, 27, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, };

/**
* Integer compare function
*
* @param    void *A
* @param    void *B
* return    int, see also enum bstree_compare
**/
int bstree_int_cmpfn(void *A, void *B)
{
    if (*(int*)A < *(int*)B) {
        return bstree_lt;
    }
    
    if (*(int*)A > *(int*)B) {
        return bstree_gt;
    }
    
    return bstree_eq;
}

/**
* String compare function
*
* @param    void *A
* @param    void *B
* return    int, see also enum bstree_compare
**/
int bstree_string_cmpfn(void *A, void *B)
{
    char *a = A;
    char *b = B;
    int i, res;

    for (i = 0; a[i] && b[i]; i++) {
        res = string_table[(int)a[i]] - string_table[(int)b[i]];
        if (res < 0) return bstree_lt;
        if (res > 0) return bstree_gt;
    }
    
    if (a[i] == b[i]) return bstree_eq;
    if (a[i] == 0) return bstree_lt;
    
    return bstree_gt;
}
