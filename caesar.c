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
    if (argc == 2) {
        int atoi(const char argv[1]);
        string k = argv[1];
        int key = atoi(k);
        if (key < 1) {
        printf("Usage: ./caesar key\n");
        }
        string input = get_string("Plaintext: ");
        int inputLen = strlen(input);
        char cipher[100];
        int x = 0;
        int y = 0;
        int change = 0;
        printf("Ciphertext: ");
        for (int i = 0; i < inputLen; i++)
        {
            if (isalpha(input[i])) {
                if(isupper(input[i])) {
                    y = 2;
                } else if (islower(input[i])) {
                    y = 1;
                }
                x = input[i] - 65;
                change = (x + key) % 26;
                cipher[i] = change + 65;
                if (y == 1) {
                    cipher[i] = cipher[i] + 32;
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
        printf("Usage: ./caesar key\n");
    }
}
