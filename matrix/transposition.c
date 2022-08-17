#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"

#define MATRIX_TR(A, row, col, B) \
    { \
        int m, n; \
        for (n=0; n<col; n++) \
        { \
            for (m=0; m<row; m++) \
            { \
                B[n][m] = A[m][n]; \
            } \
        } \
    }

int main(int argc, char *argv[])
{
    int A[2][3] = {
        {  1,  2,  3 },
        {  0, -6,  7 }
    };
    int B[3][2];

    #if (USING_MACRO)
    MATRIX_TR(A, 2, 3, B);
    #else
    transposeMatrix(A, 2, 3, B);
    #endif

    printMatrix(A, 2, 3);
    printf("T =\n");
    printMatrix(B, 3, 2);

    return 0;
}

