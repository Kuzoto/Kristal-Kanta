#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double RGBavg;
    for(int x = 0; x < height; x++)
    {
        for(int i = 0; i < width; i++)
        {
            RGBavg = image[x][i].rgbtRed + image[x][i].rgbtGreen + image[x][i].rgbtBlue;
            if (RGBavg == 50)
            {
                break;
            }
            image[x][i].rgbtRed = ceil(RGBavg/3);
            image[x][i].rgbtGreen = ceil(RGBavg/3);
            image[x][i].rgbtBlue = ceil(RGBavg/3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int RGBavg;
    for(int x = 0; x < height; x++)
    {
        for(int i = 0; i < width; i++)
        {
            double sepiaRed = .393 * image[x][i].rgbtRed + .769 * image[x][i].rgbtGreen + .189 * image[x][i].rgbtBlue;
            double sepiaGreen = .349 * image[x][i].rgbtRed + .686 * image[x][i].rgbtGreen + .168 * image[x][i].rgbtBlue;
            double sepiaBlue = .272 * image[x][i].rgbtRed + .534 * image[x][i].rgbtGreen + .131 * image[x][i].rgbtBlue;
            image[x][i].rgbtRed = sepiaRed;
            image[x][i].rgbtGreen = sepiaGreen;
            image[x][i].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int reflectW = width/2;
    for(int x = 0; x < height; x++)
    {
        for(int i = 0; i < reflectW; i++)
        {
            int originalRed = image[x][i].rgbtRed;
            int originalGreen = image[x][i].rgbtGreen;
            int originalBlue = image[x][i].rgbtBlue;
            image[x][i].rgbtRed = image[x][width - i].rgbtRed;
            image[x][i].rgbtGreen = image[x][width - i].rgbtGreen;
            image[x][i].rgbtBlue = image[x][width - i].rgbtBlue;
            image[x][width - i].rgbtRed = originalRed;
            image[x][width - i].rgbtGreen = originalGreen;
            image[x][width - i].rgbtBlue = originalBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int rowAvgR[height][width];
    int rowAvgG[height][width];
    int rowAvgB[height][width];
    for(int x = 0; x < height; x++)
    {
        for(int i = 0; i < width; i++)
        {
            int f = 0;
            for (int l = -1; l < 1; l++)
            {
                if (x == 0)
                {
                    l++;
                }
                for (int n = -1; n < 1; n++)
                {
                    if (i == 0)
                    {
                    n++;
                    }
                    rowAvgR[x][i] = rowAvgR[x][i] + image[x + l][i + n].rgbtRed;
                    rowAvgG[x][i] = rowAvgG[x][i] + image[x + l][i + n].rgbtGreen;
                    rowAvgB[x][i] = rowAvgB[x][i] + image[x + l][i + n].rgbtBlue;
                    f++;
                }
            }
            rowAvgR[x][i] = rowAvgR[x][i]/f;
            rowAvgG[x][i] = rowAvgG[x][i]/f;
            rowAvgB[x][i] = rowAvgB[x][i]/f;
            image[x][i].rgbtRed = rowAvgR[x][i];
            image[x][i].rgbtGreen = rowAvgG[x][i];
            image[x][i].rgbtBlue = rowAvgB[x][i];
        }

    }
    return;
}
