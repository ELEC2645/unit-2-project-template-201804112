#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "modules.h"

// only used in this module
static int get_color_val(char *color) {
    const char *colors[] = {"black", "brown", "red", "orange", "yellow", 
                            "green", "blue", "violet", "grey", "white"};
    to_lowercase(color);
    for (int i = 0; i < 10; i++) {
        if (strcmp(color, colors[i]) == 0) return i;
    }
    return -1;
}

void run_resistor_decoder(void) {
    char c1[32], c2[32], c3[32];
    
    printf("\n=== Resistor Color Decoder ===\n");
    printf("Colors: Black, Brown, Red, Orange, Yellow, Green, Blue, Violet, Grey, White\n");
    
    get_safe_string("Band 1 Color: ", c1, sizeof(c1));
    get_safe_string("Band 2 Color: ", c2, sizeof(c2));
    get_safe_string("Band 3 Color (Multiplier): ", c3, sizeof(c3));

    int v1 = get_color_val(c1);
    int v2 = get_color_val(c2);
    int v3 = get_color_val(c3);

    if (v1 != -1 && v2 != -1 && v3 != -1) {
        double resistance = (v1 * 10 + v2) * pow(10, v3);
        
        printf("\n>> Result: ");
        if (resistance >= 1e6) printf("%.2f M Ohms\n", resistance / 1e6);
        else if (resistance >= 1e3) printf("%.2f k Ohms\n", resistance / 1e3);
        else printf("%.2f Ohms\n", resistance);
    } else {
        printf(">> Error: Invalid color entered.\n");
    }
}