#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern.c"


int bubble_sort(int A[], int len, int verbose)
{
    int swaps = 0;
    int temp;
    int done;
    int i;
    int j;

    for (i=0; i<(len-1); i++)
    {
        done = 1;

        for (j=0; j<(len-1-i); j++)
        {
            if (A[j] > A[j+1])
            {
                /* compare the two neighbors */
                /* swap a[j] and a[j+1]      */
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                swaps++;

                if ( verbose )
                {
                    show_result(A, len, j, (j+1));
                }

                done = 0;
            }
        }

        if (1 == done) break;
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

    swaps = bubble_sort(g_data, g_dataLen, verbose);

    printf("\n");
    printf("Number of swaps: %d\n", swaps);
    printf("\n");
    show_result(g_data, g_dataLen, -1, -1);
    printf("\n");

    return 0;
}

