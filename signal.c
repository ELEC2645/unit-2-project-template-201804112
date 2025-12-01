#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "modules.h"

#define PI 3.14159265358979323846

void run_signal_analyser(void) {
    char save_choice[16];
    
    printf("\n=== Signal Frequency Analyser ===\n");
    double f = get_safe_double("Enter Frequency (Hz): ");
    
    if (f <= 0) {
        printf(">> Error: Frequency must be > 0.\n");
        return;
    }

    double v_pk = get_safe_double("Enter Peak Voltage (V): ");
    
    double period = 1.0 / f;
    double omega = 2 * PI * f;
    double v_rms = v_pk / sqrt(2);

    printf("\n--- Analysis Results ---\n");
    printf("Period (T):        %.6f s\n", period);
    printf("Angular Freq (w):  %.2f rad/s\n", omega);
    printf("RMS Voltage:       %.2f V\n", v_rms);

    get_safe_string("Generate waveform CSV data? (y/n): ", save_choice, sizeof(save_choice));
    if (save_choice[0] == 'y' || save_choice[0] == 'Y') {
        FILE *fp = fopen("waveform.csv", "w");
        if (fp) {
            fprintf(fp, "Time(s),Amplitude(V)\n");
            for (int i = 0; i <= 50; i++) {
                double t = (period / 50.0) * i;
                double amp = v_pk * sin(omega * t);
                fprintf(fp, "%.6f,%.6f\n", t, amp);
            }
            fclose(fp);
            printf(">> Data saved to 'waveform.csv'.\n");
        } else {
            printf(">> Error: Could not open file.\n");
        }
    }
}