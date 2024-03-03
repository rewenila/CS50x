#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // Counter of JPEG files
    int count = 0;

    // Allocate memory for file name
    char *filename = malloc(8 * sizeof(char));

    // Create file to store the image
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if the 512 byte block is the beggining of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Format name of JPEG file
            sprintf(filename, "%03i.jpg", count);

            // Check if it is the first JPEG found
            if (count == 0)
            {
                // Open file
                img = fopen(filename, "w");
            }
            else
            {
                // Close former file and open new one
                fclose(img);
                img = fopen(filename, "w");
            }

            // Write to file
            fwrite(buffer, 1, 512, img);

            count++;
        }
        else
        {
            // If already found a JPEG, keep writing to it, this is the next 512 block of the image
            if (count > 0)
                fwrite(buffer, 1, 512, img);
        }
    }

    // Free memory for filename
    free(filename);

    // Close remaining files
    fclose(img);
    fclose(card);
}
