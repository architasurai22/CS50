#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("error\n");
        return 1;
    }
    int i;
    printf("plaintext: ");
    string s = get_string();
    string k = argv[1];
    int n = atoi(k);
    n = n%26;
    
    for(i = 0;i < strlen(s);i++)
    {
        if(isalpha(s[i]))
        {
            if(isupper(s[i]))
            {
                s[i] = ((((s[i] -'A') + n) % 26) + 'A');
            }
                
            if(islower(s[i]))
            {
                s[i] = ((((s[i] -'a') + n) % 26) + 'a');
            }
        }
    }

    printf("ciphertext: %s\n",s);
    return 0;
}
