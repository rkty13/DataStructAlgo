#include <iostream>
#include "PNode.h"

/* Get the successor PNode in-order. */
PNode * successor(PNode *x) {
    if (x->right) {
        x = x->right;
        while (x->left)x = x->left;
    } else {
        while (x->parent && x->parent->right == x)
            x = x->parent;
    }
    return x->parent;
}

int main() {}