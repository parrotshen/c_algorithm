/* Quine McClusky Minimization */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "qm.h"


// /////////////////////////////////////////////////////////////////////////////
//    Macro declarations
// /////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////
//    Type declarations
// /////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////
//    Variables declarations
// /////////////////////////////////////////////////////////////////////////////

char  g_bufIn[1024];
char  g_bufOut[1024];


// /////////////////////////////////////////////////////////////////////////////
//    Functions
// /////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    FILE *pLog = NULL;
    char  ch;
    int   error;
    int   i;


    fprintf(stderr, "[ Quine McClusky Minimization Method ]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "NOT: %c\n", _NOT);
    fprintf(stderr, "XOR: %c\n", _XOR);
    fprintf(stderr, "AND: %c\n", _AND);
    fprintf(stderr, "OR : %c\n", _OR);
    fprintf(stderr, "\n");

    getcwd(g_bufIn, 1023);
    strcat(g_bufIn, "/qm_mini.log");
    if (NULL == (pLog=fopen(g_bufIn, "w")))
    {
        fprintf(stderr, "ERR: cannot open log file %s\n\n", g_bufIn);
    }

    fprintf(stderr, "Please input boolean expression:\n");
    fprintf(stderr, "> ");

    /* Read in single line from "stdin": */
    for (i=0; (i<1023) && ((ch=getchar())!=EOF) && (ch!='\n'); i++)
    {
        g_bufIn[i] = ch;
    }
    g_bufIn[i] = 0x00;
    fprintf(stderr, "\n");

    if (0 == strcmp("quit", g_bufIn))
    {
        if ( pLog ) fclose( pLog );
        return 0;
    }

    error = QM(g_bufIn, g_bufOut, 1024, pLog);

    switch ( error )
    {
        case QM_SUCCESS:
            fprintf(stderr, "  %s\n", g_bufIn);
            fprintf(stderr, "= %s\n\n", g_bufOut);
            break;
        case QM_NOTHING:
            break;
        case QM_FAIL_TO_POP_OPERAND:
            fprintf(stderr, "ERR: fail to pop operand\n\n");
            break;
        case QM_FAIL_TO_INSERT_TABLE:
            fprintf(stderr, "ERR: fail to insert table\n\n");
            break;
        case QM_INVALID_OUTPUT_BUFFER:
            fprintf(stderr, "ERR: invalid output buffer\n\n");
            break;
        case QM_INVALID_OPERAND:
            fprintf(stderr, "ERR: invalid operand\n\n");
            break;
        default:
            fprintf(stderr, "ERR: unknown\n\n");
    }

    if ( pLog ) fclose( pLog );

    return 0;
}

