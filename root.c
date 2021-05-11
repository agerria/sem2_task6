#include "proj.h"

//----------finding the root of the equation by the combined method----------//
double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double),
            double (*dg)(double), double (*ddf)(double), double (*ddg)(double)) {
    iters_f = 0;

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

        iters_f++;
    }

    return (a + b) / 2;
}

// gcc -m32 root.c asmsrcs/funcs.a -I asmsrcs/ -lm