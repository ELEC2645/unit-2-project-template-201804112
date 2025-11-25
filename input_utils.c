#include "modules.h"

// --- Helper: Clean newline from fgets ---
static void strip_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// 1. Get a clean string (Safe replacement for scanf("%s"))
void get_safe_string(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        strip_newline(buffer);
    } else {
        // Handle EOF or error
        buffer[0] = '\0';
    }
}

// 2. Get a Double safely (Safe replacement for scanf("%lf"))
double get_safe_double(const char *prompt) {
    char buffer[100];
    char *endptr;
    double value;
    
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) return 0.0; // Handle EOF

        strip_newline(buffer);

        // Check for empty input
        if (strlen(buffer) == 0) continue;

        errno = 0;
        value = strtod(buffer, &endptr);

        // Logic from your guide:
        // 1. endptr == buffer: No number found (e.g. "abc")
        // 2. *endptr != '\0': Extra garbage found (e.g. "12abc")
        // 3. errno == ERANGE: Number too big/small
        if (endptr == buffer || *endptr != '\0' || errno == ERANGE) {
            printf("Error: Invalid number. Please try again.\n");
        } else {
            return value; // Valid number
        }
    }
}

// 3. Get an Integer safely (Safe replacement for scanf("%d"))
int get_safe_int(const char *prompt) {
    char buffer[100];
    char *endptr;
    long value;
    
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) return 0;

        strip_newline(buffer);
        if (strlen(buffer) == 0) continue;

        errno = 0;
        value = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || errno == ERANGE) {
            printf("Error: Invalid integer. Please try again.\n");
        } else {
            return (int)value;
        }
    }
}