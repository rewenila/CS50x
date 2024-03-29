#include <stdio.h>

// void swap(int a, int b);
void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    // swap(x, y);
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

// passing by value -> there is no effect outside function scode
// void swap(int a, int b)
// {
//     int tmp = a;
//     a = b;
//     b = tmp;
// }

// passing by reference
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
