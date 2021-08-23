#include "tree.h"

struct node* make_tree(struct expression e, struct node* p, int is_left) {
    struct node* t = malloc(sizeof(struct node));
    size_t textlength = 9;
    t->parent = p;

    if (e.is_value) {
        if (e.value >= 1000) {
            sprintf(t->text, "(%.3E)", e.value);
        } else if (e.value >= 0) {
            sprintf(t->text, "(%09.5f)", e.value);
        } else if (e.value <= -1000) {
            sprintf(t->text, "(%.2E)", e.value);
        } else {
            sprintf(t->text, "(%09.5f)", e.value);
        }
        t->left = NULL;
        t->right = NULL;
    } else if (e.holder->operand_count == 2) {
        sprintf(t->text, "[%s]", operator_name(e.holder->operator_function));
        t->left = make_tree(e.holder->expression_arrays[0], t, 1);
        t->right = make_tree(e.holder->expression_arrays[1], t, 0);
    } else if (e.holder->operand_count == 1) {
        sprintf(t->text, "[%s]", operator_name(e.holder->operator_function));
        t->left = make_tree(e.holder->expression_arrays[0], t, 1);
        t->right = NULL;
    }
    return t;
}

int _print_tree(struct node* tree, int is_left, int offset, int depth, char s[20][255]) {
    if (!tree) return 0;

    int width = strlen(tree->text);  // 11

    int left = _print_t(tree->left, 1, offset, depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++) {
        s[depth][offset + left + i] = tree->text[i];
    }

    if (depth && is_left) {
        for (int i = 0; i < width + right; i++) {
            s[depth - 1][offset + left + width / 2 + i] = '-';
        }
        s[depth - 1][offset + left + width / 2] = '.';
    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++) {
            s[depth - 1][offset - width / 2 + i] = '-';
        }
        s[depth - 1][offset + left + width / 2] = '.';
    }

    return left + width + right;
}

void print_tree(struct node* tree) {
    char s[20][255];
    for (int i = 0; i < 20; i++) sprintf(s[i], "%100s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++) printf("%s%%\n", s[i]);
}
