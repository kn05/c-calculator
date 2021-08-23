#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "operator.h"

struct node {
    int is_left;
    struct node* parent;
    struct node* left;
    struct node* right;
    char text[20];
};

struct node* make_tree(struct expression e, struct node* p, int is_left);

int _print_t(struct node* tree, int is_left, int offset, int depth, char s[20][255]);

void print_t(struct node* tree);

#endif