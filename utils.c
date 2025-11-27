#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utils.h"

void strip_newline(char *str) {
    str[strcspn(str, "\r\n")] = 0;
}

void get_safe_string(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        strip_newline(buffer);
    } else {
        buffer[0] = '\0';
    }
}

double get_safe_double(const char *prompt) {
    char buffer[128];
    char *endptr;
    double value;
    
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) return 0.0;
        
        strip_newline(buffer);
        if (strlen(buffer) == 0) continue;

        errno = 0;
        value = strtod(buffer, &endptr);

        if (endptr == buffer || *endptr != '\0' || errno == ERANGE) {
            printf(">> Error: Invalid number. Please enter a valid decimal.\n");
        } else {
            return value;
        }
    }
}

void to_lowercase(char *str) {
    for(int i = 0; str[i]; i++) str[i] = tolower(str[i]);
}