#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//void caesarCipher(int argc, string argv[])
//{
//}

int main(int argc, char *argv[])
{
    if (argc == 2) //checks if two arguments are present
    {
        //int atoi(const char *argv);
        string k = argv[1];
        int keylen = strlen(k); //gets keylength
        for (int t = 0; t < keylen; t++) //checks if all key characters are unique and alphanumeric
        {
            if (!isalpha(k[t])) //checks if key character is alphanumeric
            {
                printf("Key must contain 26 LETTERS\n");
                exit(1);
            }
            else
            {
                for (int r = 0; r < keylen; r++) //checks if each key is unique
                {
                    if (k[t] == k[r] && t != r) //checks if the current key character is unique
                    {
                        printf("Key must contain 26 Unique Letters\n");
                        exit(1);
                    }
                }
            }
        }
        //int key = atoi(k);
        if (keylen < 26) //checks if key is 26 characters long
        {
            printf("Key must contain 26 characters\n");
            exit(1);
        }
        string input = get_string("Plaintext: ");
        int inputLen = strlen(input); //gets length of plaintext
        char cipher[100];
        int x = 0;
        int y = 0;
        int change = 0;
        printf("ciphertext: ");
        for (int i = 0; i < inputLen; i++) //enciphers plaintext
        {
            if (isalpha(input[i]))  //checks if character is alphanumeric
            {
                if (isupper(input[i])) //checks for and stores upper case
                {
                    y = 2;
                    x = input[i] - 65;
                    if (islower(k[x])) //checks if key character is lowercase
                    {
                        change = k[x] - 97;
                    }
                    else if (isupper(k[x])) //checks if key character is uppercase
                    {
                        change = k[x] - 65;
                    }
                    cipher[i] = change + 65;
                }
                else if (islower(input[i])) //checks for and stores lowercase
                {
                    y = 1;
                    x = input[i] - 97;
                    if (islower(k[x]))
                    {
                        change = k[x] - 97;
                    }
                    else if (isupper(k[x]))
                    {
                        change = k[x] - 65;
                    }
                    cipher[i] = change + 97;
                }
                if (y == 1)
                {
                    //cipher[i] = cipher[i] + 32;
                    printf("%c", cipher[i]);
                }
                else
                {
                    printf("%c", cipher[i]);
                }
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        printf("\n");
        //atos(cipher);
    }
    else
    {
        printf("Key must contain 26 characters\n");
        exit(1);
    }
}