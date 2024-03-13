// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary size
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain its hash value
    int index = hash(word);

    // Search the hash table at the location specified by the word’s hash value
    for (node *n = table[index]; n != NULL; n = n->next)
    {
        // Return true if the word is found
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
    }

    // Return false if no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        dictionary_size++;

        // Create new node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return 0;
        }

        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain a hash value
        int index = hash(word);

        // Insert node in the hash table
        n->next = table[index];
        table[index] = n;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
    }

    return true;
}
