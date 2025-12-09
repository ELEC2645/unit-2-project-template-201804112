#include <stdio.h>
#include "utils.h"
#include "modules.h"

void run_sensor_converter(void) {
    printf("\n=== Sensor Unit Converter ===\n");
    
    double minV = get_safe_double("Sensor Min Voltage (e.g. 0): ");
    double maxV = get_safe_double("Sensor Max Voltage (e.g. 5): ");
    
    if (maxV - minV == 0) {
        printf(">> Error: Voltage range cannot be zero.\n");
        return;
    }

    double minP = get_safe_double("Physical Min Value (e.g. -50): ");
    double maxP = get_safe_double("Physical Max Value (e.g. 150): ");
    double measureV = get_safe_double("Enter Measured Voltage: ");

    double m = (maxP - minP) / (maxV - minV);
    double result = (measureV - minV) * m + minP;
    
    printf(">> Calculated Physical Value: %.4f\n", result);
}