#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define MATRIX_MUL(A, rowa, cola, B, rowb, colb, C) \
    { \
        int m, n, l; \
        for (m=0; m<rowa; m++) \
        { \
            for (n=0; n<colb; n++) \
            { \
                C[m][n] = 0; \
                for (l=0; l<cola; l++) \
                { \
                    C[m][n] += A[m][l] * B[l][n]; \
                } \
            } \
        } \
    }

int main(int argc, char *argv[])
{
    int A[2][3] = {
        {  1,  0,  2 },
        { -1,  3,  1 }
    };
    int B[3][2] = {
        {  3,  1 },
        {  2,  1 },
        {  1,  0 }
    };
    int C[2][2];

    #if (USING_MACRO)
    MATRIX_MUL(A, 2, 3, B, 3, 2, C);
    #else
    multiplyMatrix(A, 2, 3, B, 3, 2, C);
    #endif

    printMatrix(A, 2, 3);
    printf("x\n");
    printMatrix(B, 3, 2);
    printf("=\n");
    printMatrix(C, 2, 2);

    return 0;
}

