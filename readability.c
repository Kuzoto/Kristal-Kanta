#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double lNum = 0;
double wNum = 1;
double sNum = 0;
int i = 0;

void gradeText();

void sortText()
{
    string text = get_string("Please Input Text to be Analyzed:\n");
    int n = strlen(text);
    int spaces = 0;
    int words = 0;
        for(i = 0; i < n; i++)
        {
            if(isalnum(text[i]))
            {
                lNum++;
                spaces = 0;
                words = 0;
            } else if (i > 0 && (text[i] == '?' || text[i] == '!' || text[i] == '.') && isalnum(text[i - 1]))
            {
                sNum++;
                spaces = 0;
                words = 0;
            } else if (text[i] == '\0')
            {
                spaces = spaces + 1;
            } else if (i < n - 1 && isspace(text[i]) && isalnum(text[i + 1]))
            {
                //if (words == 0) {
                    wNum++;
                    words++;
               // }
                spaces = 0;
            //} else if(text[i] == ',') {
               // lNum++;
                //spaces = 0;
            } else {
                spaces = 0;
                words = 0;
            }
        }
        gradeText();
}
void gradeText()
{

    double index = 0.0588 * (100 * lNum / wNum) - 0.296 * (100 * sNum / wNum) - 15.8;
    if (index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", round(index));
    } else if (index < 1)
    {
        printf("Before Grade 1\n");
    } else if (index >= 16)
    {
        printf("Grade 16+\n");
    } else
    {
        printf("Index Error: 42\nGrading has returned %f due to an error\n", index);
        string response = get_string("Would you like to exit the program or retry?(exit/restart)");
        if (response[0] == 'e' || response[0] == 'E') {
            exit(1);
        } else if (response[0] == 'r' || response[0] == 'R') {
            sortText();
        }
    }
    //printf("Sentences: %.0f\n", sNum);
    //printf("Words: %.0f\n", wNum);
    //printf("Letters: %.0f\n", lNum);
    //printf("L: %f\n", L);
    //printf("S: %f\n", S);
    //printf("Index: %f\n", index);
}

int main(void)
{
    sortText();
}