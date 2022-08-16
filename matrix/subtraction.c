#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define MATRIX_SUB(A, B, row, col, C) \
    { \
        int m, n; \
        for (m=0; m<row; m++) \
        { \
            for (n=0; n<col; n++) \
            { \
                C[m][n] = A[m][n] - B[m][n]; \
            } \
        } \
    }

int main(int argc, char *argv[])
{
    int A[2][3] = {
        { 1, 3, 1 },
        { 1, 0, 0 }
    };
    int B[2][3] = {
        { 0, 0, 5 },
        { 7, 5, 0 }
    };
    int C[2][3];

    #if (USING_MACRO)
    MATRIX_SUB(A, B, 2, 3, C);
    #else
    subtractMatrix(A, B, 2, 3, C);
    #endif

    printMatrix(A, 2, 3);
    printf("-\n");
    printMatrix(B, 2, 3);
    printf("=\n");
    printMatrix(C, 2, 3);

    return 0;
}

