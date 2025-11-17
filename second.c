#include <stdio.h>
#include <stdlib.h>

int main() {
    char operator;
    double num1, num2, result;
    int choice;

    do {
        printf("\n*** Simple C Calculator ***\n");
        printf("Available Operations:\n");
        printf("  1. Addition (+)\n");
        printf("  2. Subtraction (-)\n");
        printf("  3. Multiplication (*)\n");
        printf("  4. Division (/)\n");
        printf("  5. Exit\n");
        printf("---------------------------\n");
        
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("\nError: Invalid input for choice. Exiting.\n");
            while (getchar() != '\n'); 
            return 1;
        }

        if (choice == 5) {
            printf("\nExiting Calculator. Goodbye!\n");
            break;
        }
        
        switch (choice) {
            case 1: operator = '+'; break;
            case 2: operator = '-'; break;
            case 3: operator = '*'; break;
            case 4: operator = '/'; break;
            default:
                printf("\nError: Invalid choice. Please enter a number between 1 and 5.\n");
                continue;
        }
        
        printf("Enter first number: ");
        if (scanf("%lf", &num1) != 1) {
            printf("\nError: Invalid input for the first number. Exiting.\n");
            while (getchar() != '\n');
            return 1;
        }

        printf("Enter second number: ");
        if (scanf("%lf", &num2) != 1) {
            printf("\nError: Invalid input for the second number. Exiting.\n");
            while (getchar() != '\n');
            return 1;
        }

        switch (operator) {
            case '+':
                result = num1 + num2;
                printf("\nResult: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
                break;
                
            case '-':
                result = num1 - num2;
                printf("\nResult: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
                break;
                
            case '*':
                result = num1 * num2;
                printf("\nResult: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
                break;
                
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("\nResult: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
                } else {
                    printf("\nError: Division by zero is not allowed.\n");
                }
                break;
                
            default:
                printf("\nError: Something went wrong with the operation.\n");
                break;
        }
        
        while (getchar() != '\n'); 

    } while (choice != 5);

    return 0;
}