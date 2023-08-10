#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


/* Cubic spline interpolation */
int cspline_interp(
    double  inIndex[],
    double  inValue[],
    int     inLen,
    double  outIndex[],
    double  outValue[],
    int     outLen
)
{
    double *a, *b, *c, *d = inValue;
    double *A, *h, *l, *u, *z;
    double delta;
    int i;
    int j;


    if (inLen < 3)
    {
        printf("%s: wrong input data length %d\n", __func__, inLen);
        return -1;
    }

    a = malloc(inLen * sizeof(double));
    b = malloc(inLen * sizeof(double));
    c = malloc(inLen * sizeof(double));
    A = malloc(inLen * sizeof(double));
    h = malloc(inLen * sizeof(double));
    l = malloc(inLen * sizeof(double));
    u = malloc(inLen * sizeof(double));
    z = malloc(inLen * sizeof(double));

    /* [1] */
    for (i=0; i<=(inLen-2); i++)
    {
        h[i] = inIndex[i+1] - inIndex[i];
    }

    /* [2] */
    for (i=1; i<=(inLen-2); i++)
    {
        A[i] = 3 * (d[i+1] - d[i]) / h[i] - 3 * (d[i] - d[i-1]) / h[i-1];
    }

    /* [3] */
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    /* [4] */
    for (i=1; i<=(inLen-2); i++)
    {
        l[i] = 2 * (inIndex[i+1] - inIndex[i-1]) - h[i-1] * u[i-1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i-1] * z[i-1]) / l[i];
    }

    /* [5] */
    l[inLen-1] = 1;
    z[inLen-1] = 0;
    b[inLen-1] = 0;

    /* [6] */
    for (j=(inLen-2); j>=0; j--)
    {
        b[j] = z[j] - u[j] * b[j+1];
        a[j] = (b[j+1] - b[j]) / (3 * h[j]);
        c[j] = (d[j+1] - d[j]) / h[j] - h[j] * (b[j+1] + 2 * b[j]) / 3;
    }

    /* [7] S(xi) = ai * x^3 + bi * x^2 + ci * x + di */
    outValue[0] = d[0];
    for (i=1, j=0; i<outLen; i++)
    {
        if (outIndex[i] == inIndex[j+1])
        {
            j = j + 1;
            outValue[i] = d[j];
        }
        else
        {
            delta = outIndex[i] - inIndex[j];
            outValue[i]
             = a[j] * pow(delta, 3) + b[j] * pow(delta, 2) + c[j] * delta + d[j];
        }
    }

    free( a );
    free( b );
    free( c );
    free( A );
    free( h );
    free( l );
    free( u );
    free( z );
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

    cspline_interp(x, y, 10, xi, yi, 19);

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

