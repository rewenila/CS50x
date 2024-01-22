#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string encrypy(string text, string key);

int main(int argc, string argv[])
{
    // Check if usage is correct
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate the key
    string key = argv[1];
    int n = strlen(key);

    // Check key length
    if (n != 26)
    {
        printf("Key must countain 26 characters\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        // Check for non-alphabetic characters
        if (!isalpha(key[i]))
        {
            printf("Key must only countain letters\n");
            return 1;
        }

        // Check for repeated characters
        for (int j = 0; j < n; j++)
        {
            if (i != j && toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must countain each letter exactly once\n");
                return 1;
            }
        }
    }

    // Prompt user for plain text
    string text = get_string("plaintext: ");

    // Encrypt text
    string cipher = encrypy(text, key);

    // Print encrypted text
    printf("ciphertext: %s\n", cipher);
}

string encrypy(string text, string key)
{
    int n = strlen(text);
    string cipher = text;

    for (int i = 0; i < n; i++)
    {
        // Checks if character is a letter
        if (isalpha(text[i]))
        {
            int index = toupper(text[i]) - 'A';

            // Encrypt character preserving the case
            if (islower(text[i]))
            {
                cipher[i] = tolower(key[index]);
            }
            else
            {
                cipher[i] = toupper(key[index]);
            }
        }
        // Keep non-alphabetic character unchanged
        else
        {
            cipher[i] = text[i];
        }
    }
    return cipher;
}
