#include "expression.h"

double evaluate_expression(struct expression* e) {
    double result;

    if (e->is_value) {
        return e->value;
    }

    result = e->holder->operator_function(e);
    e->is_value = 1;
    e->value = result;

    return result;
}