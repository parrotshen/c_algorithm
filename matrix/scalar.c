#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"

#define MATRIX_SCALAR(A, row, col, val, B) \
    { \
        int m, n; \
        for (m=0; m<row; m++) \
        { \
            for (n=0; n<col; n++) \
            { \
                B[m][n] = val * A[m][n]; \
            } \
        } \
    }

int main(int argc, char *argv[])
{
    int A[2][3] = {
        {  1,  8, -3 },
        {  4, -2,  5 }
    };
    int alpha = 2;
    int B[2][3];

    #if (USING_MACRO)
    MATRIX_SCALAR(A, 2, 3, alpha, B);
    #else
    scalarMatrix(A, 2, 3, alpha, B);
    #endif

    printf("%d *\n", alpha);
    printMatrix(A, 2, 3);
    printf("=\n");
    printMatrix(B, 2, 3);

    return 0;
}

