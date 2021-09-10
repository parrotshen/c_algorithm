#include <stdio.h>

int main(void)
{
    unsigned char *p;
    float a = 1.0;
    int n = 0;

    printf("sizeof( float ) = %d\n\n", sizeof(float));

    p = (unsigned char *)&a;
    do
    {
        printf(
            "%3d  %02x%02x%02x%02x  %e\n",
            n++,
            p[3], p[2], p[1], p[0],
            a
        );
        a = (a / 2);
    } while (a > 0);

    printf(
        "%3d  %02x%02x%02x%02x  %e\n\n",
        n,
        p[3], p[2], p[1], p[0],
        a
    );

    return 0;
}

