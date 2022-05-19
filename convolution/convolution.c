#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
* Convolution:
*           M
*   y[n] = SUM( h[k] * x[n - k] )
*          k=0
*     k = 0, 1, 2 ... M
*/


int convolution(
    double  h[],
    int     hLen,
    double  x[],
    int     xLen,
    double  y[]
)
{
#define DEBUG 0
    int yLen = (hLen + xLen - 1);
    int n;
    int k;
    int i;

    /*
    *  y[0] = h[0]*x[0]
    *  y[1] = h[0]*x[1] + h[1]*x[0]
    *  y[2] = h[0]*x[2] + h[1]*x[1] + h[2]*x[0]
    *   ...
    *  y[n] = h[0]*x[n] + h[1]*x[n-1] + h[2]*x[n-2] + ... + h[k]*x[n-k]
    */
    for (n=0; n<yLen; n++)
    {
        #if DEBUG
        printf("[%d]", n);
        #endif
        y[n] = 0;
        for (k=0; k<hLen; k++)
        {
            i = (n - k);
            if ((i >= 0) && (i < xLen))
            {
                #if DEBUG
                printf(" %.1lf*%.1lf", h[k], x[i]);
                #endif
                y[n] += (h[k] * x[i]);
            }
        }
        #if DEBUG
        printf("\n");
        #endif
    }
    #if DEBUG
    printf("\n");
    #endif

    return yLen;
}

int main(int argc, char *argv[])
{
    double h[3] = {
        3, 2, 1
    };
    double x[5] = {
        1, 2, 2, 1, 1
    };
    double y[8];
    int n;
    int i;


    n = convolution(
            h,
            sizeof(h)/sizeof(double),
            x,
            sizeof(x)/sizeof(double),
            y
        );

    for (i=0; i<n; i++)
    {
        printf("%.1lf ", y[i]);
    }
    printf("\n");

    return 0;
}

