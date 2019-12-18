#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float qCoin = 25;
float dCoin = 10;
float nCoin = 5;
float pCoin = 1;
int qAmt = 0;
int dAmt = 0;
int nAmt = 0;
int pAmt = 0;
float change;
int coinCount;
void changeCoins(void)
{
    for(; ;)
    {
        change = get_float("Change Owed: ");
        if (change < 0)
        {
            continue;
        } else {
            break;
        }
    }
    int coins = round(change * 100);
    for(; ;) {
        if (coins >= qCoin)
        {
            qAmt++;
            coins = coins - qCoin;
            if (coins <= 0) 
            {
                break;
            }
        } else if (coins >= dCoin && coins < qCoin) {
            dAmt++;
            coins = coins - dCoin;
            if (coins <= 0) 
            {
                break;
            }
        } else if (coins >= nCoin && coins < dCoin) {
            nAmt++;
            coins = coins - nCoin;
            if (change <= 0) 
            {
                break;
            }
        } else if (coins >= pCoin && coins < nCoin) {
            pAmt++;
            coins = coins - pCoin;
           if (coins <= 0) 
            {
                break;
            }
        } else {
            break;
        }
    }
    if (coins == 0) {
        coinCount = qAmt + dAmt + nAmt + pAmt;
        printf("Total Coins: %i\n", coinCount);
        printf("Quarters: %i\nDimes: %i\nNickels: %i\nPennies: %i\n", qAmt, dAmt, nAmt, pAmt);
    }
}
int main(void)
{
    changeCoins();
}
