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
    if (argc == 2) {
        //int atoi(const char *argv);
        string k = argv[1];
        int keylen = strlen(k);
        printf("%i\n", keylen);
        //int key = atoi(k);
        if (keylen < 26) {
        printf("Key must contain 26 characters\n");
        exit(1);
        }
        string input = get_string("Plaintext: ");
        int inputLen = strlen(input);
        char cipher[100];
        int x = 0;
        int y = 0;
        int change = 0;
        printf("ciphertext: ");
        for (int i = 0; i < inputLen; i++)
        {
            if (isalpha(input[i])) {
                if(isupper(input[i])) {
                    y = 2;
                    x = input[i] - 65;
                    if (islower(k[x])) {
                        change = k[x] - 97;
                    } else if (isupper(k[x])) {
                        change = k[x] - 65;
                    }
                    cipher[i] = change + 65;
                } else if (islower(input[i])) {
                    y = 1;
                    x = input[i] - 97;
                    if (islower(k[x])) {
                        change = k[x] - 97;
                    } else if (isupper(k[x])) {
                        change = k[x] - 65;
                    }
                    cipher[i] = change + 97;
                }
                if (y == 1) {
                    //cipher[i] = cipher[i] + 32;
                    printf("%c", cipher[i]);
                }
                else {
                    printf("%c", cipher[i]);
                }
            }
            else {
                printf("%c", input[i]);
            }
        }
        printf("\n");
        //atos(cipher);
    } else {
        printf("Key must contain 26 characters\n");
        exit(1);
    }
}