#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define BUFFER_SIZE 512 

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open card.\n");
        return 1;
    }
    
    // create buffer
    unsigned char buffer[BUFFER_SIZE];
    
    // filename counter
    int x = 0;
    
    FILE *img = NULL; 
    
    // check if we've found a jpeg yet or not
    int i = 0; //false
    
    // go through cardfile until there aren't any blocks left
    while (fread(buffer, BUFFER_SIZE, 1, f) == 1)
    {
        // read first 4 bytes of buffer and see if jpg signature using bitwise on last byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //create filename variable
            char filename[8];
            if (i == 1)
            {
                //opens new file in an append
                fclose(img);
                sprintf(filename, "%03i.jpg", x);
                img = fopen(filename, "a");
                x++;
            }
            else
            {
                //opens new file in a write
                i = 1;
                sprintf(filename, "%03i.jpg", x);
                img = fopen(filename, "w");
                x++;
            }
        }
        if (i == 1)
        {
            //writes to new file after first jpg is found
            fwrite(&buffer, BUFFER_SIZE, 1, img);
        }
    }
    //close both files
    fclose(f);
    fclose(img);
        
    return 0;
}
