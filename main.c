#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "modules.h"

static void main_menu(void);
static void print_main_menu(void);
static int  get_user_input(void);
static void select_menu_item(int input);
static void go_back_to_main(void);
static int  is_integer(const char *s);

int main(void) {
    for(;;) {
        main_menu();
    }
    return 0;
}

static void main_menu(void) {
    print_main_menu();
    int input = get_user_input();
    select_menu_item(input);
}

static int get_user_input(void) {
    enum { MENU_ITEMS = 6 };   
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
            }
        }
    } while (!valid_input);

    return value;
}

static void select_menu_item(int input) {
    switch (input) {
        case 1: run_scientific_calculator(); go_back_to_main(); break;
        case 2: run_signal_analyser(); go_back_to_main(); break;
        case 3: run_resistor_decoder(); go_back_to_main(); break;
        case 4: run_sensor_converter(); go_back_to_main(); break;
        case 5: run_circuit_analysis(); go_back_to_main(); break;
        case 6: printf("Bye!\n"); exit(0);
        default: break;
    }
}

static void print_main_menu(void) {
    printf("\n=============================================\n");
    printf("      INTEGRATED ELECTRONICS WORKBENCH       \n");
    printf("=============================================\n");
    printf("\t1. Scientific Calculator\n");
    printf("\t2. Signal Frequency Analyser\n");
    printf("\t3. Resistor Color Decoder\n");
    printf("\t4. Sensor Converter\n");
    printf("\t5. Analog Circuit Analysis\n");
    printf("\t6. Exit\n");
    printf("---------------------------------------------\n");
}

static void go_back_to_main(void) {
    char buf[64];
    do {
        printf("\nEnter 'b' or 'B' to go back: ");
        if (!fgets(buf, sizeof(buf), stdin)) exit(1);
        buf[strcspn(buf, "\r\n")] = '\0';
    } while (!(buf[0] == 'b' || buf[0] == 'B'));
}

static int is_integer(const char *s) {
    if (!s || !*s) return 0;
    if (*s == '+' || *s == '-') s++;
    if (!isdigit((unsigned char)*s)) return 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}