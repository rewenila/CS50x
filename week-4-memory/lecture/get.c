#include <stdio.h>

int main(void)
{
    // get int
    int n;
    printf("n: ");
    scanf("%i", &n);
    printf("n: %i\n", n);

    // get string
    // char *s;
    // printf("s: ");
    // scanf("%s", s);
    // printf("s: %s\n", s);
    // segmentation fault: core dumped

    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    // if more than 3 characters are provided by the user -> segmentation fault:
}
