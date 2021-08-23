#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct expression;
struct expression_holder;

struct expression {
    int is_value;
    union {
        double value;
        struct expression_holder* holder;
    };
};

struct expression_holder {
    double (*operator_function)(struct expression* e);

    size_t operand_count;
    struct expression expression_arrays[0];
};

double evaluate_expression(struct expression* e);

#endif