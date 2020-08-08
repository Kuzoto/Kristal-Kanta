#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string userName = get_string("What is your name?\n"); //Prompts user for name
    printf("hello, %s\n", userName); //Receives input for string userName and prints it along with a hello
}
