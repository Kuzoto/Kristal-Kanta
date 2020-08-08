#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int main(void)
{
    long int num;
    bool valid = false;
    int i = 0;
    
    // Prompt the user for credit card number
    num = get_long("Please provide a valid credit card number: ");
    
    long int numS = num;
    long int pull = 10;
    
    while (num != 0)
    {
        num /= 10;
        i++;
    }


//  Check "Checksum" to see if the card is valid using Luhn's algorithim
// use mdolulo operator to obtain the last digit by dividing by 10


// Check to see if the card is from AMEX, VISA, MC, or Invalid
// by checking the card length and starting digits

    int test[i-1];
    num = numS;

    for(int x = 0; x < i; x++)
    {
        test[x] = num % 10;
        num /= 10;
    }
    printf("Test: %i\n", test[i]);
    int checkSum;
    for(int x = 0; x < i; x++)
    {
        if (x % 2 != 0)
        {
            checkSum = checkSum + test[x] * 2;
        }
        else
        {
            checkSum = checkSum + test[x];
        }
    }
    if (checkSum % 10 == 0)
    {
        valid = true;
    }


// Return result by printing credit card number and stating if its
// from AMEX, VISA, MC, or INVALID

    if (valid == true)
    {
        if (test[i-1] == 5)
        {
            printf("Number: %lu. Confirmed Valid\n", numS);
            printf("MASTERCARD\n");
        }
        else if (test[i-1] == 3)
        {
            printf("Number: %lu. Confirmed Valid\n", numS);
            printf("AMEX\n");
        }
        else if (test[i-1] == 4)
        {
            printf("Number: %lu. Confirmed Valid\n", numS);
            printf("VISA\n");
        }
        else
        {
            printf("Number: %lu. Can't Comfirm Valid\n Error Code: Spy\n", numS);
        }
    }
    else
    {
        printf("Number: %lu. Invalid\n", numS);
    }


}




