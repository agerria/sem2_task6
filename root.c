#include "funcs.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

#define eps1 0.0001
#define eps2 0.00001

static struct option long_options[] = {
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

//----------keeps track of the requested parameter----------//
int iters = 0;          

//----------finding the root of the equation by the combined method----------//
double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double),
            double (*dg)(double), double (*ddf)(double), double (*ddg)(double)) {
    iters = 0;

    while (fabs(a - b) > 2 * eps) {
        if ((f(a) - g(a)) * (ddf(a) - ddg(a)) < 0) {
            a -= (f(a) - g(a)) * (a - b) / (f(a) - g(a) - f(b) + g(b));
        } else {
            a -= (f(a) - g(a)) / (df(a) - dg(a));
        }
        if ((f(b) - g(b)) * (ddf(b) - ddg(b)) < 0) {
            b -= (f(b) - g(b)) * (b - a) / (f(b) - g(b) - f(a) + g(a));
        } else {
            b -= (f(b) - g(b)) / (df(b) - dg(b));
        }

        iters++;
    }

    return (a + b) / 2;
}

//----------finding the integral of a function by the trapezoid method----------//
double integral(double (*f)(double), double a, double b, double eps) {
    int n = 10;
    double h = (b - a) / n;
    double sum_n = (f(a) + f(b)) / 2;
    
    for (int i = 1; i < n; i++) {
        sum_n += f(a + i * h);
    }

    double F_n = sum_n * h;
    double sum_2n = sum_n;
    double F_2n = F_n;

    iters = 0;

    do {
        F_n = F_2n;
        n *= 2;
        h /= 2;
        sum_2n = (f(a) + f(b)) / 2;

        for (int i = 1; i < n; i++) {
            sum_2n += f(a + i * h);
        }

        F_2n = sum_2n * h;

        iters++;
    } while (fabs(F_n - F_2n) > eps);

    return F_2n;
}

//----------console option "help" message----------//
void help(void) {
    printf("Usage: ./proj [options]\n");
    printf("Options:\n");

    printf("   %-20s", "-p");
    printf("Prints the value of the x-coordinate.\n");
    printf("   --%-18s\n", long_options[0].name);

    printf("   %-20s", "-i");
    printf("Prints the number of iterations for calculating the root and integral.\n");
    printf("   --%-18s\n", long_options[1].name);

    printf("   --%-18s", long_options[2].name);
    printf("Prints the number of iterations for calculating the root.\n");

    printf("   --%-18s", long_options[3].name);
    printf("Prints the number of iterations for calculating the integral.\n");

    printf("   %-20s", "-t");
    printf("Uses to test the root and integral functions.\n");
    printf("   --%-18s\n", long_options[4].name);

    printf("   --%-18s", long_options[5].name);
    printf("Uses to test the root function.\n");

    printf("   --%-18s", long_options[6].name);
    printf("Uses to test the integral function.\n");

    printf("   %-20s", "-h");
    printf("Display this information.\n");
    printf("   --%-18s\n", long_options[7].name);

    exit(0);
}

//----------console option "test_root"----------//
void test_root(void) {
    char inp1[3], inp2[3];
    double left, right, acc;
    double res;

    printf("\nRoot function testing...\n");
    printf("Input: first function(f1/f2/f3), second function(f1/f2/f3), left border, right border, accuracy\n");
    scanf("%2s %2s %lf %lf %lf", inp1, inp2, &left, &right, &acc);

    if (inp1[1] == '1' && inp2[1] == '2' || inp1[1] == '2' && inp2[1] == '1') {
        res = root(val_f1, val_f2, left, right, acc, der1_f1, der1_f2, der2_f1, der2_f2);
    } else if (inp1[1] == '1' && inp2[1] == '3' || inp2[1] == '3' && inp1[1] == '1') {
        res = root(val_f1, val_f3, left, right, acc, der1_f1, der1_f3, der2_f1, der2_f3);
    } else {
        res = root(val_f2, val_f3, left, right, acc, der1_f2, der1_f3, der2_f2, der2_f3);
    }

    printf("\n   --------------------------------------------------\n");
    printf("\n   Root of %s(x) - %s(x) = 0 is %lf\n", inp1, inp2, res);
    if (long_options[1].flag || long_options[2].flag) {
        printf("\n   Steps: %d\n", iters);
    }
    printf("\n   --------------------------------------------------\n");
}

//----------console option "test_integral"----------//
void test_integral(void) {
    char inp[3];
    double left, right, acc;
    double res;

    printf("\nIntegral function testing...\n");
    printf("Input: function(f1/f2/f3), left border, right border, accuracy\n");
    scanf("%2s %lf %lf %lf", inp, &left, &right, &acc);

    if (inp[1] == '1') {
        res = integral(val_f1, left, right, eps2);
    } else if (inp[1] == '2') {
        res = integral(val_f2, left, right, eps2);
    } else {
        res = integral(val_f3, left, right, eps2);
    }

    printf("\n   --------------------------------------------------\n");
    printf("\n   Integral of %s(x) from %lf to %lf is %lf\n", inp, left, right, res);
    if (long_options[1].flag || long_options[2].flag) {
        printf("\n   Steps: %d\n", iters);
    }
    printf("\n   --------------------------------------------------\n");
}

int main(int ac, char **av) {
    int opt;
    int option_index = 0;

    while ((opt = getopt_long(ac, av, "piht", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'p':
                long_options[0].flag = (int *)1;
                break;
            case 'i':
                long_options[1].flag = (int *)1;
                break;
            case 'h':
                long_options[7].flag = (int *)1;
                help();
                break;
            case 't':
                long_options[4].flag = (int *)1;
                break;
            default:
                if (option_index != 0)
                    long_options[option_index].flag = (int *)1;
        }
    }

    if (long_options[5].flag) {
        test_root();
        exit(0);
    } else if (long_options[6].flag) {
        test_integral();
        exit(0);
    } else if (long_options[5].flag && long_options[6].flag || long_options[4].flag) {
        test_root();
        test_integral();
        exit (0);
    }



    if (long_options[0].flag || long_options[1].flag || long_options[2].flag)
        printf("\n   -----------------------root-----------------------\n");

    double A = root(val_f1, val_f3, -3, -2, eps1, der1_f1, der1_f3, der2_f1, der2_f3);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f1 and f3 is %lf\n", A);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f1(x) - f3(x) = 0 : %d\n", iters);
    double B = root(val_f2, val_f3, -1, -0.0001, eps1, der1_f2, der1_f3, der2_f2, der2_f3);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f2 and f3 is %lf\n", B);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f2(x) - f3(x) = 0 : %d\n", iters);
    double C = root(val_f1, val_f2, 1, 2, eps1, der1_f1, der1_f2, der2_f1, der2_f2);
    if (long_options[0].flag)
        printf("   The x-coordinate of the intersection point of functions f1 and f2 is %lf\n", C);
    if (long_options[1].flag || long_options[2].flag)
        printf("   Steps to find the root of an equation f1(x) - f2(x) = 0 : %d\n", iters);

    if (long_options[0].flag || long_options[1].flag || long_options[2].flag)
        printf("   -----------------------root-----------------------\n");


    if (long_options[1].flag || long_options[2].flag && long_options[3].flag && long_options[0].flag)
        printf("\n   **************************************************\n");


    if (long_options[1].flag || long_options[3].flag)
        printf("\n   ---------------------integral---------------------\n");

    double sq_f1 = integral(val_f1, A, C, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f1 : %d\n", iters);
    double sq_f2 = integral(val_f2, B, C, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f2 : %d\n", iters);
    double sq_f3 = integral(val_f3, A, B, eps2);
    if (long_options[1].flag || long_options[3].flag)
        printf("   Steps to find the integral of a function f3 : %d\n", iters);

    if (long_options[1].flag || long_options[3].flag)
        printf("   ---------------------integral---------------------\n");


    double res = sq_f2 + sq_f3 - sq_f1;
    printf("\n   The square of area bounded by three curves : %lf\n", res);

    return 0;
}

// gcc -m32 root.c asmsrcs/funcs.a -I asmsrcs/ -lm