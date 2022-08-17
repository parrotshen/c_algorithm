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

