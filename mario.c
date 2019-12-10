#include <cs50.h>
#include <stdio.h>
void pyramid(void) {
    int h = get_int("Please Input Height: "); //Prompts user for pyramid height and width
    int n = h; //keeps track of number of blanks to print per row
    int x; //keeps track of current space in row
    for (int i = 0; i < h; i++) { //repeat row print until i reaches height
        n--; //decrease n by 1 each time a new row starts
        for (x = 0; x <= h; x++) { //repeat column print per row until x reaches height
            if (x > n) { //print # while x is > than n
                printf("#");
            } else { //if x is less than n print a blank space
                printf(" ");
            }
        }
        printf("\n"); //once row is printed begin new row
    }
}
int main(void)
{
pyramid();
}
