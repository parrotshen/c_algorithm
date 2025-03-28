#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"

int main(int argc, char *argv[])
{
#if 0
    int A[3][3] = {
        {  6,  1,  1 },
        {  4, -2,  5 },
        {  2,  8,  7 }
    };
    int det; /* -306 */

    printf("A = \n");
    det = determinMatrix(A, 3, 3);

    printMatrix(A, 3, 3);
    printf("\n");
    printf("|A| = %d\n", det);

    return 0;
#else
    int A[4][4] = {
        {  5,  5,  6,  6 },
        {  3, -1, -2,  4 },
        { -4, -5,  2,  3 },
        {  1,  1,  1,  7 }
    };
    int det; /* -982 */

    det = determinMatrix(A, 4, 4);

    printf("A = \n");
    printMatrix(A, 4, 4);
    printf("\n");
    printf("|A| = %d\n", det);

    return 0;
#endif
}

