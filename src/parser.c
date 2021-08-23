#include "parser.h"

int operator_precedence(enum operator_kind op) {
    switch (op) {
        case unary_add:
            return 0;
            break;
        case unary_sub:
            return 0;
            break;
        case mult:
            return 1;
            break;
        case divi:
            return 1;
            break;
        case add:
            return 2;
            break;
        case sub:
            return 2;
            break;
        default:
            printf("[Error] unknown operator (function: operator_precedence) \n");
            return -1;
    }
}

int binary(enum operator_kind op) {
    switch (op) {
        case unary_add:
            return 0;
            break;
        case unary_sub:
            return 0;
            break;
        case mult:
            return 1;
            break;
        case divi:
            return 1;
            break;
        case add:
            return 1;
            break;
        case sub:
            return 1;
            break;
        default:
            return -1;
    }
}

int compare(const struct operator_array* ap, const struct operator_array* bp) {
    const struct operator_array a = *ap;
    const struct operator_array b = *bp;

    if (operator_precedence(a.op) != operator_precedence(b.op)) {
        return operator_precedence(a.op) < operator_precedence(b.op);
    } else {
        return a.pos < b.pos;
    }
}

struct expression parser(char* str, size_t size) {
    struct expression e;
    e.is_value = 1;

    for (size_t i = 0; i < size; ++i) {
        if ((str[i] < '0' || '9' < str[i]) && str[i] != '.') {
            e.is_value = 0;
            break;
        }
    }
    if (e.is_value) {
        char val[20] = {};
        sprintf(val, "%.*s", size, str);
        e.value = strtod(val, NULL);
        return e;
    } else {
        struct operator_array operators[16];
        size_t operator_num = 0;
        size_t braket = 0;
        for (size_t i = 0; i < size; ++i) {
            if (str[i] == '(') {
                braket++;
            }
            if (str[i] == ')') {
                braket--;
            }
            if (braket == 0 && strchr("+-*/", str[i])) {
                if (i == 0) {
                    switch (str[i]) {
                        case '+':
                            operators[operator_num].op = unary_add;
                            break;
                        case '-':
                            operators[operator_num].op = unary_sub;
                            break;
                        default:
                            printf("first, but mult or div\n");
                            break;
                    }
                } else {
                    switch (str[i]) {
                        case '+':
                            operators[operator_num].op = add;
                            break;
                        case '-':
                            operators[operator_num].op = sub;
                            break;
                        case '*':
                            operators[operator_num].op = mult;
                            break;
                        case '/':
                            operators[operator_num].op = divi;
                            break;
                        default:
                            printf("not oper\n");
                            break;
                    }
                }
                operators[operator_num].pos = i;
                operator_num++;
            }
        }

        if (braket != 0) {
            printf("braket is not complete. \n");  // error!
        }

        if (operator_num == 0) {
            printf("it is in the braket: %.*s\n", size - 2, str + 1);
            return parser(str + 1, size - 2);
        }

        qsort(operators, operator_num, sizeof(struct operator_array), compare);

        if (binary(operators[0].op)) {
            printf("\n>> parse to : %.*s | %.*s\n", operators[0].pos, str, size - operators[0].pos - 1,
                   str + operators[0].pos + 1);
            e.holder = malloc(sizeof(size_t) + 2 * sizeof(struct expression) + 1);
            e.holder->operand_count = 2;
            e.holder->expression_arrays[0] = parser(str, operators[0].pos);
            e.holder->expression_arrays[1] = parser(str + operators[0].pos + 1, size - operators[0].pos - 1);

        } else {
            printf("\n>> parse to : | %.*s \n", operators[0].pos, str + 1, size - 1);
            e.holder = malloc(sizeof(size_t) + 1 * sizeof(struct expression) + 1);
            e.holder->operand_count = 1;
            e.holder->expression_arrays[0] = parser(str + 1, size - 1);
        }

        switch (operators[0].op) {
            case unary_add:
                e.holder->operator_function = operator_unary_add;
                break;
            case unary_sub:
                e.holder->operator_function = operator_unary_sub;
                break;
            case mult:
                e.holder->operator_function = operator_multiply;
                break;
            case divi:
                e.holder->operator_function = operator_div;
                break;
            case add:
                e.holder->operator_function = operator_add;
                break;
            case sub:
                e.holder->operator_function = operator_sub;
                break;
            default:
                break;
        }
        return e;
    }
}