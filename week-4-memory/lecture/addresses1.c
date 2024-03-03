#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n; // declaring a pointer with *

    printf("%p\n", p);
    printf("%i\n", *p); // going to a pointer with * and showing what is there
}
