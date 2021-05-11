#ifndef PROJ_H
#define PROJ_H

#include "funcs.h"
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#define eps1 0.0001
#define eps2 0.00001

//----------keeps track of the requested parameter----------//
extern int iters_f;      

extern struct option long_options[];

double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double),
            double (*dg)(double), double (*ddf)(double), double (*ddg)(double));
double integral(double (*f)(double), double a, double b, double eps);
void help(void);
void test_root(void);
void test_integral(void);
void my_getopt(int ac, char **av);

#endif