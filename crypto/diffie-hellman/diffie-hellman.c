#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void print_mpz(char *name, mpz_t z)
{
    char *str = mpz_get_str(0, 10, z);

    printf("%s = %s\n", name, str);
    free( str );
}

/*
*  g = 3, p = 17, a = 54, b = 24, A = 15, B = 16, K = 1
*
*  (3 ^ 54) mod 17 = 15
*  (3 ^ 24) mod 17 = 16
*
*  (3 ^ (54 x 24)) mod 17 = 1
*/
int main(int argc, char **argv)
{
    mpz_t g, p, a, b, A, B, K_A, K_B;
    mpz_t C, K_C;

    mpz_init_set_ui(g, 3);
    mpz_init_set_ui(p, 17);
    mpz_init_set_ui(a, 54);
    mpz_init_set_ui(b, 24);
    mpz_init( A );
    mpz_init( B );
    mpz_init( C );
    mpz_init( K_A );
    mpz_init( K_B );
    mpz_init( K_C );

    printf("Initialization ...\n");
    print_mpz("g", g);
    print_mpz("p", p);
    print_mpz("a", a);
    print_mpz("b", b);
    printf("\n");

    /* A = (g ^ a) mod p */
    printf("[1] Alice computes\n");
    mpz_powm(A, g, a, p);
    print_mpz("A", A);
    printf("\n");

    printf("[2] Send to Bob\n");
    print_mpz("p", p);
    print_mpz("g", g);
    print_mpz("A", A);
    printf("\n");

    /* B = (g ^ b) mod p */
    /* K = (A ^ b) mod p */
    printf("[3] Bob computes\n");
    mpz_powm(B, g, b, p);
    mpz_powm(K_B, A, b, p);
    print_mpz("B", B);
    print_mpz("K_B", K_B);
    printf("\n");

    printf("[4] Send to Alice\n");
    print_mpz("p", p);
    print_mpz("g", g);
    print_mpz("B", B);
    printf("\n");

    /* K = (B ^ a) mod p */
    printf("[5] Alice computes\n");
    mpz_powm(K_A, B, a, p);
    print_mpz("K_A", K_A);
    printf("\n");

    /* K = (g ^ (a * b)) mod p */
    printf("[6] Verify ...\n");
    mpz_mul(C, a, b);
    mpz_powm(K_C, g, C, p);
    print_mpz("C", C);
    print_mpz("K_C", K_C);
    printf("\n");

    mpz_clear( K_C );
    mpz_clear( K_B );
    mpz_clear( K_A );
    mpz_clear( C );
    mpz_clear( B );
    mpz_clear( A );
    mpz_clear( b );
    mpz_clear( a );
    mpz_clear( p );
    mpz_clear( g );

    return 0;
}
