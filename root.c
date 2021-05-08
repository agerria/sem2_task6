#include "funcs.h"
#include <math.h>
#include <stdio.h>

#define eps1 0.0001
#define eps2 0.00001

double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double),
            double (*dg)(double), double (*ddf)(double), double (*ddg)(double)) {

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
    }

    return (a + b) / 2;
}

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

    do {
        F_n = F_2n;
        n *= 2;
        h /= 2;
        sum_2n = (f(a) + f(b)) / 2;

        for (int i = 1; i < n; i++) {
            sum_2n += f(a + i * h);
        }

        F_2n = sum_2n * h;
    } while (fabs(F_n - F_2n) > eps);

    return F_2n;
}

int main(void)
{
    double res;
    double square;

    // printf("F1 and F2\n");
    // res = root(val_f1, val_f2, 1, 2, eps1, der1_f1, der1_f2, der2_f1, der2_f2);
    // printf("%lf\n", res);

    // printf("F2 and F3\n");
    // res = root(val_f2, val_f3, -1, -0.0001, eps1, der1_f2, der1_f3, der2_f2, der2_f3);
    // printf("%lf\n", square);

    // printf("F1 and F3\n");
    // res = root(val_f1, val_f3, -3, -2, eps1, der1_f1, der1_f3, der2_f1, der2_f3);
    // printf("%lf\n", res);

    square = integral(val_f2, 3, 6, eps2);
    printf("%lf\n", square);
    return 0;
}

// gcc -m32 root.c asmsrcs/funcs.a -I asmsrcs/ -lm