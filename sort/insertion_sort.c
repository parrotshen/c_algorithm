#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern.c"


int insertion_sort(int A[], int len, int verbose)
{
    int swaps = 0;
    int key;
    int i;
    int j;

    for (i=1; i<len; i++)
    {
        key = A[i];
        j = (i - 1);

        while ((j >= 0) && (A[j] > key))
        {
            A[j+1] = A[j];

            if ( verbose )
            {
                show_result(A, len, j, (j+1));
            }

            swaps++;
            j--;
        }

        if (A[j+1] != key)
        {
            A[j+1] = key;
            swaps++;

            if ( verbose )
            {
                show_result(A, len, i, (j+1));
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

    swaps = insertion_sort(g_data, g_dataLen, verbose);

    printf("\n");
    printf("Number of swaps: %d\n", swaps);
    printf("\n");
    show_result(g_data, g_dataLen, -1, -1);
    printf("\n");

    return 0;
}

