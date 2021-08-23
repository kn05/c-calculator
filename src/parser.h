#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "operator.h"

struct operator_array {
    enum operator_kind op;
    size_t pos;
};

int operator_precedence(enum operator_kind op);

int binary(enum operator_kind op);

int compare(const struct operator_array* ap, const struct operator_array* bp);

struct expression parser(char* str, size_t size);

#endif