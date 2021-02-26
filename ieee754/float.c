#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * Convert 32-bit integer to string in binary format
 * @param [in]  value    Integer value.
 * @param [in]  pBuf     String buffer.
 * @param [in]  bufSize  String buffer size.
 * @returns  Number of bits.
 */
int int2bin(int value, char *pBuf, int bufSize)
{
    unsigned char bits[32];
    int len = 0;
    int i;


    memset(pBuf, 0, bufSize);

    if (0 == value)
    {
        pBuf[0] = '0';
        return 1;
    }

    while ( value )
    {
        bits[len++] = (value & 0x1);
        value >>= 1;
    }

    if (len > bufSize)
    {
        printf("ERR: un-enough buffer size (%d < %d)\n", bufSize, len);
        return 0;
    }

    for (i=len; i>0; i--)
    {
        *pBuf = (bits[i - 1] ? '1' : '0');
        pBuf++;
    }

    return len;
}

/**
 * Convert 32-bit floating-point to string in binary format
 * @param [in]  value    Floating-point value.
 * @param [in]  pBuf     String buffer.
 * @param [in]  bufSize  String buffer size.
 * @returns  Number of bits.
 */
int float2bin(float value, char *pBuf, int bufSize)
{
    unsigned char bits[32];
    int len = 0;
    int digit;
    int i;


    memset(pBuf, 0, bufSize);

    if (0.0 == value)
    {
        pBuf[0] = '.';
        pBuf[1] = '0';
        return 1;
    }

    while (value - (int)value)
    {
        digit = (int)(value * 2);

        bits[len++] = (digit & 0x1);

        if (32 == len) break;

        value = ((value * 2) - digit);
    }

    if (len > bufSize)
    {
        printf("ERR: un-enough buffer size (%d < %d)\n", bufSize, len);
        return 0;
    }

    *pBuf = '.'; pBuf++;
    for (i=0; i<len; i++)
    {
        *pBuf = (bits[i] ? '1' : '0');
        pBuf++;
    }

    return len;
}

int main(int argc, char *argv[])
{
    char  input[256];
    char *pInput = "-0.078125";
    char *pChar;
    int   i = 0;

    char  buf[256];
    char *pBuf = buf;
    unsigned int  ieee754;
    unsigned int  fraction;
    int  exponent;
    int  sign;

    char *pInt = NULL;
    char *pDec = NULL;
    char *pDot = NULL;
    int  lenInt;
    int  lenDec;
    int  n;


    if (argc > 1)
    {
        pInput = argv[1];
    }

    strncpy(input, pInput, 255);
    memset(buf, 0x00, 256);

    pInt = input;
    if ('-' == input[0])
    {
        buf[0] = '-';
        pBuf++;
        pInt++;
        i++;
    }

    for (; i<strlen( input ); i++)
    {
        if ('.' == input[i])
        {
            pDec = &(input[i]);
            input[i] = 0x00;
            break;
        }
    }

    if ((NULL == pInt) || (NULL == pDec))
    {
        printf("ERR: wrong input %s\n\n", pInput);
        return -1;
    }


    printf("1) floating-point to binary format\n");

    lenInt = int2bin(atoi(pInt), pBuf, 80);

    *pDec = '.';
    lenDec = float2bin(atof(pDec), (pBuf + lenInt), 80);
    pDot = (pBuf + lenInt);

    printf("   %s\n\n", buf);


    printf("2) represent by scientific notation\n");

    exponent = 0;

    for (n=1, pChar=pBuf; (*pChar) && (*pChar != '.'); pChar++)
    {
        if ('1' == *pChar)
        {
            exponent = (lenInt - n);

            for (i=0; i<exponent; i++)
            {
                *pDot = *(pDot - 1);
                pDot--;
            }
            *pDot = '.';

            pBuf = buf;

            goto _DONE;
        }

        n++;
    }

    for (n=-1, pChar++; *pChar; pChar++)
    {
        if ('1' == *pChar)
        {
            exponent = n;

            for (i=0; i>exponent; i--)
            {
                *pDot = *(pDot + 1);
                pDot++;
            }
            *pDot = '.';
            if (0x00 == *(pDot + 1))
            {
                /* append '0' */
                *(pDot + 1) = '0';
                *(pDot + 2) = 0x00;
            }

            if ('-' == buf[0])
            {
                pBuf = (pDot - 2);
                *pBuf = '-';
            }
            else
            {
                pBuf = (pDot - 1);
            }

            break;
        }

        n--;
    }

    if (0 == exponent)
    {
        /* 0.0 */
        exponent = -127;
    }

_DONE:
    printf("   %s x 2^%d\n\n", pBuf, exponent);


    printf("3) 32-bit floating-point format\n");

    sign = ('-' == buf[0]);
    exponent = (127 + exponent);
    fraction = 0;
    for (pChar=(pDot+1), i=22; *pChar && i>=0; pChar++)
    {
        fraction |= ((unsigned int)((*pChar - '0') & 0x1) << i);
        i--;
    }

    ieee754 = 0;
    ieee754 |= ((unsigned int)(sign & 0x1) << 31);
    ieee754 |= ((unsigned int)(exponent & 0xFF) << 23);
    ieee754 |= (fraction & 0x7FFFFF);

    printf("   ");
    printf("[1;31m%u[0m", (sign & 0x1));
    printf("[1;33m");
    printf(
        "%d%d%d",
        ((exponent >>  7) & 0x1),
        ((exponent >>  6) & 0x1),
        ((exponent >>  5) & 0x1)
    );
    printf(
        " %d%d%d%d",
        ((exponent >>  4) & 0x1),
        ((exponent >>  3) & 0x1),
        ((exponent >>  2) & 0x1),
        ((exponent >>  1) & 0x1)
    );
    printf(
        " %d",
        ((exponent      ) & 0x1)
    );
    printf("[0m");
    printf("[1;32m");
    printf(
        "%d%d%d",
        ((fraction >> 22) & 0x1),
        ((fraction >> 21) & 0x1),
        ((fraction >> 20) & 0x1)
    );
    for (i=0; i<5; i++)
    {
        printf(
            " %d%d%d%d",
            ((fraction >> (19 - (i * 4))) & 0x1),
            ((fraction >> (18 - (i * 4))) & 0x1),
            ((fraction >> (17 - (i * 4))) & 0x1),
            ((fraction >> (16 - (i * 4))) & 0x1)
        );
    }
    printf("[0m\n");
    printf(" = 0x%x\n", ieee754);
    printf(" = %f\n\n", *((float *)( &ieee754 )));

    printf("   sign    : %d\n", sign);
    printf("   exponent: %d\n", exponent);
    printf("   fraction: 0x%x\n\n", fraction);


    return 0;
}

