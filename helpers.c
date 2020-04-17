#include "helpers.h"
#include <math.h>

int cap255(double n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // averages the color intensity and then applies the same value to all the colors to get gray
            rgbGray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.000);

            image[j][i].rgbtBlue = rgbGray;
            image[j][i].rgbtGreen = rgbGray;
            image[j][i].rgbtRed = rgbGray;
        }
    }
}

// stops max value at 255 preventing overflow
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //use of a temporary array to swap values
    int temp[3];
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            temp[0] = image[j][i].rgbtBlue;
            temp[1] = image[j][i].rgbtGreen;
            temp[2] = image[j][i].rgbtRed;

            // swap pixels with the ones on the opposite side of the picture and viceversa
            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            image[j][width - i - 1].rgbtBlue = temp[0];
            image[j][width - i - 1].rgbtGreen = temp[1];
            image[j][width - i - 1].rgbtRed = temp[2];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{


    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rGx, gGx, bGx, rGy, gGy, bGy;
            rGx = gGx = bGx = rGy = gGy = bGy = 0;

            // Up
            if (i > 0)
            {
                rGy += -2 * image[i-1][j].rgbtRed;
                gGy += -2 * image[i-1][j].rgbtGreen;
                bGy += -2 * image[i-1][j].rgbtBlue;
            }
            // Down
            if (i < height - 1)
            {

                rGy += 2 * image[i+1][j].rgbtRed;
                gGy += 2 * image[i+1][j].rgbtGreen;
                bGy += 2 * image[i+1][j].rgbtBlue;
            }
            // Left
            if (j > 0)
            {
                rGx += -2 * image[i][j-1].rgbtRed;
                gGx += -2 * image[i][j-1].rgbtGreen;
                bGx += -2 * image[i][j-1].rgbtBlue;

            }
            // Right
             if (j < height - 1)
            {
                rGx += 2 * image[i][j+1].rgbtRed;
                gGx += 2 * image[i][j+1].rgbtGreen;
                bGx += 2 * image[i][j+1].rgbtBlue;

            }
            // Up left
            if (i >= 1 && j >= 1)
            {
                // Primeros tres valores, cambiando de signo muevo de lado el resultado
                rGx += -1 * image[i-1][j-1].rgbtRed;
                gGx += -1 * image[i-1][j-1].rgbtGreen;
                bGx += -1 * image[i-1][j-1].rgbtBlue;
                rGy += -1 * image[i-1][j-1].rgbtRed;
                gGy += -1 * image[i-1][j-1].rgbtGreen;
                bGy += -1 * image[i-1][j-1].rgbtBlue;
            }
            // Up right
            if (i > 0 && j < width - 1)
            {
                rGx += 1 * image[i-1][j+1].rgbtRed;
                gGx += 1 * image[i-1][j+1].rgbtGreen;
                bGx += 1 * image[i-1][j+1].rgbtBlue;
                rGy += -1 * image[i-1][j+1].rgbtRed;
                gGy += -1 * image[i-1][j+1].rgbtGreen;
                bGy += -1 * image[i-1][j+1].rgbtBlue;
            }
            // Bottom right
            if (i < height - 1  && j < width - 1)
            {
                rGx += 1 * image[i+1][j+1].rgbtRed;
                gGx += 1 * image[i+1][j+1].rgbtGreen;
                bGx += 1 * image[i+1][j+1].rgbtBlue;
                rGy += 1 * image[i+1][j+1].rgbtRed;
                gGy += 1 * image[i+1][j+1].rgbtGreen;
                bGy += 1 * image[i+1][j+1].rgbtBlue;
            }
            // Bottom left
            if (i < height - 1  && j > 0)
            {
                rGx += -1 * image[i+1][j-1].rgbtRed;
                gGx += -1 * image[i+1][j-1].rgbtGreen;
                bGx += -1 * image[i+1][j-1].rgbtBlue;
                rGy += 1 * image[i+1][j-1].rgbtRed;
                gGy += 1 * image[i+1][j-1].rgbtGreen;
                bGy += 1 * image[i+1][j-1].rgbtBlue;
            }

            // Compute result
            copy[i][j].rgbtRed = (int) cap255(sqrt((rGx*rGx)+(rGy*rGy)));
            copy[i][j].rgbtGreen = (int) cap255(sqrt((gGx*gGx)+(gGy*gGy)));
            copy[i][j].rgbtBlue = (int) cap255(sqrt((bGx*bGx)+(bGy*bGy)));
        }
    }

    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j] = copy[i][j];
            }
        }
    return;
}

int cap255(double n)
{
    int result = 0;

    if (n >= 255)
    {
        result = 255;
    }
    else if(n < 0)
    {
        result = 0;
    }
    else
    {
        result = (int) round(n);
    }
    return (result);
}