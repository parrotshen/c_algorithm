#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utility.h"


/*
* Even: 
*      1 2 3 4 5 6
*  ==> 4 5 6 1 2 3
*           ^
*           N = 6, N/2 = 3
*
* Odd:
*      1 2 3 4 5 6 7
*  ==> 5 6 7 1 2 3 4
*            ^
*            N = 7, N/2 = 3
*/
void fft_shift(tComplex *pIn, tComplex *pOut, int N)
{
    int seq1, seq2;
    int n;
    int i;

    seq1 = (N / 2);
    seq2 = (seq1 + (N & 0x1));
    for (n=0; n<N; n++)
    {
        i = (n < seq1) ? (seq2 + n) : (n - seq1);
        pOut[n].real = pIn[i].real;
        pOut[n].imag = pIn[i].imag;
    }
}


int main(int argc, char *argv[])
{
    tComplex *pBuf1 = NULL;
    tComplex *pBuf2 = NULL;
    char *pFile1;
    char *pFile2;
    int size;


    if (argc != 3)
    {
        printf("Usage: fft_shift F_INPUT.txt F_OUTPUT.txt\n\n");
        return 0;
    }

    pFile1 = argv[1];
    pFile2 = argv[2];

    size = count_lines( pFile1 );
    if (size > 0)
    {
        pBuf1 = malloc(size * sizeof( tComplex ));
        pBuf2 = malloc(size * sizeof( tComplex ));
        if ( pBuf1 && pBuf2 )
        {
            parse_complex(pFile1, pBuf1, size);

            fft_shift(pBuf1, pBuf2, size);
            print_complex("FFT shift:", pBuf2, size);

            store_complex(pFile2, pBuf2, size);
        }
    }

    if ( pBuf1 ) free( pBuf1 );
    if ( pBuf2 ) free( pBuf2 );
    return 0;
}
