#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "subirane.h"

int main(int argc, char **argv) 
{

    printf("Start\n");
    int sub1 = argv[1][0]-0x30;
    int sub2 = atoi(argv[2]);
    printf("var1 = %d\n", sub1);
    printf("var2 = %d\n", sub2);
    //int res = calc_sum(sub1,sub2);

    int res;
    subirane sub;
    sub.sub1 = sub1;
    sub.sub2 = sub2;
    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, calc_sum, (void *)&sub);
    void * ressult = NULL;
    pthread_join(thread_id1, &ressult);



    printf("res = %d\n", (int *)ressult);
    return 0;
}