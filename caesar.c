#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//void caesarCipher(int argc, string argv[])
//{
//}

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int atoi(const char argv[1]);
        string k = argv[1]; //stores key
        int key = atoi(k);
        if (key < 1) //checks if key is greater than one
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
        string input = get_string("Plaintext: ");
        int inputLen = strlen(input); //gets plaintext length
        char cipher[100];
        int x = 0;
        int y = 0;
        int change = 0;
        printf("ciphertext: ");
        for (int i = 0; i < inputLen; i++) //enciphers each character
        {
            if (isalpha(input[i])) //checks if character is alphanumeric
            {
                if (isupper(input[i])) //checks if character is upper case and stores the case if true
                {
                    y = 2;
                    x = input[i] - 65;
                    change = (x + key) % 26; //keeps letters as letters
                    cipher[i] = change + 65;
                }
                else if (islower(input[i])) //checks if character is lower case and stores the case if true
                {
                    y = 1;
                    x = input[i] - 97;
                    change = (x + key) % 26; //keeps letters as letters
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
        printf("Usage: ./caesar key\n");
        exit(1);
    }
}
