#include"proj.h"

int iters_f;
struct option long_options[] = {
    {"print", 0, 0, 'p'},              //// do flag //
    {"iters", 0, 0, 'i'},              //// do flag ////
    {"iters-root", 0, 0, 'r'},         //// do flag ////
    {"iters-integral", 0, 0, 's'},     //// do flag ////
    {"test", 0, 0, 't'},               //// do flag //
    {"test-root", 0, 0, 'R'},          //// do flag //
    {"test-integral", 0, 0, 'S'},      //// do flag //
    {"help", 0, 0, 'h'},               //// do flag //
    {0, 0, 0, 0}
};

int main(int ac, char **av) {
    my_getopt(ac, av);

    if ((long_options[5].flag && long_options[6].flag) || long_options[4].flag) {
        test_root();
        test_integral();
        exit (0);
    } else if (long_options[5].flag) {
        test_root();
        exit(0);
    } else if (long_options[6].flag) {
        test_integral();
        exit(0);
    }


    //----------doing calculations and formating output----------//
    if (long_options[0].flag || long_options[1].flag || long_options[2].flag)
        printf("\n   -----------------------root-----------------------\n");

    double A = root(val_f1, val_f3, -3, -2, eps1, der1_f1, der1_f3, der2_f1, der2_f3);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f1 and f3 is %lf\n", A);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f1(x) - f3(x) = 0 : %d\n", iters_f);
    double B = root(val_f2, val_f3, -1, -0.0001, eps1, der1_f2, der1_f3, der2_f2, der2_f3);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f2 and f3 is %lf\n", B);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f2(x) - f3(x) = 0 : %d\n", iters_f);
    double C = root(val_f1, val_f2, 1, 2, eps1, der1_f1, der1_f2, der2_f1, der2_f2);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f1 and f2 is %lf\n", C);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f1(x) - f2(x) = 0 : %d\n", iters_f);

    if (long_options[0].flag || long_options[1].flag || long_options[2].flag)
        printf("   -----------------------root-----------------------\n");


    if (long_options[1].flag || (long_options[2].flag && long_options[3].flag && long_options[0].flag))
        printf("\n   **************************************************\n");


    if (long_options[1].flag || long_options[3].flag)
        printf("\n   ---------------------integral---------------------\n");

    double sq_f1 = integral(val_f1, A, C, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f1 : %d\n", iters_f);
    double sq_f2 = integral(val_f2, B, C, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f2 : %d\n", iters_f);
    double sq_f3 = integral(val_f3, A, B, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f3 : %d\n", iters_f);

    if (long_options[1].flag || long_options[3].flag)
        printf("   ---------------------integral---------------------\n\n");


    double res = sq_f2 + sq_f3 - sq_f1;
    printf("   The square of area bounded by three curves : %lf\n", res);

    return 0;
}