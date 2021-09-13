#include <stdio.h>

int main(void)
{
    unsigned char *p;
    float a;
    int e;

    printf("\n");
    printf(" e    %d-bit    value\n", (sizeof(float) * 8));
    p = (unsigned char *)&a;

    e = -127;  /* min. value */
    p[3] = (((e + 127) >> 1) & 0x7F);
    p[2] = ((((e + 127) & 0x1) << 7) | 0x00);
    p[1] = 0x00;
    p[0] = 0x01;
    printf(
        "%d  %02x%02x%02x%02x  %e\n",
        e,
        p[3], p[2], p[1], p[0],
        a
    );

    e = 127;  /* max. value */
    p[3] = (((e + 127) >> 1) & 0x7F);
    p[2] = ((((e + 127) & 0x1) << 7) | 0x7F);
    p[1] = 0xFF;
    p[0] = 0xFF;
    printf(
        " %d  %02x%02x%02x%02x  %e\n",
        e,
        p[3], p[2], p[1], p[0],
        a
    );
    printf("\n");

    return 0;
}

