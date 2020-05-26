// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

int words;
//node *arrow = NULL;
//node *temp = malloc(sizeof(node));
// Hash table
node *table[HASHTABLE_SIZE] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int l = strlen(word);
    char *copy = malloc(l+1);

    for (int i = 0; i < l; i++)
    {
        copy[i] = tolower(word[i]);
    }

    copy[l] = '\0';

    int index = hash(copy);

    node *init = table[index];
    if (init)
    {
        node *arrow = init;

        while (arrow->next != NULL)
        {
            if (strcmp(copy, arrow->word) == 0)
            {
                free(copy);
                return true;
            }
            arrow = arrow->next;
        }

        if (strcmp(copy, arrow->word) == 0)
        {
            free(copy);
            return true;
        }
        arrow = arrow->next;
    }
    free(copy);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int n = strlen(word);
    unsigned int h = 0;
    for (int i = 0; i < n; i++)
        h = (h << 2) ^ word[i];
    return h % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *df = fopen(dictionary, "r");
    if (df == NULL)
    {
        printf("Could not open %s. Error Code: fish\n", dictionary);
        return false;
    }

    char buffer[LENGTH+2];;
    int i = 0;
    
    while (fgets(buffer, sizeof(buffer), df))
    {
        buffer[strlen(buffer) - 1] = '\0';

        node *temp = malloc(sizeof(node));

        strncpy(temp->word, buffer, LENGTH + 1);
    	temp->next = NULL;

    	int index = hash(buffer);
    	//printf("Buffer Index: %i\n", index);

    	if (table[index] == NULL)
    	{
    	    table[index] = temp;
    	}
    	else
    	{
    	    node *arrow = table[index];

    	    while (arrow->next != NULL)
    	    {
    	        arrow = arrow->next;
    	    }
    	    arrow->next = temp;
    	}
    	words++;
    }

    fclose(df);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {

        node *arrow = table[i];

        if (arrow)
        {
            node *temp = arrow->next;

            // free the current node
            //free(temp);
            free(arrow);
            // move the arrow to the next node
            arrow = temp;
        }
    }
return true;

}
