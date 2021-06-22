#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>


typedef struct _tComplex
{
    double real;
    double imag;
} tComplex;


void dump(void *pAddr, unsigned int size);
int parse_complex(char *pFileName, tComplex *pBuf, int num);
int store_complex(char *pFileName, tComplex *pBuf, int num);


#endif
