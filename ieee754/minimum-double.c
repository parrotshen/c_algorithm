#include <stdio.h>

int main(void)
{
    unsigned char *p;
    double a = 1.0;
    int n = 0;

    printf("sizeof( double ) = %d\n\n", sizeof(double));

    p = (unsigned char *)&a;
    do
    {
        printf(
            "%4d  %02x%02x%02x%02x%02x%02x%02x%02x  %e\n",
            n++,
            p[7], p[6], p[5], p[4],
            p[3], p[2], p[1], p[0],
            a
        );
        a = (a / 2);
    } while (a > 0);

    printf(
        "%4d  %02x%02x%02x%02x%02x%02x%02x%02x  %e\n\n",
        n,
        p[7], p[6], p[5], p[4],
        p[3], p[2], p[1], p[0],
        a
    );

    return 0;
}

