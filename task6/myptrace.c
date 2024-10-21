#define _GNU_SOURCE

#include <dlfcn.h>
#include <linux/ptrace.h>
#include <stdio.h>
#include <stdlib.h>

typedef long time_t;

long ptrace(unsigned request, pid_t pid, void *addr, void *data)
{
    return 0;
}
