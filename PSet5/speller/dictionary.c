// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>




#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1300; // 1.3 * count of hash codes (recommended by the internet)

// Hash table
node *table[N];

// number of words in dictionary
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
   // copy original word to a temporary variable to not modify it
    char tmp_word[strlen(word + 1)];

    for(int i = 0; i <= strlen(word); i++)
    {
        tmp_word[i] = tolower(word[i]); //lower case to insure correct hash code
    }


    int hash_index = hash(tmp_word); // get hash index of word

    // travers linked list at the word's table index of the word
    for (node *cursor = table[hash_index]; cursor != NULL; cursor = cursor->next)
    {
        //printf("'%s' is in: %d\n", cursor->word, hash_index);
        if(strcmp(cursor->word, tmp_word) == 0)
        {
            //printf("'%s' is in the dictionary!\n", word);
            return true;
        }
    }

    //printf("%s is NOT in the dictionary!\n", word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)  // hash function: djb2 | Soursed from: shorturl.at/fhDXY
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++)) // *word++ is going to the next address in memory, where the next char in the string is stored
    {
        if (isupper(c))
        {
            c = c + 32;
        }

        hash = ((hash << 5) + hash) + c;

        hash = (int)((hash % 143091) % 1000);
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    int hash_index;

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("error opening file\n");
        return false;
    }

    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("dynamic memory: allocation error \n");
            return false;
        }
        strcpy(n->word, word);
        hash_index = hash(word);
        n->next = table[hash_index];
        table[hash_index] = n;
        word_count ++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    node *cursor;
    for(int i = 0; i < 1300; i++)
    {
        cursor = table[i];
        while(cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
