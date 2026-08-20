/* EX.NO: 9 - Simple Code Optimization Techniques
   AIM: Implement Constant Folding, Strength Reduction, Algebraic Simplification */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char code[100][100];

int main() {
    int i = 0;
    printf("Enter Three Address Code (empty line to stop):\n");
    while (1) {
        fgets(code[i], sizeof(code[i]), stdin);
        code[i][strcspn(code[i], "\n")] = '\0';
        if (strlen(code[i]) == 0) break;
        i++;
    }
    int lines = i;
    printf("\nUnoptimized Code:\n");
    for (i = 0; i < lines; i++) printf("  %s\n", code[i]);

    printf("\nOptimized Code:\n");
    for (i = 0; i < lines; i++) {
        char lhs, op1, op2, opr;
        int val1, val2, res;
        if (sscanf(code[i], "%c=%c%c%c;", &lhs, &op1, &opr, &op2) == 4) {
            if (isdigit(op1) && isdigit(op2)) {
                /* Constant Folding */
                val1 = op1 - '0'; val2 = op2 - '0';
                switch (opr) {
                    case '+': res = val1 + val2; break;
                    case '-': res = val1 - val2; break;
                    case '*': res = val1 * val2; break;
                    case '/': res = val2 != 0 ? val1 / val2 : 0; break;
                    default:  res = 0;
                }
                printf("  %c=%d;\t\t// Constant Folding\n", lhs, res);
            } else if ((opr == '*' && op2 == '1') || (opr == '/' && op2 == '1')) {
                /* Algebraic Simplification: x*1 = x, x/1 = x */
                printf("  %c=%c;\t\t// Algebraic Simplification (x*1 or x/1)\n", lhs, op1);
            } else if ((opr == '+' && op2 == '0') || (opr == '-' && op2 == '0')) {
                /* Algebraic Simplification: x+0 = x, x-0 = x */
                printf("  %c=%c;\t\t// Algebraic Simplification (x+0 or x-0)\n", lhs, op1);
            } else if (opr == '*' && op2 == '2') {
                /* Strength Reduction: x*2 -> x+x */
                printf("  %c=%c+%c;\t\t// Strength Reduction (x*2 -> x+x)\n", lhs, op1, op1);
            } else {
                printf("  %s\n", code[i]);
            }
        } else {
            printf("  %s\n", code[i]);
        }
    }
    return 0;
}
