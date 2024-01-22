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
        for (int j = h - 1; j >= i; j--)
        {
            printf(" ");
        }

        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
