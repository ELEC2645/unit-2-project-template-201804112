#include <stdio.h>
#include "utils.h"
#include "modules.h"
#include <math.h>
#define PI 3.14159265358979323846

static void print_scaled_frequency(double hz) {
    printf(">> Cut-off Frequency: ");
    
    if (hz >= 1e9) {
        printf("%.3f GHz", hz / 1e9);
    } else if (hz >= 1e6) {
        printf("%.3f MHz", hz / 1e6);
    } else if (hz >= 1e3) {
        printf("%.3f kHz", hz / 1e3);
    } else {
        printf("%.3f Hz", hz);
    }
    
    //original data
    printf(" (%.4f Hz)\n", hz);
}

void run_circuit_analysis(void) {
    printf("\n=== Analog Circuit Analysis ===\n");
    printf("1. Series Resistors\n");
    printf("2. Parallel Resistors\n");
    printf("3. RC Time Constant\n");
    printf("4. RC Cut-off Frequency (fc)\n"); // new function
    double choice = get_safe_double("Select Mode (1-4): ");

    if (choice == 1.0) {
        double r1 = get_safe_double("R1 (Ohms): ");
        if (r1 <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }
        double r2 = get_safe_double("R2 (Ohms): ");
        if (r2 <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }

        printf(">> Total Series R: %.2f Ohms\n", r1 + r2);
    } 
    else if (choice == 2.0) {
        double r1 = get_safe_double("R1 (Ohms): ");
        if (r1 <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }
        double r2 = get_safe_double("R2 (Ohms): ");
        if (r2 <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }
        
        printf(">> Total Parallel R: %.2f Ohms\n", (r1 * r2) / (r1 + r2));
    } 
    else if (choice == 3.0) {
        double r = get_safe_double("Resistance (Ohms): ");
        if (r <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }
        double c = get_safe_double("Capacitance (Farads): ");
        if (c <= 0) { printf(">> Error: Capacitance must be positive.\n"); return; }
        
        printf(">> Time Constant (Tau): %.6f s\n", r * c);
    } 
    else if (choice == 4.0) {
        printf("--- Calculate Cut-off Frequency ---\n");
        double r = get_safe_double("Resistance (Ohms): ");
        if (r <= 0) { printf(">> Error: Resistance must be positive.\n"); return; }
        double c = get_safe_double("Capacitance (Farads): ");
        if (c <= 0) { printf(">> Error: Capacitance must be positive.\n"); return; }
        
        double fc = 1.0 / (2.0 * PI * r * c);
        print_scaled_frequency(fc);
    } 
    else {
        printf(">> Invalid selection.\n");
    }
}