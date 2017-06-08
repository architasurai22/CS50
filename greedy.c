#include <cs50.h>
#include<stdio.h>

int main(void)
{
    float change;
    int cents,count=0;
    printf("Change : ");
    change = get_float();
    cents = change*100;
    while(cents)
    {
        if(cents>25)
        {
            cents = cents - 25;
            count++;
        }
        else if(cents>10)
        {
            cents = cents - 10;
            count++;
        }
        else if(cents>5)
        {
            cents = cents - 5;
            count++;
        }
        else
        {
            cents = cents - 1;
            count++;
        }
    }
    printf("%d\n",count);
}
