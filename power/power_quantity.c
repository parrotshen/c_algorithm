#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


int main(int argc, char *argv[])
{
    double P;
    double Pref;
    double Gain;
    double dB;

    if (argc != 3)
    {
        printf("Usage: power_quantity P Pref\n\n");
        return 0;
    }

    P = strtod(argv[1], NULL);
    Pref = strtod(argv[2], NULL);
    Gain = P / Pref;
    dB = 10 * log10( Gain );

    printf("\n");
    printf("%.4f / %.4f = %.4f\n", P, Pref, Gain);
    printf("10 * log10( %.4f ) = %.4f dB\n", Gain, dB);
    printf("            Gain\n");
    printf("\n");

    return 0;
}

