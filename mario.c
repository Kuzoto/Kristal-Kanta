#include <cs50.h>
#include <stdio.h>

void pyramid(void)
{
    int h = get_int("Please Input Height: "); //Prompts user for pyramid height and width
    for (; ;) 
    {
        if (h > 0 && h < 9) 
        {
            break;
        } 
        else if (h < 1) 
        {
            h = get_int("Error Please Input Positive Height: ");
            continue;
        } 
        else if (h > 8) 
        {
            h = get_int("Error Please Input Height Less Than 9: ");
            continue;
        } 
        else 
        {
            h = get_int("Error Please Input Int: ");
            continue;
        }
    }
    int n = h; //keeps track of number of blanks to print per row
    int x; //keeps track of current space in row
    for (int i = 0; i < h; i++) //repeat row print until i reaches height
    {
        n--; //decrease n by 1 each time a new row starts
        int t = h - n; //declares t as h subtracted by current n value
        for (x = 0; x <= h; x++) //repeat column print per row until x reaches height
        {
            if (x > n) //print # while x is > than n
            {
                printf("#");
            } 
            else if (x < n) //if x is less than n print a blank space
            {
                printf(" ");
            }
        }
        printf(" "); //prints space
        printf(" "); //prints space
        for (int r = 0; r <= h; r++) //runs mirror row print until r = 8 or exitted
        {
            if (r < t) //checks if r is less than t and if it is prints a #
            {
                printf("#");
            }
            else if (r > t) //checks if r > than t if it is it exits loop
            {
                break;
            }
        }
        printf("\n"); //once row is printed begin new row
    }
}
int main(void)
{
    pyramid();
}

