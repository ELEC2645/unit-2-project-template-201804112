#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"   // invoking utils function
#include "modules.h"

#define PI 3.14159265358979323846

void run_scientific_calculator(void) {
    char op[32];
    double a, res;

    printf("\n=== Scientific Calculator ===\n");
    printf("Operations: +, -, *, /, sin, cos, tan, log, ln\n");
    
    get_safe_string("Enter operation: ", op, sizeof(op));
    to_lowercase(op);
    
    if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || 
        strcmp(op, "tan") == 0 || strcmp(op, "log") == 0 || strcmp(op, "ln") == 0) {
        
        a = get_safe_double("Enter value: ");

        if (strcmp(op, "sin") == 0) res = sin(a * PI / 180.0);
        else if (strcmp(op, "cos") == 0) res = cos(a * PI / 180.0);
        else if (strcmp(op, "tan") == 0) res = tan(a * PI / 180.0);
        else if (strcmp(op, "log") == 0) res = (a > 0) ? log10(a) : 0;
        else if (strcmp(op, "ln") == 0) res = (a > 0) ? log(a) : 0;
        
        printf(">> Result: %.4f\n", res);

    } else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
               strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        
        double x = get_safe_double("Enter first number: ");
        double y = get_safe_double("Enter second number: ");

        if (strcmp(op, "+") == 0) printf(">> Result: %.4f\n", x + y);
        else if (strcmp(op, "-") == 0) printf(">> Result: %.4f\n", x - y);
        else if (strcmp(op, "*") == 0) printf(">> Result: %.4f\n", x * y);
        else if (strcmp(op, "/") == 0) {
            if (y != 0) printf(">> Result: %.4f\n", x / y);
            else printf(">> Error: Division by zero!\n");
        }
    } else {
        printf(">> Invalid Operation.\n");
    }
}