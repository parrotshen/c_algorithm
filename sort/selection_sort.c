#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern.c"


int selection_sort(int A[], int len, int verbose)
{
    int swaps = 0;
    int temp;
    int min;
    int i;
    int j;

    for (i=0; i<(len-1); i++)
    {
        min = i;

        for (j=(i+1); j<len; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            temp = A[min];
            A[min] = A[i];
            A[i] = temp;
            swaps++;

            if ( verbose )
            {
                show_result(A, len, i, min);
            }
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

    swaps = selection_sort(g_data, g_dataLen, verbose);

    printf("\n");
    printf("Number of swaps: %d\n", swaps);
    printf("\n");
    show_result(g_data, g_dataLen, -1, -1);
    printf("\n");

    return 0;
}

