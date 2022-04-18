#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

//PSET 2: Caesar

int main(int argc, string kaka[])
{

//-------------VALIDATE KEY--------------------------------

    string keyStr = kaka[1];
    long long key = atoi(kaka[1]);


    for (int i = 0; i < strlen(keyStr); i++)
    {
        // printf("char at i: %c\n", keyStr[i]);

        if (!isdigit(keyStr[i]))
        {

            printf("A valid key is a digit. \n");
            return 0;

        }
        else
            {
            }

           if (key == 0 || argc != 2)
           {
                 printf("Usage: ./sb key. \n");
           }

    }
    printf("%lli\n", key);

//-------------Encipher--------------------------------

    string txt;
    // txt's upper-cass alphabetical index, txt's lower-cass alphabetical index, ciphered text's index
    int txtUprIdx, txtLwrIdx, ciphIndex;

    txt = get_string("Enter text to encipher: ");

    //keeping a copy of the original index
        char *oriTxt = malloc(strlen(txt) + 1);
        if (oriTxt != NULL)
        {
            strcpy(oriTxt, txt);
        }


    for (int j = 0; j < strlen(txt); j++)
    {
        ciphIndex = 0;
        // printf("char at i: %c\n", keyStr[i]);

        if (isalpha(txt[j])) //check if alphabetic
        {
                if(isupper(txt[j]))
                {
                    txtUprIdx = txt[j] - 65;
                    ciphIndex = (txtUprIdx + key) % 26;
                    txt[j] = 65 + ciphIndex;
                    // printf("ciph upper: %c\n", txt[j]);
                }
                else if (islower(txt[j]))
                {
                    txtLwrIdx = txt[j] - 97;
                    ciphIndex = (txtLwrIdx + key) % 26;
                    txt[j] = 97 + ciphIndex;
                    // printf("ciph lower: %c\n", txt[j]);
                }
        }

    }

    printf("Enciphered: %s\n", txt);

    return 0;
}





 /*

printf("\n", );

------------

if ()
{
    printf();
}
else
{
    printf();
}

-------------

for (int i = 0; i < ssLen; i++)
{
    printf();
}
-------------
if (isupper(txt[i]))
{
    printf("is upper\n");
}
else
{
    printf("is lower\n");
}


87654678 + f@#%k th3em haters :P

 */