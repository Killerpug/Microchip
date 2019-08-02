#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int r_number;
int main()
{
        srand(10);//intialize random seed
         r_number=rand();
    printf("your number is : \n", r_number);

}
