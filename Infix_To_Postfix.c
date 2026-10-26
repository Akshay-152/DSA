
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int main() {
    char infix[MAX], postfix[MAX], stack[MAX];
    int values[MAX];
    int top = -1, vtop = -1;
    int i, j = 0;
    int a, b, result;
    int valid = 1;

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    // Infix to Postfix Conversion
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum((unsigned char)ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }

            if (top == -1) {
                valid = 0;
                break;
            }
            top--;
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/') {

            while (top != -1 && stack[top] != '(') {
                int p1 = (stack[top] == '+' ||
                          stack[top] == '-') ? 1 : 2;
                int p2 = (ch == '+' || ch == '-') ? 1 : 2;

                if (p1 >= p2)
                    postfix[j++] = stack[top--];
                else
                    break;
            }

            stack[++top] = ch;
        }
        else {
            valid = 0;
            break;
        }
    }

    while (valid && top != -1) {
        if (stack[top] == '(') {
            valid = 0;
            break;
        }
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';

    if (!valid) {
        printf("Invalid expression!\n");
        return 1;
    }

    printf("Postfix Expression: %s\n", postfix);

    // Postfix Evaluation (single-digit operands only)
    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit((unsigned char)ch)) {
            values[++vtop] = ch - '0';
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/') {

            if (vtop < 1) {
                valid = 0;
                break;
            }

            b = values[vtop--];
            a = values[vtop--];

            if (ch == '+')
                result = a + b;
            else if (ch == '-')
                result = a - b;
            else if (ch == '*')
                result = a * b;
            else {
                if (b == 0) {
                    printf("Division by zero!\n");
                    return 1;
                }
                result = a / b;
            }

            values[++vtop] = result;
        }
        else {
            valid = 0;
            break;
        }
    }

    if (valid && vtop == 0)
        printf("Evaluation Result: %d\n", values[vtop]);
    else
        printf("Evaluation skipped: use numeric operands.\n");

    return 0;
}
