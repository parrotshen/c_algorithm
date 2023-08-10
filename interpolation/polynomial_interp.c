#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


/* Lagrange polynomial interpolation */
int polynomial_interp(
    double  inIndex[],
    double  inValue[],
    int     inLen,
    double  outIndex[],
    double  outValue[],
    int     outLen
)
{
    double p;
    int n;
    int m;
    int i;
    int j;
 

    if (inLen < 2)
    {
        printf("%s: wrong input data length %d\n", __func__, inLen);
        return -1;
    }

    for (n=0, m=0; n<outLen; n++)
    {
        if (outIndex[n] == inIndex[m])
        {
            outValue[n] = inValue[m];
            m++;
        }
        else
        {
            outValue[n] = 0;
            for (j=0; j<inLen; j++)
            {
                p = 1;
                for (i=0; i<inLen; i++)
                {
                    if (i != j)
                    {
                        /*         (xi - x1)   (xi - x2)   (xi - x3)
                        * l0(xi) = --------- * --------- * --------- ...
                        *          (x0 - x1)   (x0 - x2)   (x0 - x3)
                        */
                        p = p * (outIndex[n] - inIndex[i]) / (inIndex[j] - inIndex[i]);
                    }
                }
                /* p(xi) = f(x0)*l0(xi) + f(x1)l1(xi) + f(x2)l2(xi) + ... */
                outValue[n] = outValue[n] + p * inValue[j];
            }
        }
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

    polynomial_interp(x, y, 10, xi, yi, 19);
    
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

