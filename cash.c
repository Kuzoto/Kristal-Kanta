#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float qCoin = 25; //Quarter value
float dCoin = 10; //Dime value
float nCoin = 5; //Nickel value
float pCoin = 1; //Penny value
int qAmt = 0; //Quarter amount
int dAmt = 0; //Dime amount
int nAmt = 0; //Nickel amount
int pAmt = 0; //Penny amount
float change; //Change owed input storage
int coinCount; //Total Amount of Coins
void changeCoins(void) //See how many of each coin and total amount of coins you would need to give to the customer
{
    for (; ;)
    {
        change = get_float("Change Owed: "); //Prompt for change owed input
        if (change < 0) //Check if input is valid
        {
            continue;
        } 
        else 
        {
            break;
        }
    }
    int coins = round(change * 100); //Change float to an int
    for (; ;)
    {
        if (coins >= qCoin) // check if coins is greater than or equal to a Quarter
        {
            qAmt++; //Increment quarter amount
            coins = coins - qCoin; //subtract quarter value for change owed
            if (coins <= 0) 
            {
                break;
            }
        } 
        else if (coins >= dCoin && coins < qCoin) //check if change owed is less than a quarter and greater than or equal to a dime
        {
            dAmt++; //increment dime amount
            coins = coins - dCoin; //subtract change owed by dime value
            if (coins <= 0) 
            {
                break;
            }
        } 
        else if (coins >= nCoin && coins < dCoin) //check if change owed is less than a dime and greater than or equal to a nickel
        {
            nAmt++; //increment nickel amount
            coins = coins - nCoin; //subtract change owed by nickel value
            if (change <= 0) 
            {
                break;
            }
        } 
        else if (coins >= pCoin && coins < nCoin) //check if change owed is less than a nickel and greater than or equal to a penny
        {
            pAmt++; //increment penny amount
            coins = coins - pCoin; //Subtract change owed by penny value
            if (coins <= 0) //check if change owed equals 0
            {
                break;
            }
        } 
        else
        {
            break;
        }
    }
    if (coins == 0)
    {
        coinCount = qAmt + dAmt + nAmt + pAmt; //Get coin total
        printf("Total Coins: %i\n", coinCount); //Print coin total
        printf("Quarters: %i\nDimes: %i\nNickels: %i\nPennies: %i\n", qAmt, dAmt, nAmt, pAmt); //Print individual coin amounts
    }
}
int main(void)
{
    changeCoins(); //run function to find coin amount
}
