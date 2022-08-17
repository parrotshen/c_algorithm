#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


int main(int argc, char *argv[])
{
    double F;
    double Fref;
    double Gain;
    double dB;

    if (argc != 3)
    {
        printf("Usage: field_quantity F Fref\n\n");
        return 0;
    }

    F = strtod(argv[1], NULL);
    Fref = strtod(argv[2], NULL);
    Gain = F / Fref;
    dB = 20 * log10( Gain );

    printf("\n");
    printf("%.4f / %.4f = %.4f\n", F, Fref, Gain);
    printf("20 * log10( %.4f ) = %.4f dB\n", Gain, dB);
    printf("            Gain\n");
    printf("\n");

    return 0;
}

