#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("disarm = %d\n", 0xffffffff - 0x7b7c7bcf + 1);
    printf("unk cmd = %d\n", 0xffffffff - 0x7b7c7bd0 + 1);
    printf("unk cmd = %d\n", 0xffffffff - 0x7b967c7c + 1);

    return 0;
}
