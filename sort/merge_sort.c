#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern.c"


int merge_sort(
    int  A[],
    int  len,
    int  left,
    int  right,
    int  verbose
)
{
    int *B = NULL;
    int swaps = 0;
    int midL;
    int midR;
    int idxL;
    int idxR;
    int i;

    if (left < right)
    {
        /* [1] find the middle position */
        midL = ((left + right) / 2);
        midR = (midL + 1);

        /* [2] recursive each part */
        swaps += merge_sort(A, len, left, midL, verbose);
        swaps += merge_sort(A, len, midR, right, verbose);

        /* [3] merge two parts */
        B = malloc( (sizeof(int) * len) );
        memset(B, 0, (sizeof(int) * len));

        /* copy the left part */
        for (i=left; i<=midL; i++)
        {
            B[i] = A[i];
        }

        /* copy the right part */
        for (i=midR; i<=right; i++)
        {
            B[right-i+midR] = A[i];
        }

        idxL = left;
        idxR = right;
        for (i=left; i<=right; i++)
        {
            if (B[idxL] < B[idxR])
            {
                if (A[i] != B[idxL])
                {
                    A[i] = B[idxL];
                    swaps++;
                }
                idxL++;
            }
            else
            {
                if (A[i] != B[idxR])
                {
                    A[i] = B[idxR];
                    swaps++;
                }
                idxR--;
            }
        }

        free( B );

        if ( verbose )
        {
            show_result(A, len, -1, -1);
        }
    }

    return swaps;
}

int main(int argc, char *argv[])
{
    int verbose = 0;
    int swaps;

    if (argc > 1)
    {
        if (0 == strcmp("-v", argv[1]))
        {
            verbose = 1;
        }
    }

    if ( verbose )
    {
        show_result(g_data, g_dataLen, -1, -1);
    }

    swaps = merge_sort(
                g_data,
                g_dataLen,
                0,
                (g_dataLen - 1),
                verbose
            );

    printf("\n");
    printf("Number of swaps: %d\n", swaps);
    printf("\n");
    show_result(g_data, g_dataLen, -1, -1);
    printf("\n");

    return 0;
}

