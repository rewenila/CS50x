#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_number_letters(string text);
int get_number_words(string text);
int get_number_sentences(string text);
int calculate_coleman_liau_index(int number_letters, int number_words, int number_sentences);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Calculate number of letters and words
    int number_letters = get_number_letters(text);
    int number_words = get_number_words(text);
    int number_sentences = get_number_sentences(text);

    // Calculate Coleman-Liau index
    int index = calculate_coleman_liau_index(number_letters, number_words, number_sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

int get_number_letters(string text)
{
    int number_letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            number_letters++;
        }
    }
    return number_letters;
}

int get_number_words(string text)
{
    int number_spaces = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            number_spaces++;
        }
    }
    return number_spaces + 1;
}

int get_number_sentences(string text)
{
    int number_punctuation_marks = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            number_punctuation_marks++;
        }
    }
    return number_punctuation_marks;
}

int calculate_coleman_liau_index(int number_letters, int number_words, int number_sentences)
{
    double L = number_letters / (number_words / 100.0);
    double S = number_sentences / (number_words / 100.0);

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
