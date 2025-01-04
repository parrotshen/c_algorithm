#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utility.h"


/*
* DFT:
*          N-1
*   X[k] = SUM{ x[n] * e^(-j*2*pi*k*n/N) }
*          n=0
*     k = 0, 1, 2 ... N-1
*/

void dit_detail(double x[], tComplex X[], int N)
{
    tComplex W;
    int n;
    int k;

/* e^(-j*2*pi*f0*t) = cos(2*pi*f0*t) - j*sin(2*pi*f0*t) */
    for (k=0; k<N; k++)
    {
        X[k].real = 0;
        X[k].imag = 0;
        for (n=0; n<N; n++)
        {
            W.real =  cos(2*M_PI*k*n/N);
            W.imag = -sin(2*M_PI*k*n/N);
            if ((n != 0) && ((n % 10) == 0)) printf("\n");
            //printf("%+f ", W.real);
            printf("%+f ", (x[n] * W.real));
            X[k].real += (x[n] * W.real);
            X[k].imag += (x[n] * W.imag);
        }
        printf("\n");
        //X[k].real /= N;
        //X[k].imag /= N;
        printf("[1;33m%+f[0m\n", X[k].real);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
#define POINTS 20
    tComplex X[POINTS];
    double x[POINTS];
    double f = 3;
    int N = POINTS;
    int n;
    int k;


    for (n=0; n<N; n++)
    {
        x[n] = cos(2*M_PI*f*n/N);
        #if 0
        printf("%d %+f\n", n, x[n]);
        #endif
    }

    dit_detail(x, X, N);

    #if 1
    printf("x[n]:\n");
    for (n=0; n<N; n++)
    {
        printf("%+f\n", x[n]);
    }
    printf("\n");
    printf("X[k]:\n");
    for (k=0; k<N; k++)
    {
        printf("%+f %+fi\n", X[k].real, X[k].imag);
    }
    printf("\n");
    #endif

    return 0;
}

