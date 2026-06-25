#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utility.h"


#define PRINT_1 0
#define PRINT_2 1
#define PRINT_3 0


/*
* DFT:
*          N-1
*   X[k] = SUM{ x[n] * e^(-j*2*pi*k*n/N) }
*          n=0
*     k = 0, 1, 2 ... N-1
*/
void dft_detail(double x[], tComplex X[], int N)
{
    tComplex W;
    int n;
    int k;

    /*
    * W[k,n] = e^(-j*2*pi*k*n/N)
    *        = cos(2*pi*k*n/N) - j*sin(2*pi*k*n/N)
    */
    for (k=0; k<N; k++)
    {
        X[k].real = 0;
        X[k].imag = 0;
        n = 0;
        {
            W.real =  cos(2*M_PI*k*n/N);
            W.imag = -sin(2*M_PI*k*n/N);
            #if (PRINT_1)
            printf("%+f\n", W.real);
            #endif
            #if (PRINT_2)
            printf("%+f\n", (x[n] * W.real));
            #endif
            X[k].real += (x[n] * W.real);
            X[k].imag += (x[n] * W.imag);
            #if (PRINT_3)
            printf("%+f\n", X[k].real);
            #endif
        }
        for (n=1; n<N; n++)
        {
            W.real =  cos(2*M_PI*k*n/N);
            W.imag = -sin(2*M_PI*k*n/N);
            if ((n != 1) && ((n % 11) == 0)) printf("\n");
            #if (PRINT_1)
            printf("%+f ", W.real);
            #endif
            #if (PRINT_2)
            printf("%+f ", (x[n] * W.real));
            #endif
            X[k].real += (x[n] * W.real);
            X[k].imag += (x[n] * W.imag);
            #if (PRINT_3)
            printf("%+f ", X[k].real);
            #endif
        }
        printf("\n");
        //X[k].real /= N;
        //X[k].imag /= N;
        printf("[1;33m%2d %+f[0m\n", k, X[k].real);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
#define POINTS 21
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

    dft_detail(x, X, N);

    #if 1
    printf("x[n]:\n");
    for (n=0; n<N; n++)
    {
        printf("%+10.6f\n", x[n]);
    }
    printf("\n");
    printf("X[k]:\n");
    for (k=0; k<N; k++)
    {
        printf("%+10.6f %+10.6fi\n", X[k].real, X[k].imag);
    }
    printf("\n");
    #endif

    return 0;
}

