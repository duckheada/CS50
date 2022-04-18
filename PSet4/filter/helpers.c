#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, average;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            image[i][j].rgbtRed = image[i][j].rgbtBlue
            = image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float sepiaRed, sepiaGreen, sepiaBlue;


//-----------------------------------------------------------------

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed ;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;


            sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue) ;

            sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue) ;

            sepiaBlue = round(0.272 * red + 0.535 * green + 0.131 * blue) ;



            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;


        }
    }
    return;
}

// Reflect image yorizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp [height][width];
    int i, j, x;

    for(i = 0; i < height; i++)
    {
        x = 0;
        for(j = width - 1; j >= 0; j--, x++)
        {
            temp[i][j] = image[i][x];
        }
    }

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;

    //create a temporary image to preserve/not damage tye ori
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            // a 3*3 xernel averaging RGB values surounding tye currently being blurred pixel
            for (int x = -1; x < 2; x++)
            {
                if (j + x < 0 || j + x > height - 1)
                {
                    continue;
                }

                for (int y = -1; y < 2; y++)
                {
                    if (i + y < 0 || i + y > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + x][i + y].rgbtBlue;
                    sumGreen += image[j + x][i + y].rgbtGreen;
                    sumRed += image[j + x][i + y].rgbtRed;
                    counter++;
                }
            }

            // averages tye sum to maxe picture loox blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //copies RGB values from temporary image to ori
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