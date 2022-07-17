#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            average = round(average);

            // Assign the average value to all RGB
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int left = 0;
    int right = width - 1;
    int temp = 0;

    for (int i = 0; i < height; i++)
    {
        left = 0;
        right = width - 1;

        while (left <= right)
        {
            // Swap red
            temp = image[i][left].rgbtRed;
            image[i][left].rgbtRed = image[i][right].rgbtRed;
            image[i][right].rgbtRed = temp;

            // Swap green
            temp = image[i][left].rgbtGreen;
            image[i][left].rgbtGreen = image[i][right].rgbtGreen;
            image[i][right].rgbtGreen = temp;

            // Swap blue
            temp = image[i][left].rgbtBlue;
            image[i][left].rgbtBlue = image[i][right].rgbtBlue;
            image[i][right].rgbtBlue = temp;

            left += 1;
            right -= 1;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float totalRed = 0;
    float totalGreen = 0;
    float totalBlue = 0;
    float total = 0;
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRed = 0;
            totalGreen = 0;
            totalBlue = 0;
            total = 0;

            // Re-assign the middle value based on the average in the surrounding
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        totalRed += image[i + k][j + l].rgbtRed;
                        totalGreen += image[i + k][j + l].rgbtGreen;
                        totalBlue += image[i + k][j + l].rgbtBlue;
                        total += 1;
                    }
                }
            }

            // Copy the values into a temporary 2D array
            temp[i][j].rgbtRed = round(totalRed / total);
            temp[i][j].rgbtGreen = round(totalGreen / total);
            temp[i][j].rgbtBlue = round(totalBlue / total);
        }
    }

    // Re-assign the values in image based on the values in temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    free(temp);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int matrixGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int matrixGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int gxRed = 0;
    int gxGreen = 0;
    int gxBlue = 0;
    int gyRed = 0;
    int gyGreen = 0;
    int gyBlue = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Calculate RGB for Gx and Gy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;
            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;

            // Calculate the Gx and Gy values based on the surrounding values multiply to the values in matrixGx and matrixGy
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        gxRed += (image[i + k][j + l].rgbtRed * matrixGx[1 + k][1 + l]);
                        gxGreen += (image[i + k][j + l].rgbtGreen * matrixGx[1 + k][1 + l]);
                        gxBlue += (image[i + k][j + l].rgbtBlue * matrixGx[1 + k][1 + l]);
                        gyRed += (image[i + k][j + l].rgbtRed * matrixGy[1 + k][1 + l]);
                        gyGreen += (image[i + k][j + l].rgbtGreen * matrixGy[1 + k][1 + l]);
                        gyBlue += (image[i + k][j + l].rgbtBlue * matrixGy[1 + k][1 + l]);
                    }
                }
            }

            // Sobel edge detection algorithm
            red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            // Store the final values into a temporary variable 
            temp[i][j].rgbtRed = (red < 255) ? red : 255;
            temp[i][j].rgbtGreen = (green < 255) ? green : 255;
            temp[i][j].rgbtBlue = (blue < 255) ? blue : 255;
        }
    }

    // Re-assign the values in image based on the values in temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    free(temp);
    return;
}
