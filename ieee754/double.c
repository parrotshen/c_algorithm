#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * Convert 64-bit integer to string in binary format
 * @param [in]  value    Integer value.
 * @param [in]  pBuf     String buffer.
 * @param [in]  bufSize  String buffer size.
 * @returns  Number of bits.
 */
int long2bin(unsigned long long value, char *pBuf, int bufSize)
{
    unsigned char bits[64];
    int len = 0;
    int i;


    if (0 == value)
    {
        if (bufSize < 2)
        {
            printf("ERR: un-enough buffer size (%d < 2)\n", bufSize);
            pBuf[0] = 0x00;
            return 0;
        }
        pBuf[0] = '0';
        pBuf[1] = 0x00;
        return 1;
    }

    while ( value )
    {
        bits[len++] = (value & 0x1LL);
        value >>= 1;
    }

    if ((len + 1) > bufSize)
    {
        printf("ERR: un-enough buffer size (%d < %d)\n", bufSize, (len + 1));
        if (len > 0) len = (len - 1);
    }

    for (i=len; i>0; i--)
    {
        *pBuf = (bits[i - 1] ? '1' : '0');
        pBuf++;
    }
    *pBuf = 0x00;

    return len;
}

/**
 * Convert 64-bit floating-point to string in binary format
 * @param [in]  value    Floating-point value.
 * @param [in]  pBuf     String buffer.
 * @param [in]  bufSize  String buffer size.
 * @returns  Number of bits.
 */
int double2bin(double value, char *pBuf, int bufSize)
{
    unsigned char bits[128];
    int len = 0;
    int digit;
    int i;


    if (0.0 == value)
    {
        if (bufSize < 3)
        {
            printf("ERR: un-enough buffer size (%d < 3)\n", bufSize);
            pBuf[0] = 0x00;
            return 0;
        }
        pBuf[0] = '.';
        pBuf[1] = '0';
        pBuf[2] = 0x00;
        return 1;
    }

    while (value - (int)value)
    {
        digit = (int)(value * 2);

        bits[len++] = (digit & 0x1);

        if (128 == len) break;

        value = ((value * 2) - digit);
    }

    if ((len + 2) > bufSize)
    {
        printf("ERR: un-enough buffer size (%d < %d)\n", bufSize, (len + 2));
        len = ((len > 1) ? (len - 2) : (len - 1));
    }

    *pBuf = '.'; pBuf++;
    for (i=0; i<len; i++)
    {
        *pBuf = (bits[i] ? '1' : '0');
        pBuf++;
    }
    *pBuf = 0x00;

    return len;
}

int main(int argc, char *argv[])
{
    char  input[256];
    char *pInput = "41209.057373046875";
    char *pChar;
    int   i = 0;

    char  buf[256];
    char *pBuf = buf;
    unsigned long long  ieee754;
    unsigned long long  fraction;
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

    lenInt = long2bin(atoll(pInt), pBuf, 80);

    *pDec = '.';
    lenDec = double2bin(atof(pDec), (pBuf + lenInt), 160);
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
        exponent = -1023;
    }

_DONE:
    printf("   %s x 2^%d\n\n", pBuf, exponent);


    printf("3) 64-bit floating-point format\n");

    sign = ('-' == buf[0]);
    exponent = (1023 + exponent);
    fraction = 0;
    for (pChar=(pDot+1), i=51; *pChar && i>=0; pChar++)
    {
        fraction |= ((unsigned long long)((*pChar - '0') & 0x1) << i);
        i--;
    }

    ieee754 = 0;
    ieee754 |= ((unsigned long long)(sign & 0x1) << 63);
    ieee754 |= ((unsigned long long)(exponent & 0x7FF) << 52);
    ieee754 |= (fraction & 0xFFFFFFFFFFFFFLL);

    printf("   ");
    printf("[1;31m%u[0m", (sign & 0x1));
    printf("[1;33m");
    printf(
        "%d%d%d",
        ((exponent >> 10) & 0x1),
        ((exponent >>  9) & 0x1),
        ((exponent >>  8) & 0x1)
    );
    printf(
        " %d%d%d%d",
        ((exponent >>  7) & 0x1),
        ((exponent >>  6) & 0x1),
        ((exponent >>  5) & 0x1),
        ((exponent >>  4) & 0x1)
    );
    printf(
        " %d%d%d%d",
        ((exponent >>  3) & 0x1),
        ((exponent >>  2) & 0x1),
        ((exponent >>  1) & 0x1),
        ((exponent      ) & 0x1)
    );
    printf("[0m");
    printf("[1;32m");
    for (i=0; i<13; i++)
    {
        printf(
            " %d%d%d%d",
            (int)((fraction >> (51 - (i * 4))) & 0x1),
            (int)((fraction >> (50 - (i * 4))) & 0x1),
            (int)((fraction >> (49 - (i * 4))) & 0x1),
            (int)((fraction >> (48 - (i * 4))) & 0x1)
        );
    }
    printf("[0m\n");
    printf(" = 0x%llx\n", ieee754);
    printf(" = %lf\n\n", *((double *)( &ieee754 )));

    printf("   sign    : %d\n", sign);
    printf("   exponent: %d\n", exponent);
    printf("   fraction: 0x%llx\n\n", fraction);


    return 0;
}

