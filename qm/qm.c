#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "qm.h"


// /////////////////////////////////////////////////////////////////////////////
//    Macro declarations
// /////////////////////////////////////////////////////////////////////////////

#define IS_NUMBER(c)  ((c >= '0') && (c <= '9'))

#define LINE_LEN   1023
#define TOKEN_LEN  255

#define OPERAND   0
#define OPERATOR  1
#define TERMINAL  2
#define VALUE     3

#define DEBUG  0


// /////////////////////////////////////////////////////////////////////////////
//    Type declarations
// /////////////////////////////////////////////////////////////////////////////

typedef struct variable
{
    char name[TOKEN_LEN+1];
    int  value;
    int  power;
    struct variable *next;
} TOKEN;

typedef struct postfix
{
    TOKEN *token;
    char  op;
    int   type;
    struct postfix *link;
    struct postfix *next;
} LIST;


typedef struct item
{
    char *term;
    char  min[TOKEN_LEN+1];
    int   group;
    int   prime;
    struct item *node;
    struct item *next;
} TABLE;

typedef struct minterm
{
    char min[TOKEN_LEN+1];
    int  index;
    int  include;
    struct minterm *next;
} MINTERM;

typedef struct element
{
    char *term;
    char  min[TOKEN_LEN+1];
    int  *EPI;
    int   check;
    struct element *next;
} PRIME;


// /////////////////////////////////////////////////////////////////////////////
//    Variables declarations
// /////////////////////////////////////////////////////////////////////////////

char  g_buf[LINE_LEN+1];


// /////////////////////////////////////////////////////////////////////////////
//    Functions
// /////////////////////////////////////////////////////////////////////////////

/* In Comming Priority */
int ICP(char op)
{
    int priority;

    switch ( op )
    {
        case  '(':
            priority = 999;
            break;
        case _NOT:
            priority = 5; /* right association */
            break;
        case _XOR:
            priority = 3;
            break;
        case _AND:
            priority = 2;
            break;
        case  _OR:
            priority = 1;
            break;
        default:
            priority = 0;
    }

    return priority;
}

/* In Stack Priority */
int ISP(char op)
{
    int priority;

    switch ( op )
    {
        case  '(':
            priority = 0;
            break;
        case _NOT:
            priority = 4;
            break;
        case _XOR:
            priority = 3;
            break;
        case _AND:
            priority = 2;
            break;
        case  _OR:
            priority = 1;
            break;
        default:
            priority = -999;
    }

    return priority;
}


void freeTokenList(TOKEN *pListHead)
{
    TOKEN *pListNode;
    TOKEN *pListTail;

    pListNode = pListHead;
    pListTail = NULL;
    while (pListNode != NULL)
    {
        pListTail = pListNode;
        pListNode = pListNode->next;
        free( pListTail );
    }
}

void freePostfixList(LIST *pListHead)
{
    LIST *pListNode;
    LIST *pListTail;

    pListNode = pListHead;
    pListTail = NULL;
    while (pListNode != NULL)
    {
        pListTail = pListNode;
        pListNode = pListNode->next;
        free( pListTail );
    }
}

void freeTableList(TABLE *pListHead)
{
    TABLE *pListNode;
    TABLE *pListTail;

    pListNode = pListHead;
    pListTail = NULL;
    while (pListNode != NULL)
    {
        pListTail = pListNode;
        pListNode = pListNode->next;
        free( pListTail );
    }
}

void freeMintermList(MINTERM *pListHead)
{
    MINTERM *pListNode;
    MINTERM *pListTail;

    pListNode = pListHead;
    pListTail = NULL;
    while (pListNode != NULL)
    {
        pListTail = pListNode;
        pListNode = pListNode->next;
        free( pListTail );
    }
}

void freePrimeList(PRIME *pListHead)
{
    PRIME *pListNode;
    PRIME *pListTail;

    pListNode = pListHead;
    pListTail = NULL;
    while (pListNode != NULL)
    {
        pListTail = pListNode;
        pListNode = pListNode->next;
        free( pListTail );
    }
}

int getTokenLength(TOKEN *pTokenHead)
{
    TOKEN *pTokenNode = NULL;
    double k = 0.0;
    int len = 0;

    for (pTokenNode=pTokenHead;
         pTokenNode!=NULL;
         pTokenNode=pTokenNode->next)
    {
        len++;
    }

    for (pTokenNode=pTokenHead, k=(len-1);
         pTokenNode!=NULL;
         pTokenNode=pTokenNode->next, k--)
    {
        pTokenNode->power = (int)pow(2.0, k);
    }

    return len;
}

void checkPriority(LIST **ppPostTail, LIST **ppStackHead, char op)
{
    LIST *pStackTop = NULL;
    LIST *pPostNode = NULL;

    pStackTop = (*ppStackHead);
    while ((pStackTop != NULL) && (ISP(pStackTop->op) >= ICP(op)))
    {
        /* pop an operator from stack */
        pPostNode = pStackTop;
        pStackTop = pStackTop->next;
        pPostNode->next = NULL;
        (*ppPostTail)->next = pPostNode;
        (*ppPostTail) = pPostNode;
    }

    /* push the operator into stack */
    pPostNode = (LIST *)malloc( sizeof(LIST) );
    pPostNode->token = (TOKEN *)malloc( sizeof(TOKEN) );
    sprintf(pPostNode->token->name, "%c", op);
    pPostNode->token->next = NULL;
    pPostNode->op   = op;
    pPostNode->type = OPERATOR;
    pPostNode->link = NULL;
    pPostNode->next = pStackTop;
    (*ppStackHead)  = pPostNode;
}


void addVariable(
    LIST  **ppPostHead,
    LIST  **ppPostTail,
    TOKEN **ppTokenHead,
    char   *pString
)
{
    LIST  *pPostNode  = NULL;
    TOKEN *pTokenNode = NULL;
    TOKEN *pTokenRear = NULL;
    TOKEN *pTokenNew  = NULL;
    int exist;

    pTokenNode = (*ppTokenHead);
    pTokenRear = NULL;
    exist = 0;
    while (pTokenNode != NULL)
    {
        pTokenRear = pTokenNode;
        pTokenNode = pTokenNode->next;

        if (0 == strcmp(pTokenRear->name, pString))
        {
            pTokenNew = pTokenRear;
            exist = 1;
        }
    }

    if ( !exist )
    {
        pTokenNew = (TOKEN *)malloc( sizeof(TOKEN) );
        strcpy(pTokenNew->name, pString);
        pTokenNew->next = NULL;

        if ((*ppTokenHead) == NULL)
        {
            (*ppTokenHead) = pTokenNew;
        }
        else
        {
            pTokenRear->next = pTokenNew;
        }
    }

    pPostNode = (LIST *)malloc( sizeof(LIST) );
    pPostNode->token = pTokenNew;
    pPostNode->op    = 0x00;
    pPostNode->type  = OPERAND;
    pPostNode->link  = NULL;
    pPostNode->next  = NULL;

    if (NULL == (*ppPostHead))
    {
        (*ppPostHead) = pPostNode;
        (*ppPostTail) = pPostNode;
    }
    else
    {
        (*ppPostTail)->next = pPostNode;
        (*ppPostTail) = pPostNode;
    }
}

void findParentheses(LIST **ppPostTail, LIST **ppStackHead)
{
    LIST *pStackTop = NULL;
    LIST *pPostNode = NULL;

    pStackTop = (*ppStackHead);
    while ((pStackTop != NULL) && (pStackTop->op != '('))
    {
        /* pop an operator from stack */
        pPostNode = pStackTop;
        pStackTop = pStackTop->next;
        pPostNode->next = NULL;
        (*ppPostTail)->next = pPostNode;
        (*ppPostTail) = pPostNode;
    }

    /* pop the element: '(' */
    pPostNode = pStackTop;
    pStackTop = pStackTop->next;
    (*ppStackHead) = pStackTop;
    free( pPostNode );
    pPostNode = NULL;
}

int evaluationPostfix(LIST *pPostHead, TOKEN *pTokenHead)
{
    LIST *pPostCurr = NULL;
    LIST *pPostNode = NULL;
    LIST *pStackHead = NULL;
    int a = 0;
    int b = 0;
    int q = 0;
    int z = 0;

    /* get the first element in stack */
    pPostCurr = pPostHead;
    while (pPostCurr != NULL)
    {
        if (pPostCurr->type == OPERAND)
        {
            /* push the operand into stack */
            pPostCurr->link = pStackHead;
            pStackHead = pPostCurr;
        }
        else
        {
            /* pop an element */
            pPostNode = pStackHead;
            if (NULL == pPostNode)
            {
                freePostfixList( pStackHead );
                freePostfixList( pPostHead );
                freeTokenList( pTokenHead );
                return QM_FAIL_TO_POP_OPERAND;
            }
            pStackHead = pStackHead->link;
            a = pPostNode->token->value;

            /* pop second element */
            if (pPostCurr->op != '!')
            {
                pPostNode = pStackHead;
                if (NULL == pPostNode)
                {
                    freePostfixList( pStackHead );
                    freePostfixList( pPostHead );
                    freeTokenList( pTokenHead );
                    return QM_FAIL_TO_POP_OPERAND;
                }
                pStackHead = pStackHead->link;
                b = pPostNode->token->value;
            }

            switch ( pPostCurr->op )
            {
                case _NOT:
                    q = (a == 1) ? 0 : 1;
                    break;
                case _XOR:
                    q = (a == b) ? 0 : 1;
                    break;
                case _AND:
                    q = ((a == 1) && (b == 1)) ? 1 : 0;
                    break;
                case  _OR:
                    q = ((a == 1) || (b == 1)) ? 1 : 0;
                    break;
                default:
                    freePostfixList( pStackHead );
                    freePostfixList( pPostHead );
                    freeTokenList( pTokenHead );
                    return QM_INVALID_OPERAND;
            }

            /* push into stack */
            pPostNode = (LIST *)malloc( sizeof(LIST) );
            pPostNode->token = (TOKEN *)malloc( sizeof(TOKEN) );
            pPostNode->token->value = q;
            pPostNode->token->next  = NULL;
            pPostNode->op   = 0x00;
            pPostNode->type = VALUE;
            pPostNode->link = pStackHead;
            pPostNode->next = NULL;
            pStackHead = pPostNode;
        }

        pPostCurr = pPostCurr->next;
    }

    /* pop the final value */
    pPostNode = pStackHead;
    if (NULL == pPostNode)
    {
        freePostfixList( pPostHead );
        freeTokenList( pTokenHead );
        return QM_FAIL_TO_POP_OPERAND;
    }
    pStackHead = pStackHead->link;
    z = pPostNode->token->value;

    freePostfixList( pStackHead );

    return z;
}


int QM_reduction(char *pTarget, char *pStr1, char *pStr2)
{
    int same;
    int len;
    int i;

    same = 1;
    len  = strlen(pStr2);
    for (i=0; i<len; i++)
    {
        if (pStr1[i] != pStr2[i])
        {
            same = 0;
            break;
        }
    }

    if ((pStr1 != pTarget) && IS_NUMBER(*(pStr1-1)))
    {
        return 0;
    }
    else if ((pStr1[i] != 0) && IS_NUMBER(pStr1[i]))
    {
        return 0;
    }

    if (same == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int QM_cancellation(char *p1st, char *p2nd)
{
    int different;
    int cancel;
    int i;

    different = 0;
    cancel = 0;
    for (i=0; i<(int)strlen(p1st); i++)
    {
        if (p1st[i] != p2nd[i])
        {
            different++;
            cancel = i;
        }
    }

    return ((1 == different) ? cancel : -1);
}

int QM_insertTable(TABLE **ppTableHead, TABLE **ppTableTail, TABLE *pTableNew)
{
    TABLE *pTableNode = NULL;
    TABLE *pTableTemp = NULL;
    TABLE *pTableRear = NULL;

    if (NULL == (*ppTableHead))
    {
        (*ppTableHead) = pTableNew;
        (*ppTableTail) = pTableNew;
    }
    else
    {
        pTableNode = *ppTableHead;
        pTableTemp = NULL;
        while ((pTableNode != NULL) && (pTableNode->group <= pTableNew->group))
        {
            pTableTemp = pTableNode;
            pTableNode = pTableNode->next;
        }

        if (NULL == pTableTemp)
        {
            pTableNew->next = *ppTableHead;
            (*ppTableHead) = pTableNew;
        }
        else
        {
            if (pTableTemp->group == pTableNew->group)
            {
                pTableNode = pTableTemp;
                pTableRear = NULL;
                while (pTableNode != NULL)
                {
                    pTableRear = pTableNode;
                    pTableNode = pTableNode->node;

                    if (strcmp(pTableRear->term, pTableNew->term) == 0)
                    {
                        free( pTableNew );
                        return 0;
                    }
                }

                if (NULL == pTableRear)
                {
                    freeTableList( (*ppTableHead) );
                    (*ppTableHead) = NULL;
                    return QM_FAIL_TO_INSERT_TABLE;
                }
                pTableRear->node = pTableNew;
            }
            else
            {
                (*ppTableTail)->next = pTableNew;
                (*ppTableTail) = pTableNew;
            }
        }
    }

    return 0;
}

PRIME *QM_recursive(
    TABLE *pTableHead,
    TABLE *pTableTail,
    int    number,
    int    count,
    FILE  *pLog
)
{
    TABLE *pTableReturnHead = NULL;
    TABLE *pTableReturnTail = NULL;
    TABLE *pTableGroup = NULL;
    TABLE *pTableNode1 = NULL;
    TABLE *pTableNode2 = NULL;
    TABLE *pTableNew   = NULL;
    PRIME *pPrimeHead  = NULL;
    PRIME *pPrimeTail  = NULL;
    PRIME *pPrimeNode  = NULL;

    char min[TOKEN_LEN+1];
    int  cancel;
    int  i;


    if (NULL == pTableHead) return NULL;

    for (pTableGroup=pTableHead; pTableGroup!=pTableTail; pTableGroup=pTableGroup->next)
    {
        for (pTableNode1=pTableGroup; pTableNode1!=NULL; pTableNode1=pTableNode1->node)
        {
            for (pTableNode2=pTableGroup->next; pTableNode2!=NULL; pTableNode2=pTableNode2->node)
            {
                if ((cancel=QM_cancellation(pTableNode1->term, pTableNode2->term)) >= 0)
                {
                    pTableNode1->prime = 1;
                    pTableNode2->prime = 1;
                    sprintf(min, "%s, ", pTableNode1->min);
                    strcat(min, pTableNode2->min);

                    pTableNew = (TABLE *)malloc( sizeof(TABLE) );
                    pTableNew->term = (char *)malloc( (number+1)*sizeof(char) );
                    strcpy(pTableNew->term, pTableNode1->term);
                    pTableNew->term[cancel] = '-';
                    strcpy(pTableNew->min, min);
                    pTableNew->group = pTableNode1->group;
                    pTableNew->prime = 0;
                    pTableNew->node  = NULL;
                    pTableNew->next  = NULL;

                    /* create new table */
                    if (0 != QM_insertTable(&pTableReturnHead, &pTableReturnTail, pTableNew))
                    {
                        return NULL;
                    }
                }
            }
        }
    }

    pPrimeHead = NULL;
    for (pTableGroup=pTableHead; pTableGroup!=NULL; pTableGroup=pTableGroup->next)
    {
        for (pTableNode1=pTableGroup; pTableNode1!=NULL; pTableNode1=pTableNode1->node)
        {
            if ( pLog )
            {
                fprintf(pLog, "%c ", ((pTableNode1->prime == 0) ? '*' : ' '));
                fprintf(pLog, "%s  %s\n", pTableNode1->term, pTableNode1->min);
            }

            if (pTableNode1->prime == 0)
            {
                pPrimeNode = (PRIME *)malloc( sizeof(PRIME) );
                pPrimeNode->term = (char *)malloc( (number+1)*sizeof(char) );
                strcpy(pPrimeNode->term, pTableNode1->term);
                strcpy(pPrimeNode->min, pTableNode1->min);
                pPrimeNode->EPI = (int *)malloc( (count+1)*sizeof(int) );
                for (i=0; i<count; i++)
                {
                    pPrimeNode->EPI[i] = 0;
                }
                pPrimeNode->check = 0;
                pPrimeNode->next  = pPrimeHead;
                pPrimeHead = pPrimeNode;
            }
        }

        if ( pLog )
        {
            fprintf(pLog, "------------------------------------------\n");
        }
    }

    pPrimeNode = pPrimeHead;
    pPrimeTail = pPrimeHead;
    while (pPrimeNode != NULL)
    {
        pPrimeTail = pPrimeNode;
        pPrimeNode = pPrimeNode->next;
    }

    pPrimeNode = QM_recursive(pTableReturnHead, pTableReturnTail, number, count, pLog);
    if (NULL == pPrimeTail)
    {
        pPrimeHead = pPrimeNode;
    }
    else
    {
        pPrimeTail->next = pPrimeNode;
    }

    return pPrimeHead;
}

void QM_minimization(
    TOKEN   *pTokenHead,
    PRIME   *pPrimeHead,
    MINTERM *pMinHead,
    int      count,
    char    *pOutput,
    int      outputLen,
    FILE    *pLog
)
{
    PRIME   *pPrimeReturnHead = NULL;
    PRIME   *pPrimeReturnNode = NULL;
    PRIME   *pPrimeNode = NULL;
    PRIME   *pPrimeTemp = NULL;
    MINTERM *pMinNode   = NULL;
    TOKEN   *pTokenNode = NULL;
    char *pStr;
    int  found;
    int  i;
    int  j;
    int  k;
    int  n;


    if ( pLog )
    {
        fprintf(pLog, "\n");
        fprintf(pLog, "Prime Implicant:\n");
    }

    pPrimeReturnHead = NULL;
    for (pMinNode=pMinHead; pMinNode!=NULL; pMinNode=pMinNode->next)
    {
        if ( pLog )
        {
            fprintf(pLog, "%2s ", pMinNode->min);
        }

        for (pPrimeNode=pPrimeHead; pPrimeNode!=NULL; pPrimeNode=pPrimeNode->next)
        {
            if ((pStr=strstr(pPrimeNode->min, pMinNode->min)) != NULL)
            {
                if ( QM_reduction(pPrimeNode->min, pStr, pMinNode->min) )
                {
                    pMinNode->include++;
                    pPrimeNode->EPI[pMinNode->index] = 1;
                    pPrimeTemp = pPrimeNode;
                }
            }
        }

        if ((pMinNode->include == 1) && (pPrimeTemp->check == 0))
        {
            /* find E.P.I. */
            pPrimeTemp->check = 1;
            pPrimeReturnNode = (PRIME *)malloc( sizeof(PRIME) );
            memcpy(pPrimeReturnNode, pPrimeTemp, sizeof(PRIME));
            pPrimeReturnNode->next = pPrimeReturnHead;
            pPrimeReturnHead = pPrimeReturnNode;
        }
    }

    for (pPrimeNode=pPrimeReturnHead; pPrimeNode!=NULL; pPrimeNode=pPrimeNode->next)
    {
        for (pMinNode=pMinHead; pMinNode!=NULL; pMinNode=pMinNode->next)
        {
            if (pPrimeNode->EPI[pMinNode->index] == 1)
            {
                pMinNode->include = 0;
            }
        }
    }

    if ( pLog )
    {
        fprintf(pLog, "\n");
        #if DEBUG
        {
            for (pMinNode=pMinHead; pMinNode!=NULL; pMinNode=pMinNode->next)
            {
                fprintf(pLog, "%d ", pMinNode->include);
            }
            fprintf(pLog, "\n");
            fprintf(pLog, "--\n");
        }
        #endif
    }

    for (pPrimeNode=pPrimeHead, i=0; pPrimeNode!=NULL; pPrimeNode=pPrimeNode->next, i++)
    {
        if ( pLog )
        {
            for (i=0; i<count; i++)
            {
                fprintf(pLog, " %c ", ((pPrimeNode->EPI[i] == 1) ? 'x' : ' '));
            }
            fprintf(pLog, " %2s\n", pPrimeNode->min);
        }

        if (pPrimeNode->check == 0)
        {
            found = 0;
            for (pMinNode=pMinHead; pMinNode!=NULL; pMinNode=pMinNode->next)
            {
                if (pMinNode->include != 0)
                {
                    if (pPrimeNode->EPI[pMinNode->index] == 1)
                    {
                        /* find the necessary prime implicant */
                        found = 1;
                    }
                    else
                    {
                        found = 0;
                        break;
                    }
                }
            }

            if (found == 1)
            {
                pPrimeNode->check = 1;
                pPrimeReturnNode = (PRIME *)malloc( sizeof(PRIME) );
                memcpy(pPrimeReturnNode, pPrimeNode, sizeof(PRIME));
                pPrimeReturnNode->next = pPrimeReturnHead;
                pPrimeReturnHead = pPrimeReturnNode;

                for (pMinNode=pMinHead; pMinNode!=NULL; pMinNode=pMinNode->next)
                {
                    if (pPrimeNode->EPI[pMinNode->index] == 1)
                    {
                        pMinNode->include = 0;
                    }
                }
            }
        }
    }

    if ( pLog )
    {
        fprintf(pLog, "\n");
    }

    /* print the minimized result */
    n = 0;
    for (pPrimeNode=pPrimeReturnHead, i=0; pPrimeNode!=NULL; pPrimeNode=pPrimeNode->next, i++)
    {
        if (i > 0)
        {
            pOutput[n++] = _OR;
            if (n >= outputLen) break;
        }

        k = 0;
        for (pTokenNode=pTokenHead, j=0; pTokenNode!=NULL; pTokenNode=pTokenNode->next, j++)
        {
            switch ( pPrimeNode->term[j] )
            {
                case '0':
                    if (j > k)
                    {
                        pOutput[n++] = _AND;
                        if (n >= outputLen) break;
                    }
                    pOutput[n++] = _NOT;
                    if (n >= outputLen) break;
                    for (pStr=pTokenNode->name; *pStr; pStr++)
                    {
                        pOutput[n++] = *pStr;
                        if (n >= outputLen) break;
                    }
                    break;
                case '1':
                    if (j > k)
                    {
                        pOutput[n++] = _AND;
                        if (n >= outputLen) break;
                    }
                    for (pStr=pTokenNode->name; *pStr; pStr++)
                    {
                        pOutput[n++] = *pStr;
                        if (n >= outputLen) break;
                    }
                    break;
                default:
                    if (k == j) k++;
            }
        }
    }
    pOutput[n] = 0x00;
}


/**
 * Quine McClusky minimization.
 * @param [in]   pInput     Input expression.
 * @param [out]  pOutput    Output expression.
 * @param [in]   outputLen  Output buffer length.
 * @param [in]   pLog       Debug log file.
 * @returns  Success(0) or failure(< 0).
 */
int QM(char *pInput, char *pOutput, int outputLen, FILE *pLog)
{
    TABLE *pTableHead = NULL;
    TABLE *pTableTail = NULL;
    TABLE *pTableNode = NULL;
    PRIME *pPrimeHead = NULL;
    MINTERM *pMinHead = NULL;
    MINTERM *pMinTail = NULL;
    MINTERM *pMinNode = NULL;

    LIST  *pPostHead  = NULL;
    LIST  *pPostTail  = NULL;
    #if DEBUG
    LIST  *pPostNode  = NULL;
    #endif
    LIST  *pStackHead = NULL;
    LIST  *pStackNode = NULL;
    TOKEN *pTokenHead = NULL;
    TOKEN *pTokenNode = NULL;

    char   token[TOKEN_LEN+1];
    char  *pCh;

    unsigned int loop;
    unsigned int min;
    unsigned int k;
    int  error = QM_SUCCESS;
    int  number;
    int  result;
    int  count;
    int  group;
    int  i;
    int  j;


    if ((NULL == pOutput) || (outputLen <= 1)) return QM_INVALID_OUTPUT_BUFFER;

    /* prepare stack with a min priority element */
    pStackHead = (LIST *)malloc( sizeof(LIST) );
    pStackHead->token = NULL;
    pStackHead->op    = 0x00;
    pStackHead->type  = TERMINAL;
    pStackHead->link  = NULL;
    pStackHead->next  = NULL;

    /* Read in single line from "stdin": */
    pTokenHead = NULL;
    pPostHead  = NULL;
    token[0]   = 0x00;
    for (pCh=pInput, j=0; *pCh; pCh++)
    {
        switch ( *pCh )
        {
            case 0x20:
            case '\t':
                /* ignore white space */
                break;
            case  ')':
                if (j != 0)
                {
                    addVariable(&pPostHead, &pPostTail, &pTokenHead, token);
                }
                token[j=0] = 0x00;

                findParentheses(&pPostTail, &pStackHead);
                break;
            case  '(':
            case _NOT:
            case _XOR:
            case _AND:
            case _OR:
                if (j != 0)
                {
                    addVariable(&pPostHead, &pPostTail, &pTokenHead, token);
                }
                token[j=0] = 0x00;

                checkPriority(&pPostTail, &pStackHead, *pCh);
                break;
            default:
                token[j++] = *pCh;
                token[j]   = 0x00;
        }
    }

    if (token[0] != 0x00)
    {
        addVariable(&pPostHead, &pPostTail, &pTokenHead, token);
    }
    token[j=0] = 0x00;

    while ((pStackHead != NULL) && (pStackHead->type != TERMINAL))
    {
        /* pop an operator from stack */
        pStackNode = pStackHead;
        pStackHead = pStackHead->next;
        pPostTail->next  = pStackNode;
        pStackNode->next = NULL;
        pPostTail  = pStackNode;
    }

    number = getTokenLength( pTokenHead );
    if (0 == number)
    {
        *pOutput = 0x00;
        error = QM_NOTHING;
        goto _EXIT;
    }


    #if DEBUG
    {
        fprintf(stderr, "Postfix:\n");
        for (pPostNode=pPostHead; pPostNode!=NULL; pPostNode=pPostNode->next)
        {
            fprintf(stderr, "%s ", (char *)pPostNode->token);
        }
        fprintf(stderr, "\n\n");

        /* print all variables */
        for (pTokenNode=pTokenHead; pTokenNode!=NULL; pTokenNode=pTokenNode->next)
        {
            fprintf(stderr, "%s ", pTokenNode->name);
        }
        fprintf(stderr, "\n");
    }
    #endif

    if ( pLog )
    {
        fprintf(pLog, "  ");
        for (pTokenNode=pTokenHead; pTokenNode!=NULL; pTokenNode=pTokenNode->next)
        {
            fprintf(pLog, "%s ", pTokenNode->name);
        }
        fprintf(pLog, "\n");
    }


    /* Begin of table initialization */
    pMinHead = NULL;
    count = 0;
    loop  = (unsigned int)pow(2.0, (double)number);
    for (min=0; min<loop; min++)
    {
        k = min;
        group = 0;
        for (pTokenNode=pTokenHead; pTokenNode!=NULL; pTokenNode=pTokenNode->next)
        {
            pTokenNode->value = (k / pTokenNode->power);
            k = (k % pTokenNode->power);

            group += pTokenNode->value;
            #if DEBUG
            {
                fprintf(stderr, "%d ", pTokenNode->value);
            }
            #endif
        }

        result = evaluationPostfix(pPostHead, pTokenHead);
        if (result < 0)
        {
            error = result;
            goto _EXIT;
        }
        #if DEBUG
        {
            fprintf(stderr, " %d  %d\n", result, min);
        }
        #endif

        /* list min-terms */
        if (1 == result)
        {
            pMinNode = (MINTERM *)malloc( sizeof(MINTERM) );
            sprintf(pMinNode->min, "%d", min);
            pMinNode->index   = count;
            pMinNode->include = 0;
            pMinNode->next    = NULL;
            if (NULL == pMinHead)
            {
                pMinHead = pMinNode;
                pMinTail = pMinNode;
            }
            else
            {
                pMinTail->next = pMinNode;
                pMinTail = pMinNode;
            }
            count++;

            pTableNode = (TABLE *)malloc( sizeof(TABLE) );
            pTableNode->term = (char *)malloc( (number+1)*sizeof(char) );
            for (pTokenNode=pTokenHead, i=0; pTokenNode!=NULL; pTokenNode=pTokenNode->next, i++)
            {
                pTableNode->term[i] = ((pTokenNode->value == 0) ? '0' : '1');
            }
            pTableNode->term[i] = 0x00;
            sprintf(pTableNode->min, "%d", min);
            pTableNode->group = group;
            pTableNode->prime = 0;
            pTableNode->node  = NULL;
            pTableNode->next  = NULL;

            if (0 != QM_insertTable(&pTableHead, &pTableTail, pTableNode))
            {
                return QM_FAIL_TO_INSERT_TABLE;
            }
        }
    }
    /* End of table initialization */


    #if DEBUG
    {
        fprintf(stderr, "\n");
    }
    #endif


    pPrimeHead = QM_recursive(pTableHead, pTableTail, number, count, pLog);
    if (0 == count)
    {
        snprintf(pOutput, outputLen, "0\n");
    }
    else if (loop == count)
    {
        snprintf(pOutput, outputLen, "1\n");
    }
    else
    {
        QM_minimization(
            pTokenHead,
            pPrimeHead,
            pMinHead,
            count,
            pOutput,
            (outputLen - 1),
            pLog
        );
    }


_EXIT:
    if ( pPrimeHead ) freePrimeList( pPrimeHead );
    if ( pTableHead ) freeTableList( pTableHead );
    if ( pMinHead ) freeMintermList( pMinHead );
    if ( pTokenHead ) freeTokenList( pTokenHead );
    if ( pPostHead ) freePostfixList( pPostHead );
    if ( pStackHead ) freePostfixList( pStackHead );

    return error;
}

