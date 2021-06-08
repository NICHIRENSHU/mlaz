#include <stdio.h>
#include "subirane.h"
#include <stdlib.h>

int main(int argc, char **argv) {

printf("Start\n");
int sub1 = argv[1][0]-0x30;
int sub2 = atoi(argv[2]);
printf("var1 = %d\n", sub1);
printf("var2 = %d\n", sub2);

int res = calc_sum(sub1,sub2);

    printf("res = %d\n", res);
    return 0;
}