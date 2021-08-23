#include "operator.h"

double operator_multiply(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]) * evaluate_expression(&exp->expression_arrays[1]);

    free(e->holder);
    return result;
}
double operator_add(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]) + evaluate_expression(&exp->expression_arrays[1]);
    free(e->holder);
    return result;
}
double operator_div(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]) / evaluate_expression(&exp->expression_arrays[1]);

    free(e->holder);
    return result;
}
double operator_sub(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]) - evaluate_expression(&exp->expression_arrays[1]);
    free(e->holder);
    return result;
}
double operator_unbinary_add(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]);

    free(e->holder);
    return result;
}
double operator_unbinary_sub(struct expression* e) {
    double result = 0;

    struct expression_holder* exp = e->holder;

    result = evaluate_expression(&exp->expression_arrays[0]) * (-1);

    free(e->holder);
    return result;
}

typedef double (*oper_function_t)(struct expression*);
char* operator_name(oper_function_t oper) {
    if (oper == operator_add) {
        return "ADD";
    } else if (oper == operator_sub) {
        return "SUB";
    } else if (oper == operator_multiply) {
        return "MUL";
    } else if (oper == operator_div) {
        return "DIV";
    } else if (oper == operator_unbinary_add) {
        return "U_ADD";
    } else if (oper == operator_unbinary_sub) {
        return "U_SUB";
    } else {
        return "UN_OP";
    }
}