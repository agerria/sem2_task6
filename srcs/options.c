#include "proj.h"

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

    if ((inp1[1] == '1' && inp2[1] == '2') || (inp1[1] == '2' && inp2[1] == '1')) {
        res = root(val_f1, val_f2, left, right, acc, der1_f1, der1_f2, der2_f1, der2_f2);
    } else if ((inp1[1] == '1' && inp2[1] == '3') || (inp2[1] == '3' && inp1[1] == '1')) {
        res = root(val_f1, val_f3, left, right, acc, der1_f1, der1_f3, der2_f1, der2_f3);
    } else if ((inp1[1] == '2' && inp2[1] == '3') || (inp2[1] == '3' && inp1[1] == '2')) {
        res = root(val_f2, val_f3, left, right, acc, der1_f2, der1_f3, der2_f2, der2_f3);
    } else {
        printf("\n   \033[0;31mBAD INPUT\033[0m \n");
        return ;
    }

    printf("\n   --------------------------------------------------\n");
    printf("\n   Root of %s(x) - %s(x) = 0 is %lf\n", inp1, inp2, res);
    if (long_options[1].flag || long_options[2].flag) {
        printf("\n   Steps: %d\n", iters_f);
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
    scanf("%3s %lf %lf %lf", inp, &left, &right, &acc);

    if (inp[1] == '1') {
        res = integral(val_f1, left, right, eps2);
    } else if (inp[1] == '2') {
        res = integral(val_f2, left, right, eps2);
    } else if (inp[1] == '3') {
        res = integral(val_f3, left, right, eps2);
    } else {
        printf("\n   \033[0;31mBAD INPUT\033[0m \n");
        return ;
    }

    printf("\n   --------------------------------------------------\n");
    printf("\n   Integral of %s(x) from %lf to %lf is %lf\n", inp, left, right, res);
    if (long_options[1].flag || long_options[2].flag) {
        printf("\n   Steps: %d\n", iters_f);
    }
    printf("\n   --------------------------------------------------\n");
}

//----------parsing options from command line----------//
void my_getopt(int ac, char **av) {
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
}