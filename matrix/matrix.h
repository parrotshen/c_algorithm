#ifndef __MATRIX_H__
#define __MATRIX_H__


void printMatrix(void *data, int row, int col);

void addMatrix(void *ina, void *inb, int row, int col, void *outc);

void subtractMatrix(void *ina, void *inb, int row, int col, void *outc);

void multiplyMatrix(
    void *ina,
    int   rowa,
    int   cola,
    void *inb,
    int   rowb,
    int   colb,
    void *outc
);

void scalarMatrix(void *in, int row, int col, int val, void *out);

void transposeMatrix(void *in, int row, int col, void *out);


#endif
