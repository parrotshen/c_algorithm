#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"


#define IS_UPPER_ALHPABET(ch)  ((ch >= 'A') && (ch <= 'Z'))
#define IS_LOWER_ALHPABET(ch)  ((ch >= 'a') && (ch <= 'z'))
#define IS_NUMBER(ch)          ((ch >= '0') && (ch <= '9'))
#define IS_SPACE(ch)           ((ch == ' ') || (ch == '\t'))
#define LINE_SIZE              (1023)
#define TOKEN_SIZE             (255)


void dump(void *pAddr, unsigned int size)
{
    unsigned char *pByte = pAddr;
    unsigned int  i;

    if (pAddr != NULL)
    {
        for (i=0; i<size; i++)
        {
            if ((i != 0) && ((i % 16) == 0))
            {
                printf("\n");
            }
            printf(" %02X", pByte[i]);
        }
        printf("\n");
        printf(" (%u bytes)\n", size);
        printf("\n");
    }
}

char *parse_token(char *pString, char *pToken, int tsize)
{
    int i = 0;

    if (0x0 == pString[0])
    {
        /* This is a NULL line */
        pToken[0] = 0x0;
        return NULL;
    }

    /* Bypass space and tab characters */
    for (; *pString && IS_SPACE(*pString); pString++);

    /* Pull out a token */
    for (; *pString && !IS_SPACE(*pString) && i<tsize; pString++, i++)
    {
        *pToken++ = *pString;
    }
    *pToken = 0x0;

    return pString;
}

int parse_line(FILE *pFile, char *pLine, int lsize)
{
    pLine[0] = 0x0;

    if ( feof(pFile) )
    {
        /* end of file */
        return -1;
    }

    /* char *fgets(                                   */
    /*     char *s,      // character array to store  */
    /*     int   n,      // length to read            */
    /*     FILE *stream  // FILE pointer              */
    /* );                                             */
    fgets(pLine, lsize, pFile);

    /* remove the CR/LF character */
    if ((strlen(pLine) > 0) && (pLine[strlen(pLine)-1] == 0x0a))
    {
        pLine[strlen(pLine)-1] = 0x0;
    }
    if ((strlen(pLine) > 0) && (pLine[strlen(pLine)-1] == 0x0d))
    {
        pLine[strlen(pLine)-1] = 0x0;
    }

    return strlen(pLine);
}

int parse_complex(char *pFileName, tComplex *pBuf, int num)
{
    FILE *pInput = NULL;
    char  line[LINE_SIZE+1];
    char  token[TOKEN_SIZE+1];
    char *pNext;
    int  count;
    int  more;


    if ((pInput=fopen(pFileName, "r")) == NULL)
    {
        printf("ERR: cannot open file %s\n", pFileName);
        return 0;
    }

    /* start reading input file */
    count = 0;
    do
    {
        if ((more=parse_line(pInput, line, LINE_SIZE)) > 0)
        {
            pNext = parse_token(line, token, TOKEN_SIZE);
            if ( token[0] )
            {
                if (count >= num)
                {
                    printf("ERR: ignore data (> %d)\n", num);
                    goto _EXIT_PARSE;
                }

                pBuf[count].real = strtod(token, NULL);

                parse_token(pNext, token, TOKEN_SIZE);

                pBuf[count].imag = strtod(token, NULL);

                count++;
            }
        }
    } while (more != -1);

_EXIT_PARSE:
    fclose( pInput );

    return count;
}

int store_complex(char *pFileName, tComplex *pBuf, int num)
{
    FILE *pOutput = NULL;
    int  i;

    if ((pOutput=fopen(pFileName, "w")) == NULL)
    {
        printf("ERR: cannot open file %s\n", pFileName);
        return -1;
    }

    for (i=0; i<num; i++)
    {
        fprintf(pOutput, "%f\t%f\n", pBuf[i].real, pBuf[i].imag);
    }

    fclose( pOutput );

    return 0;
}

