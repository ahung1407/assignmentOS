#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"  // Header của các hàm

int main() {
    char input[100];
    double a, b, result;
    char op;

    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);  // Đọc đầu vào từ người dùng

        if (strncmp(input, "EXIT", 4) == 0) {
            break;
        }

        if (sscanf(input, "%lf %c %lf", &a, &op, &b) != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        switch (op) {
            case '+':
                result = add(a, b);
                break;
            case '-':
                result = subtract(a, b);
                break;
            case 'x':
            case '*':
                result = multiply(a, b);
                break;
            case '/':
                if (b == 0) {
                    printf("MATH ERROR\n");
                    continue;
                }
                result = divide(a, b);
                break;
            default:
                printf("SYNTAX ERROR\n");
                continue;
        }

        printf("Result: %.2f\n", result);
    }

    return 0;
}