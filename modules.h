#ifndef MODULES_H
#define MODULES_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h> // Required for accurate error checking

#define PI 3.14159265358979323846

// --- SAFE INPUT HELPERS (Implemented in input_utils.c) ---
// These replace scanf entirely
void get_safe_string(const char *prompt, char *buffer, int size);
double get_safe_double(const char *prompt);
int get_safe_int(const char *prompt);

// --- Module Functions ---
void scientificCalculator();
void signalAnalyser();
void resistorDecoder();
void sensorConverter();
void circuitAnalysis();

#endif