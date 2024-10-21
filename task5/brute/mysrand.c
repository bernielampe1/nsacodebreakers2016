#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void srand(unsigned int seed)
{
    void (*orig_srand)(unsigned int);
    orig_srand = dlsym(RTLD_NEXT, "srand");

    unsigned int new_seed = atoi(getenv("SEED"));
    if (new_seed % 1000 == 0) {
        printf("seed = %d\n", new_seed);
    }

    return (*orig_srand)(new_seed);
}
