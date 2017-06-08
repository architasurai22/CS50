#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s;
    int i;
    char c;
    
    s = get_string();
    c = s[0];
    if(islower(c))
    printf("%c",toupper(c));
    else
    printf("%c",c);
    for(i = 1;i < strlen(s);i++)
    {
        if(s[i] == ' ')
        {
            c = s[i+1];
            if(islower(c))
            printf("%c",toupper(c));
            else
           printf("%c",c);
           i++;
        }
    }
    printf("\n");
}
