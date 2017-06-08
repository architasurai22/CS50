#include <cs50.h>
#include<stdio.h>

int main(void)
{
    int n,i,j,k;
    
    do
    {
        printf("Enter a non-negetive integer number no greater than 23 : ");
        n = get_int();
    }
    while((n>23)||(n<0));
    for(i = 1;i <= n;i++)
    {
        for(j = 1;j <= n-i;j++)
        printf(" ");
        for(k = 1;k <= i+1;k++)
        printf("#");
        printf("\n");
    }
}
