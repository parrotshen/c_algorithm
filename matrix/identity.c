#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define MATRIX_I(A, row, col) \
    int A[row][col]; \
    { \
        int m, n; \
        for (m=0; m<row; m++) \
        { \
            for (n=0; n<col; n++) \
            { \
                A[m][n] = (m == n); \
            } \
        } \
    }

int main(int argc, char *argv[])
{
    MATRIX_I(I, 4, 4);
    int A[4][4] = {
        {  1,  2,  3,  4 },
        {  5,  6,  7,  8 },
        {  9, 10, 11, 12 },
        { 13, 14, 15, 16 }
    };
    int B[4][4];

    multiplyMatrix(A, 4, 4, I, 4, 4, B);

    printMatrix(A, 4, 4);
    printf("x\n");
    printMatrix(I, 4, 4);
    printf("=\n");
    printMatrix(B, 4, 4);

    return 0;
}

