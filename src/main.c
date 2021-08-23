#include "expression.h"
#include "operator.h"
#include "parser.h"
#include "tree.h"

int main() {
    char x[100] = {};
    printf("expression input > ");
    scanf("%s", &x);
    size_t size = 0;

    for (size_t i = 0; i < 100; ++i) {
        if (x[i] == '\0') {
            size = i;
            break;
        }
    }
    struct expression r = parser(x, size);

    print_t(make_tree(r, 0, 0));

    double rx = evaluate_expression(&r);

    printf("result : %f", rx);
}