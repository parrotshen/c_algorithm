#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>


#define COMPLEX_ADD(ina, inb, outc) \
{ \
    outc.real = (ina.real + inb.real); \
    outc.imag = (ina.imag + inb.imag); \
}

#define COMPLEX_SUB(ina, inb, outc) \
{ \
    outc.real = (ina.real - inb.real); \
    outc.imag = (ina.imag - inb.imag); \
}

#define COMPLEX_MUL(ina, inb, outc) \
{ \
    double real, imag; \
    real = ((ina.real * inb.real) - (ina.imag * inb.imag)); \
    imag = ((ina.imag * inb.real) + (ina.real * inb.imag)); \
    outc.real = real; \
    outc.imag = imag; \
}

#define COMPLEX_DIV(ina, inb, outc) \
{ \
    double real, imag; \
    double temp = ((inb.real * inb.real) + (inb.imag * inb.imag)); \
    real = ((ina.real * inb.real) + (ina.imag * inb.imag)) / temp; \
    imag = ((ina.imag * inb.real) - (ina.real * inb.imag)) / temp; \
    outc.real = real; \
    outc.imag = imag; \
}

#define COMPLEX_ABS( in ) \
    sqrt(pow(in.real, 2) + pow(in.imag, 2))

#define COMPLEX_ANGLE( in ) \
    (((in.imag != 0) || (in.real != 0)) ? atan2(in.imag, in.real) : 0)


typedef struct _tComplex
{
    double real;
    double imag;
} tComplex;


void dump(void *pAddr, unsigned int size);
int count_lines(char *pFileName);
int parse_complex(char *pFileName, tComplex *pBuf, int num);
int store_complex(char *pFileName, tComplex *pBuf, int num);
void print_complex(char *pStr, tComplex *pBuf, int num);


#endif
