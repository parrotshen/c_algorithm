#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pattern.c"


#define DEBUG 1

#if DEBUG
int g_iteration = 0;
#endif


int binary_search(int A[], int start, int end, int target)
{
    int index = -1;
    int mid;

    if (start > end) return -1;

    mid = (((end - start) >> 1) + start);
    #if DEBUG
    printf(" A[%2d..%2d..%2d] -> %2d\n", start, mid, end, A[mid]);
    g_iteration++;
    #endif

    if (target > A[mid])
    {
        start = (mid + 1);
        index = binary_search(A, start, end, target);
    }
    else if (target < A[mid])
    {
        end = (mid - 1);
        index = binary_search(A, start, end, target);
    }
    else
    {
        #if DEBUG
        printf(" found at A[%d]\n", mid);
        #endif
        index = mid;
    }

    return index;
}


int main(int argc, char *argv[])
{
    int target = 0;
    int index;

    show_data();

    if (argc > 1)
    {
        target = atoi( argv[1] );
    }
    else
    {
        printf("Usage: binary_search TARGET\n\n");
        return 0;
    }

    index = binary_search(g_data, 0, (g_dataLen - 1), target);

    #if DEBUG
    printf(" iteration(s) ... [1;36m%d[0m\n\n", g_iteration);
    #endif

    if (index >= 0)
    {
        printf(
            "Target [1;33m%d[0m is at A[[1;31m%d[0m]\n\n",
            target,
            index
        );
    }
    else
    {
        printf("ERR: cannot find %d\n\n", target);
    }

    return 0;
}

