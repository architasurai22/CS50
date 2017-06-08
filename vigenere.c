#include <stdlib.h>

int main(int argc, string argv[])
{
    string k = argv[1];
    int i;
    if(argc!=2)
    {
        printf("error\n");
        return 1;
    }
        for(i = 0;i < strlen(k);i++)
        if(!isalpha(k[i]))
        {
            printf("error\n");
            return 1;
        }
    
    
    printf("plaintext: ");
    string s = get_string();
    int counter = 0;
    int n = strlen(k),a;
    char c;
    
    for(i = 0;i < strlen(s);i++)
    {
        if(isalpha(s[i]))
        {
            if(isupper(s[i]))
            {
                c = k[counter%n];
                if(isupper(c))
                c = c - 'A';
                else
                c = c - 'a';
                a = c;
                s[i] = ((((s[i] -'A') + a) % 26) + 'A');
                counter++;
            }
            if(islower(s[i]))
            {
                c = k[counter%n];
                if(isupper(c))
                c = c - 'A';
                else
                c = c - 'a';
                a = c;
                s[i] = ((((s[i] -'a') + a) % 26) + 'a');
                counter++;
            }
        }
    }
    printf("ciphertext: %s\n",s);
    return 0;
}
