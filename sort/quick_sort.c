#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern.c"


int quick_sort(
    int  A[],
    int  len,
    int  left,
    int  right,
    int  verbose
)
{
    int swaps = 0;
    int temp;
    int pivot;
    int L;
    int R;

    if (left < right)
    {
        /* [1] select the pivot */
        pivot = left;
        L = left;
        R = right;

        /* [2] partition in two groups:
         *       less than pivot and greater than pivot
         */
        while (L != R)
        {
            while ((A[R] > A[pivot]) && (L < R))
            {
                R--;
            }

            while ((A[L] <= A[pivot]) && (L < R))
            {
                L++;
            }

            if (L < R)
            {
                temp = A[R];
                A[R] = A[L];
                A[L] = temp;
                swaps++;

                if ( verbose )
                {
                    show_result(A, len, L, R);
                }
            }
        }

        if (pivot != L)
        {
            temp = A[pivot];
            A[pivot] = A[L];
            A[L] = temp;
            swaps++;

            if ( verbose )
            {
                show_result(A, len, L, pivot);
            }

            pivot = L;
        }

        /* [3] recursive */
        swaps += quick_sort(A, len, left, (pivot - 1), verbose);
        swaps += quick_sort(A, len, (pivot + 1), right, verbose);
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

    swaps = quick_sort(
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

