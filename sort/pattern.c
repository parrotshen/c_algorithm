
#if 0
int g_data[] = {
     7, 10, 21, 29, 38, 40, 43, 48,
    55, 59, 60, 64, 72, 76, 87, 93
};
#else
int g_data[] = {
    38, 10, 76, 40, 29, 55,  7, 43,
    72, 59, 21, 64, 93, 48, 60, 87
};
#endif
int g_dataLen = (sizeof(g_data) / (sizeof(int)));

void show_result(int A[], int len, int c1, int c2)
{
    int i;

    for (i=0; i<len; i++)
    {
        if ((i == c1) || (i == c2))
        {
            printf("[1;32m");
        }
        printf("%2d ", A[i]);
        if ((i == c1) || (i == c2))
        {
            printf("[0m");
        }
    }
    printf("\n");
}

