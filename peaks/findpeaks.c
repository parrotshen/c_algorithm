#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct _tPeaks
{
    double value;
    int    index;
} tPeaks;

int findPeaks(double in[], int inLen, tPeaks out[], int outLen)
{
    /*    peak
    *      ^--+
    *      |  |
    *    +-+  |
    *    |    |
    * ---+    +---
    */
    double deltaL;
    double deltaR;
    int num = 0;
    int peak;
    int i;

    deltaR = in[1] - in[0];
    for (i=1; i<(inLen-1); i++)
    {
        peak = i; /* peak candidate */
        deltaL = deltaR;
        deltaR = in[i+1] - in[i];
        while ((deltaR == 0) && ((++i) < (inLen-1)))
        {
            deltaR = in[i+1] - in[i];
        }

        if ((deltaL > 0) && (deltaR < 0))
        {
            out[num].value = in[peak];
            out[num].index = peak;
            num++;
            if (num >= outLen) return num;
        }
    }

    return num;
}


int main(int argc, char *argv[])
{
    tPeaks peaks[50];
    int peaksLen;

    struct timeval tv;
    double data[50];
    int i;
    int j;


    for (i=0; i<50; i++)
    {
        gettimeofday(&tv, NULL);
        srand( (unsigned int)tv.tv_usec );
        data[i] = ((rand() % 199) - 99);
    }

    peaksLen = findPeaks(data, 50, peaks, 50);

    printf("%d peaks:\n", peaksLen);
    for (i=0, j=0; i<50; i++)
    {
        if ((i != 0) && ((i % 10) == 0)) printf("\n");
        if (peaks[j].index == i)
        {
            printf("[30;46m%+3d[0m  ", (int)data[i]);
            j++;
        }
        else
        {
            printf("%+3d  ", (int)data[i]);
        }
    }
    printf("\n\n");

    return 0;
}
