#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint32_t rgbtBlue;
    uint32_t rgbtGreen;
    uint32_t rgbtRed;
} URGBTRIPLE;

void sum_neighbour_values(int *c, int x, int y, int height, int width, RGBTRIPLE image[height][width], URGBTRIPLE *sum);
RGBTRIPLE calculate_neighbours_avg(int x, int y, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE calculate_sobel_gradient(int i, int j, int height, int width, RGBTRIPLE temp[height][width]);
void get_neighbours_matrix(int i, int j, int height, int width, RGBTRIPLE temp[height][width], RGBTRIPLE neighbours[3][3]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Set red, green, and blue values to the average
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Capture image values to a temporary image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Reflect image horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][width - 1 - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Capture image values to a temporary image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Apply filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE avg = calculate_neighbours_avg(i, j, height, width, temp);
            image[i][j] = avg;
        }
    }
    return;
}

// Calculate average RGB values for a pixel and all its neighbours
RGBTRIPLE calculate_neighbours_avg(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    // Define counter, sum, and average variables
    int c = 0;
    URGBTRIPLE sum = {.rgbtRed = 0, .rgbtGreen = 0, .rgbtBlue = 0};
    RGBTRIPLE avg = {.rgbtRed = 0, .rgbtGreen = 0, .rgbtBlue = 0};

    // For each neighbour, get RBG values and add it to the sum
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            sum_neighbour_values(&c, x + i, y + j, height, width, image, &sum);
        }
    }

    // Calculate average
    avg.rgbtRed = round(sum.rgbtRed / (float) c);
    avg.rgbtGreen = round(sum.rgbtGreen / (float) c);
    avg.rgbtBlue = round(sum.rgbtBlue / (float) c);

    return avg;
}

void sum_neighbour_values(int *c, int x, int y, int height, int width, RGBTRIPLE image[height][width], URGBTRIPLE *sum)
{
    // Check if pixel is out of borders and ignore it
    if (x < 0 || x >= height)
        return;
    if (y < 0 || y >= width)
        return;

    // Add pixel values to the sum
    sum->rgbtRed += image[x][y].rgbtRed;
    sum->rgbtGreen += image[x][y].rgbtGreen;
    sum->rgbtBlue += image[x][y].rgbtBlue;

    *c += 1;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Capture image values to a temporary image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Apply filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE gradient = calculate_sobel_gradient(i, j, height, width, temp);
            image[i][j] = gradient;
        }
    }
    return;
}

RGBTRIPLE calculate_sobel_gradient(int i, int j, int height, int width, RGBTRIPLE temp[height][width])
{
    // Define kernels
    int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Define neighbours matrix
    RGBTRIPLE neighbours[3][3];
    get_neighbours_matrix(i, j, height, width, temp, neighbours);

    // Multiply kernel and neighbours matrices
    int Gx_r = 0, Gx_g = 0, Gx_b = 0, Gy_r = 0, Gy_g = 0, Gy_b = 0;

    for (int m = 0; m < 3; m++)
    {
        for (int n = 0; n < 3; n++)
        {
            Gx_r += neighbours[m][n].rgbtRed * Gx_kernel[m][n];
            Gx_g += neighbours[m][n].rgbtGreen * Gx_kernel[m][n];
            Gx_b += neighbours[m][n].rgbtBlue * Gx_kernel[m][n];

            Gy_r += neighbours[m][n].rgbtRed * Gy_kernel[m][n];
            Gy_g += neighbours[m][n].rgbtGreen * Gy_kernel[m][n];
            Gy_b += neighbours[m][n].rgbtBlue * Gy_kernel[m][n];
        }
    }

    // Calculate magnitude and cap it at 255
    int G_r = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
    int G_g = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
    int G_b = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));

    if (G_r > 255) G_r = 255;
    if (G_g > 255) G_g = 255;
    if (G_b > 255) G_b = 255;

    RGBTRIPLE G = {.rgbtRed = G_r, .rgbtGreen = G_g, .rgbtBlue = G_b};
    return G;
}

void get_neighbours_matrix(int i, int j, int height, int width, RGBTRIPLE temp[height][width], RGBTRIPLE neighbours[3][3])
{
    // Define black pixel
    RGBTRIPLE black = {.rgbtRed = 0, .rgbtGreen = 0, .rgbtBlue = 0};

    // Iterate over each neighbour
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            int new_i = i + x;
            int new_j = j + y;

            // Check if pixel is out of borders and assign it a black pixel
            if (new_i < 0 || new_i >= height || new_j < 0 || new_j >= width)
                neighbours[x + 1][y + 1] = black;

            // Otherwise, assign the corresponding pixel from the temporary image
            else
                neighbours[x + 1][y + 1] = temp[new_i][new_j];
        }
    }
}
