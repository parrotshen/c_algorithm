#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


void printMatrix(void *matrix, int row, int col)
{
    int *val = matrix;
    int i = 0;
    int m;
    int n;

    for (m=0; m<row; m++)
    {
        for (n=0; n<col; n++)
        {
            printf(" %d", val[i++]);
        }
        printf("\n");
    }
}

void addMatrix(void *ina, void *inb, int row, int col, void *outc)
{
    int *A = ina;
    int *B = inb;
    int *C = outc;
    int i = 0;
    int m;
    int n;

    for (m=0; m<row; m++)
    {
        for (n=0; n<col; n++)
        {
            C[i] = A[i] + B[i];
            i++;
        }
    }
}

void subtractMatrix(void *ina, void *inb, int row, int col, void *outc)
{
    int *A = ina;
    int *B = inb;
    int *C = outc;
    int i = 0;
    int m;
    int n;

    for (m=0; m<row; m++)
    {
        for (n=0; n<col; n++)
        {
            C[i] = A[i] - B[i];
            i++;
        }
    }
}

void multiplyMatrix(
    void *ina,
    int   rowa,
    int   cola,
    void *inb,
    int   rowb,
    int   colb,
    void *outc
)
{
    int *A = ina;
    int *B = inb;
    int *C = outc;
    int i = 0;
    int m;
    int n;
    int l;

    if (cola != rowb)
    {
        printf("ERR: A(col %d) not equal to B(row %d)\n", cola, rowb);
        return;
    }

    for (m=0; m<rowa; m++)
    {
        for (n=0; n<colb; n++)
        {
            C[i] = 0;
            for (l=0; l<cola; l++)
            {
                C[i] += A[(m * cola) + l] * B[(l * colb) + n];
            }
            i++;
        }
    }
}

void scalarMatrix(void *in, int row, int col, int val, void *out)
{
    int *A = in;
    int *B = out;
    int i = 0;
    int m;
    int n;

    for (m=0; m<row; m++)
    {
        for (n=0; n<col; n++)
        {
            B[i] = val * A[i];
            i++;
        }
    }
}

void transposeMatrix(void *in, int row, int col, void *out)
{
    int *A = in;
    int *B = out;
    int i = 0;
    int m;
    int n;

    for (n=0; n<col; n++)
    {
        for (m=0; m<row; m++)
        {
            B[i] = A[(m * col) + n];
            i++;
        }
    }
}

int determinMatrix(void *in, int row, int col)
{
    int *A = in;
    int det = 0;

    if (row != col)
    {
        printf("ERR: (%d x %d) is not a square matrix\n", row, col);
        return 0;
    }

    switch ( row )
    {
        case 1:
            /* | 0 | */
            det = A[0];
            break;
        case 2:
            /*
            * | 0  1 |
            * | 2  3 |
            */
            det = ((A[0]*A[3]) - (A[1]*A[2]));
            break;
        case 3:
            /*
            * | 0  1  2 |
            * | 3  4  5 |
            * | 6  7  8 |
            */
            det
             = ((A[0]*A[4]*A[8]) + (A[1]*A[5]*A[6]) + (A[2]*A[3]*A[7])) -
               ((A[2]*A[4]*A[6]) + (A[0]*A[5]*A[7]) + (A[1]*A[3]*A[8]));
            break;
        case 4:
            /*
            * |  0  1  2  3 |
            * |  4  5  6  7 |
            * |  8  9 10 11 |
            * | 12 13 14 15 |
            */
            det
             = A[0]*((A[5]*A[10]*A[15] + A[6]*A[11]*A[13] + A[7]*A[9]*A[14]) -
                     (A[7]*A[10]*A[13] + A[5]*A[11]*A[14] + A[6]*A[9]*A[15])) -
               A[1]*((A[4]*A[10]*A[15] + A[6]*A[11]*A[12] + A[7]*A[8]*A[14]) -
                     (A[7]*A[10]*A[12] + A[4]*A[11]*A[14] + A[6]*A[8]*A[15])) +
               A[2]*((A[4]*A[ 9]*A[15] + A[5]*A[11]*A[12] + A[7]*A[8]*A[13]) -
                     (A[7]*A[ 9]*A[12] + A[4]*A[11]*A[13] + A[5]*A[8]*A[15])) -
               A[3]*((A[4]*A[ 9]*A[14] + A[5]*A[10]*A[12] + A[6]*A[8]*A[13]) -
                     (A[6]*A[ 9]*A[12] + A[4]*A[10]*A[13] + A[5]*A[8]*A[14]));
            break;
        default:
            printf("ERR: (%d x %d) is unavailable\n", row, col);
            break;
    }

    return det;
}

