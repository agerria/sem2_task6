#include <stdio.h>
#include <getopt.h>

static struct option long_options[] = {
    {"print", 0, 0, 'p'},
    {"iters", 0, 0, 'i'},
    {"iters-root", 0, 0, 'r'},
    {"iters-integral", 0, 0, 's'},
    {"test", 0, 0, 't'},
    {"test-root", 0, 0, 'R'},
    {"test-integral", 0, 0, 'S'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
};


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
                break;
            case 't':
                long_options[4].flag = (int *)1;
                break;
            default:
                if (option_index != 0)
                    long_options[option_index].flag = (int *)1;
        }
    }
    // for (int i = 0; i < 9; i++)
    //     if (long_options[i].flag)
    //         printf("i = %d, print_flag = 1\n", i);
    return 0;
}