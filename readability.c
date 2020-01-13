#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double lNum = 0;
double wNum = 1;
double sNum = 0;
int i = 0;
int x = 0;
void gradeText();

void sortText()
{
    string text = get_string("Please Input Text to be Analyzed:\n");
    int spaces = 0;
        for(i = 0; spaces < 3; i++)
        {
            if(text[i] >= 'A' && text[i] <= 'Z')
            {
                lNum++;
                spaces = 0;
            } else if (text[i] == '?' || text[i] == '!' || text[i] == '.')
            {
                sNum++;
                spaces = 0;
            } else if (text[i] == '\0')
            {
                spaces = spaces + 1;
            } else if(text[i] >= 'a' && text[i] <= 'z')
            {
                lNum++;
                spaces = 0;
            } else if (text[i] == ' ')
            {
                wNum++;
                spaces = 0;
            } else {
                spaces = 0;
            }
        }
        gradeText();
}
void gradeText()
{
    float wAvg = 100 / wNum;
    float L = lNum * wAvg;
    float S = sNum * wAvg;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", index);
    } else if (index < 1) {
        printf("Before Grade 1\n");
    } else if (index >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Index Error: 42\nGrading has returned %f due to an error\n", index);
        string response = get_string("Would you like to exit the program or retry?(exit/restart)");
        if (response[0] == 'e' || response[0] == 'E') {
            exit(1);
        } else if (response[0] == 'r' || response[0] == 'R') {
            sortText();
        }
    }
    printf("Sentences: %.0f\n", sNum);
    printf("Words: %.0f\n", wNum);
    printf("Letters: %.0f\n", lNum);
}

int main(void)
{
    sortText();
}