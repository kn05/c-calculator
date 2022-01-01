#include "expression.h"
#include "operator.h"
#include "parser.h"
#include "tree.h"

int main() {
    while (1) {
        char x[100] = {};
        printf("expression input > ");
        scanf("%s", &x);
        if (x[0] == 'e') {
            break;
        }
        struct expression r = parser(x, strlen(x));
        print_tree(make_tree(r, 0, 0));
        double rx = evaluate_expression(&r);
        printf("result : %f\n", rx);
    }
    printf("calculator is ended.\n");
    return 0;
}