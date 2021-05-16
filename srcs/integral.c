#include "proj.h"

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

    iters_f = 0;

    do {
        F_n = F_2n;
        n *= 2;
        h /= 2;
        sum_2n = (f(a) + f(b)) / 2;

        for (int i = 1; i < n; i++) {
            sum_2n += f(a + i * h);
        }

        F_2n = sum_2n * h;

        iters_f++;
    } while (fabs(F_n - F_2n) > eps);

    return F_2n;
}