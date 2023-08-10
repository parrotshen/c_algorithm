#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


/* Linear interpolation */
int linear_interp(
    double  inIndex[],
    double  inValue[],
    int     inLen,
    double  outIndex[],
    double  outValue[],
    int     outLen
)
{
    double factor;
    int i;
    int j;
 

    if (inLen < 2)
    {
        printf("%s: wrong input data length %d\n", __func__, inLen);
        return -1;
    }

    /* Beginning extrapolation */
    i = 0;
    factor = (inValue[1] - inValue[0]) / (inIndex[1] - inIndex[0]);
    for ( ; i<outLen; )
    {
        if (outIndex[i] >= inIndex[0]) break;
        outValue[i] = inValue[0] - factor * (inIndex[0] - outIndex[i]);
        i++;
    }

    /* Main interpolation */
    j = 0;
    for ( ; i<outLen; )
    {
        if (outIndex[i] >= inIndex[j+1])
        {
            if ((j+1) == (inLen-1)) break;
            j++;
            factor = (inValue[j+1] - inValue[j]) / (inIndex[j+1] - inIndex[j]);
            continue;
        }
        outValue[i] = inValue[j] + factor * (outIndex[i] - inIndex[j]);
        i++;
    }

    /* Ending extrapolation */
    j = inLen -1;
    factor = (inValue[j] - inValue[j-1]) / (inIndex[j] - inIndex[j-1]);
    for ( ; i<outLen; )
    {
        outValue[i] = inValue[j] + factor * (outIndex[i] - inIndex[j]);
        i++;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    struct timespec ts1, ts2;
    unsigned long td;

    double x[10];
    double y[10];
    double xi[19];
    double yi[19];
    int i;
    int j;
    
    
    printf ("Inputs:\n");
    for (i=0, j=1; i<10; i++, j++)
    {
        x[i] = j;
        y[i] = sin( x[i] );
        printf ("%.1f  %+f\n", x[i], y[i]);
    }
    printf ("\n");

    memset(yi, 0, sizeof(double) * 19);
    for (i=0, j=0; i<9; i++)
    {
        xi[j++] = x[i];
        xi[j++] = x[i] + 0.5;
    }
    xi[j] = x[i];

    clock_gettime(CLOCK_MONOTONIC, &ts1);

    linear_interp(x, y, 10, xi, yi, 19);
    
    clock_gettime(CLOCK_MONOTONIC, &ts2);

    printf ("Outputs:\n");
    for (i=0; i<19; i++)
    {
        printf ("%.1f  %+f\n", xi[i], yi[i]);
    }

    td = ((ts2.tv_sec * 1000000000L) + ts2.tv_nsec) -
         ((ts1.tv_sec * 1000000000L) + ts1.tv_nsec);
    printf("\nTime spent: %lu ns\n\n", td);

    return 0;
}

