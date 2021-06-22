#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utility.h"


/*
* DFT:
*          N-1
*   X[k] = SUM( x[n] * e^(-j * 2* pi *n * k / N) )
*          n=0
*     k = 0, 1, 2 ... N-1
*/


void dit_fft(tComplex *pData, int size)
{
    tComplex swap;
    double C;
    double S;
    double W[2];
    double tempR;
    double tempI;
    int N;
    int n;
    int i;
    int j;
    int k;


    /* bit-reverse */
    j = 0;
    N = (size >> 1);
    for (i=1; i<(size-1); i++)
    {
        n = N;
        while (j >= n)
        {
            j -= n;
            n >>= 1;
        }
        j += n;

        if (i < j)
        {
            swap = pData[i];
            pData[i] = pData[j];
            pData[j] = swap;
        }
    }


    /* N/2-point DFT */
    n = 0;
    N = 1;
    for (i=0; i<(int)log2(size); i++)
    {
        n = N;
        N <<= 1;
        W[0] = (-6.283185307179586 / N);
        W[1] = 0.0;

        for (j=0; j<n; j++)
        {
            C = cos( W[1] );
            S = sin( W[1] );
            W[1] += W[0];

            for (k=j; k<size; k+=N)
            {
                tempR = (C * pData[k+n].real) - (S * pData[k+n].imag);
                tempI = (S * pData[k+n].real) + (C * pData[k+n].imag);
                pData[k+n].real = pData[k].real - tempR;
                pData[k+n].imag = pData[k].imag - tempI;
                pData[k  ].real = pData[k].real + tempR;
                pData[k  ].imag = pData[k].imag + tempI;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    char *pIn = NULL;
    char *pOut = NULL;
    int size = 0;

    tComplex *pBuf = NULL;
    int retval;


    if (argc != 4)
    {
        printf("Usage: dft T_INPUT.txt F_OUTPUT.txt N_POINT\n\n");
        return 0;
    }

    pIn  = argv[1];
    pOut = argv[2];
    size = atoi( argv[3] );

    pBuf = malloc(size * sizeof( tComplex ));
    if ( pBuf )
    {
        retval = parse_complex(pIn, pBuf, size);
        if (retval != size)
        {
            printf("ERR: incorrect number of input data (%d)\n\n", retval);
            goto _EXIT_DFT;
        }

        /* Radix-2 Decimation-In-Time FFT */
        dit_fft(pBuf, size);

        store_complex(pOut, pBuf, size);
    }


_EXIT_DFT:
    if ( pBuf ) free( pBuf );
    return 0;
}

