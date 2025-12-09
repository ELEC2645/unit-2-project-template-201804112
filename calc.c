#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"   // invoking utils function
#include "modules.h"

#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#define PI 3.14159265358979323846

// Define a minimum value to eliminate floating-point errors
// If the absolute value of the result is less than this number, it is considered to be zero
#define EPSILON 1e-10

static double snap_to_zero(double val) {
    if (fabs(val) < EPSILON) {
        return 0.0;
    }
    return val;
}

static double get_math_value(const char *prompt) {
    char buffer[128];
    char *endptr;
    double value;

    while (1) {
        get_safe_string(prompt, buffer, sizeof(buffer));
        to_lowercase(buffer);

        // 1. Handling individual pi or -pi
        if (strcmp(buffer, "pi") == 0) return PI;
        if (strcmp(buffer, "-pi") == 0) return -PI;

        // 2. Attempt to parse the numerical part
        if (strlen(buffer) == 0) {
        printf(">> Error: No input provided.\n");
        return NAN;
        }

        errno = 0;
        value = strtod(buffer, &endptr);

        while (isspace((unsigned char)*endptr)) endptr++;

        // 3. parse the string part
        if (endptr == buffer) {
            // No numbers were parsed
            printf(">> Error: Invalid input.\n");
        } 
        else if (*endptr == '\0') {
            // Pure digits, no suffix
            return value; 
        } 
        else if (strcmp(endptr, "pi") == 0) {
            //Detected pi suffixes
            return value * PI;
        } 
        else {
            // Unrecognised suffix (e.g. 2abc)
            printf(">> Error: Invalid suffix '%s'.\n", endptr);
            return NAN;
        }
    }
}

void run_scientific_calculator(void) {
    char op[32];
    double a, res;

    int is_radian_mode = 0; 
    char mode_input[16];

    printf("\n=== Scientific Calculator ===\n");

    // Ask the user which mode they are using
    printf("Select Mode -> (d)egrees or (r)adians? [default: r]: ");
    get_safe_string("", mode_input, sizeof(mode_input));
    to_lowercase(mode_input);

    if (mode_input[0] == 'd') {
        is_radian_mode = 0;
        printf(">> Mode set to: DEGREES\n");
    } else {
        is_radian_mode = 1;
        printf(">> Mode set to: RADIANS\n");
    }

    printf("Operations: +, -, *, /, sin, cos, tan, log, ln\n");
    
    
    get_safe_string("Enter operation: ", op, sizeof(op));
    to_lowercase(op);
    
    if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || 
        strcmp(op, "tan") == 0 || strcmp(op, "log") == 0 || strcmp(op, "ln") == 0) {
        
            if (is_radian_mode) {
        printf("Tip: You can enter values like 'pi', '2pi', '0.5pi', '-1.5pi'\n");
        }
        a = get_math_value("Enter value: ");
        
        if (isnan(a)) return;
        // Handling of Trigonometric Functions
        if (strcmp(op, "sin") == 0) {
            double angle = is_radian_mode ? a : (a * PI / 180.0);
            res = sin(angle);
        }
        else if (strcmp(op, "cos") == 0) {
            double angle = is_radian_mode ? a : (a * PI / 180.0);
            res = cos(angle);
        }
        else if (strcmp(op, "tan") == 0) {
            double angle = is_radian_mode ? a : (a * PI / 180.0);
            // Avoid the infinite error in tan(90 degrees)
            if (fabs(cos(angle)) < EPSILON) {
                printf(">> Error: Undefined (tan leads to infinity).\n");
                return;
            }
            res = tan(angle);
        }

        else if (strcmp(op, "log") == 0) res = (a > 0) ? log10(a) : 0;
        else if (strcmp(op, "ln") == 0) res = (a > 0) ? log(a) : 0;
        
        printf(">> Result: %.4f\n", snap_to_zero(res));

    } else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
               strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        
        double x = get_math_value("Enter first number: ");
        double y = get_math_value("Enter second number: ");

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