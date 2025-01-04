#include <stdio.h>

int main(void)
{
    unsigned char *p;
    double a;
    int e;

    printf("\n");
    printf(" e     %ld-bit            value\n", (sizeof(double) * 8));
    p = (unsigned char *)&a;

    e = -1023;  /* min. value */
    p[7] = (((e + 1023) >> 4) & 0x7F);
    p[6] = ((((e + 1023) & 0xF) << 4) | 0x00);
    p[5] = 0x00;
    p[4] = 0x00;
    p[3] = 0x00;
    p[2] = 0x00;
    p[1] = 0x00;
    p[0] = 0x01;
    printf(
        "%d  %02x%02x%02x%02x%02x%02x%02x%02x  %e\n",
        e,
        p[7], p[6], p[5], p[4],
        p[3], p[2], p[1], p[0],
        a
    );

    e = 1023;  /* max. value */
    p[7] = (((e + 1023) >> 4) & 0x7F);
    p[6] = ((((e + 1023) & 0xF) << 4) | 0x0F);
    p[5] = 0xFF;
    p[4] = 0xFF;
    p[3] = 0xFF;
    p[2] = 0xFF;
    p[1] = 0xFF;
    p[0] = 0xFF;
    printf(
        " %d  %02x%02x%02x%02x%02x%02x%02x%02x  %e\n",
        e,
        p[7], p[6], p[5], p[4],
        p[3], p[2], p[1], p[0],
        a
    );
    printf("\n");

    return 0;
}

