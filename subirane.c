#include <stdio.h>
#include "subirane.h"


void change_smth(int* bla)
{
    *bla = 2;
}

void change_test1(int* arg)
{
    //arg = p
    arg = 10;
}

void change_test2(int** arg)
{
    //arg = &p
    **arg = 52;
    *arg = 100;   
}

void change_smth1(int rt)
{
    rt = 88;
}

int promenliva1 = 5;
int* p = &promenliva1;

int calc_sum(int sub1, int sub2)
{
    printf("promenliva1 = %d\n", promenliva1);
    change_smth(&promenliva1);
    printf("promenliva1 = %d\n", promenliva1);

    printf("%p\n", p);
    change_test1(p);
    printf("%p\n", p);
    change_test2(&p);
    printf("%p\n", p);

    printf("promenliva1 = %d\n", promenliva1);

    return sub1+sub2;  
}


