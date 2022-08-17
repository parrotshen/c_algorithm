#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


int main(int argc, char *argv[])
{
    double dB;
    double Gain;

    if (argc != 2)
    {
        printf("Usage: field_gain dB\n\n");
        return 0;
    }

    dB = strtod(argv[1], NULL);
    Gain = pow(10, (dB / 20));

    printf("\n");
    printf("      dB\n");
    printf("10 ^ (%.4f / 20) = %.4f\n", dB, Gain);
    printf("                     Gain\n");
    printf("\n");

    return 0;
}

