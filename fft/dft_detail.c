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
void dft_detail(tComplex x[], tComplex X[], int N)
{
    tComplex temp;
    tComplex W;
    int half;
    int freq;
    int n;
    int k;

    /*
    * W[k,n] = e^(-j*2*pi*k*n/N)
    *        = cos(2*pi*k*n/N) - j*sin(2*pi*k*n/N)
    */
    half = ((N & 0x1) ? N/2 : N/2-1);
    for (k=0; k<N; k++)
    {
        freq = ((k > half) ? (k-N) : k);
        printf("[1;33m%dHz[0m\n", freq);
        X[k].real = 0;
        X[k].imag = 0;
        for (n=0; n<N; n++)
        {
            W.real =  cos(2*M_PI*k*n/N);
            W.imag = -sin(2*M_PI*k*n/N);
            COMPLEX_MUL(x[n], W, temp);
            printf("X[%d] =%+10f, x[%d] * cos(2*pi*%d*%d/%d) = %+f\n",
                k,
                X[k].real,
                n,
                k,
                n,
                N,
                temp.real
            );
            COMPLEX_ADD(X[k], temp, X[k]);
        }
        printf("X[%d] =[1;33m%+10f[0m\n", k, X[k].real);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    tComplex x[32];
    tComplex X[32];
    double f = 1;
    int N = 8;
    int half;
    int n;
    int k;

    if (argc > 1)
    {
        N = atoi( argv[1] );
        if (N < 8) N = 8;
        if (N > 32) N = 32;
    }
    if (argc > 2)
    {
        half = (N & 0x1) ? (N/2): (N/2-1);
        f = atoi( argv[2] );
        if (f < 1) f = 1;
        if (f > half) f = half;
    }

    for (n=0; n<N; n++)
    {
        x[n].real = cos(2*M_PI*f*n/N);
        x[n].imag = 0;
    }

    dft_detail(x, X, N);

    printf("x[n]:\n");
    for (n=0; n<N; n++)
    {
        printf("%+10f %+10f\n", x[n].real, x[n].imag);
    }
    printf("\n");

    printf("X[k]:\n");
    for (k=0; k<N; k++)
    {
        if ((k == f) || (k == (N-f)))
        {
            printf("[1;36m%+10f %+10fi[0m\n", X[k].real, X[k].imag);
        }
        else
        {
            printf("%+10f %+10fi\n", X[k].real, X[k].imag);
        }
    }
    printf("\n");

    return 0;
}

