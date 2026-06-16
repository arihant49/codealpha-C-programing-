#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
     char operator;
    double num1;
    double num2;
    double result;

    printf("\nEnter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    printf("Enter number 1: ");
    scanf("%lf", &num1);

    printf("Enter number 2: ");
    scanf("%lf", &num2);

    switch(operator) {
        case '+':
            result = num1 + num2;
            printf("\nResult: %.2lf\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("\nResult: %.2lf\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("\nResult: %.2lf\n", result); 
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("\nResult: %.2lf\n", result);
            } else {
                printf("\nError: Division by zero is not allowed.\n");
                return 1;
            }
            break;
        default:
            printf("\nError: Invalid operator.\n");
            return 1;
    }

    printf("\nResult: %.2lf\n", result);
    return 0;
}