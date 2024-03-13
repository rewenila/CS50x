#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Declare a list of numbers
    int *list = malloc(3 * sizeof(int));
    if (list == NULL) // no memory left for list
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Declare temporary variable to store more numbers
    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL) // no memory left for tmp
    {
        free(list);
        return 1;
    }

    // Copy from list to tmp
    for (int i = 0; i < 3; i++) {
        tmp[i] = list[i];
    }
    tmp[3] = 4;

    // Point list to tmp
    free(list);
    list = tmp;

    for (int i = 0; i < 4; i++) {
        printf("%i\n", list[i]);
    }

    free(list);
    return 0;
}
