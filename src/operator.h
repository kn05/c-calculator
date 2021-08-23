#ifndef OPERATOR_H_
#define OPERATOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"

enum operator_kind { add = 0, sub, mult, divi, unary_add, unary_sub };

double operator_multiply(struct expression* e);
double operator_add(struct expression* e);
double operator_div(struct expression* e);
double operator_sub(struct expression* e);
double operator_unary_add(struct expression* e);
double operator_unary_sub(struct expression* e);

typedef double (*oper_function_t)(struct expression*);
char* operator_name(oper_function_t oper);

#endif