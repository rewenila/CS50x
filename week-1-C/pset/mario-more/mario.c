#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;

    // Asks for pyramid height
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1);

    // Print pyramid
    for (int i = 1; i <= h; i++)
    {
        // Print spaces
        for (int j = h - 1; j >= i; j--)
        {
            printf(" ");
        }

        // Print first pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Print gap between pyramids
        printf("  ");

        // Print second pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Go to new line
        printf("\n");
    }
}
