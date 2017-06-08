#include <cs50.h>
#include<stdio.h>

int main(void)
{
    int minutes,bottles;
    printf("Minutes : ");
    minutes = get_int();
    bottles = minutes*192/16;
    printf("%d\n",bottles);
}
