#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //caculating average
            int pixelTotal = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float pixelAverage = (float)pixelTotal / 3.0;
            int roundedPixelAverage = round(pixelAverage);

            //checking if over maximum color value
            if (roundedPixelAverage > 255)
            {
                roundedPixelAverage = 255;
            }

            //changing value of the pixel to the average
            image[i][j].rgbtBlue = roundedPixelAverage;//pixelAverage;
            image[i][j].rgbtGreen = roundedPixelAverage;//pixelAverage;
            image[i][j].rgbtRed = roundedPixelAverage;//pixelAverage;

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagetemp[height][width];
    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            imagetemp[i][j] = image[i][width - j - 1];

        }
    }
    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;

        }
    }





    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //printf("HI");
    //initializing variables
    float counter = 0;
    RGBTRIPLE imagetemp[height][width];
    //caculating average

    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            //initializing variables
            float totalBlue = 0;
            float totalGreen = 0;
            float totalRed = 0;
            counter = 0;

            //middle of box
            //adding to totalBlue, totalGreen, and totalRed. These act as accumalators.
            totalBlue = totalBlue + image[i][j].rgbtBlue;
            totalGreen = totalGreen + image[i][j].rgbtGreen;
            totalRed = totalRed + image[i][j].rgbtRed;

            //counter keeps track of how many times we have added to totalBlue, totalGreen, and totalRed, so we can divide the sum later.
            counter += 1;

            //left of box
            if ((j - 1) >= 0) // if ((j-1) >= 0)
            {
                totalBlue = totalBlue + image[i][j - 1].rgbtBlue;
                totalGreen = totalGreen + image[i][j - 1].rgbtGreen;
                totalRed = totalRed + image[i][j - 1].rgbtRed;
                counter += 1;
            }

            //right of box
            if (j + 1 < width) //if ((j+1) >= 0)
            {
                totalBlue = totalBlue + image[i][j + 1].rgbtBlue;
                totalGreen = totalGreen + image[i][j + 1].rgbtGreen;
                totalRed = totalRed + image[i][j + 1].rgbtRed;
                counter += 1;

            }

            //top middle of box
            if ((i - 1) >= 0)
            {
                totalBlue = totalBlue + image[i - 1][j].rgbtBlue;
                totalGreen = totalGreen + image[i - 1][j].rgbtGreen;
                totalRed = totalRed + image[i - 1][j].rgbtRed;
                counter += 1;
            }

            //top left of box
            if (((i - 1) >= 0) && ((j - 1)) >= 0)
            {
                totalBlue = totalBlue + image[i - 1][j - 1].rgbtBlue;
                totalGreen = totalGreen + image[i - 1][j - 1].rgbtGreen;
                totalRed = totalRed + image[i - 1][j - 1].rgbtRed;
                counter += 1;
            }

            //top right of box
            if ((((i - 1) >= 0) && (j + 1) < width))
            {
                totalBlue = totalBlue + image[i - 1][j + 1].rgbtBlue;
                totalGreen = totalGreen + image[i - 1][j + 1].rgbtGreen;
                totalRed = totalRed + image[i - 1][j + 1].rgbtRed;
                counter += 1;
            }

            //bottom midle of box
            if ((i + 1) < height)
            {
                totalBlue = totalBlue + image[i + 1][j].rgbtBlue;
                totalGreen = totalGreen + image[i + 1][j].rgbtGreen;
                totalRed = totalRed + image[i + 1][j].rgbtRed;
                counter += 1;
            }

            //bottom left of box
            if ((((i + 1) < height) && ((j - 1)) >= 0)) // if((i+1) <= (width-1) && (j-1) >= 0)
            {
                totalBlue = totalBlue + image[i + 1][j - 1].rgbtBlue;
                totalGreen = totalGreen + image[i + 1][j - 1].rgbtGreen;
                totalRed = totalRed + image[i + 1][j - 1].rgbtRed;
                counter += 1;
            }

            //bottom right of box
            if ((i + 1) < height && (j + 1) < width)
            {
                totalBlue = totalBlue + image[i + 1][j + 1].rgbtBlue;
                totalGreen = totalGreen + image[i + 1][j + 1].rgbtGreen;
                totalRed = totalRed + image[i + 1][j + 1].rgbtRed;
                counter += 1;
            }

            //adding and dividing caculate average

            float averageBlue = totalBlue / counter;
            float averageGreen = totalGreen / counter;
            float averageRed = totalRed / counter;


            //changing color blue to average
            imagetemp[i][j].rgbtBlue = round(averageBlue);

            //changing color green to average
            imagetemp[i][j].rgbtGreen = round(averageGreen);

            //changing color red to average
            imagetemp[i][j].rgbtRed = round(averageRed);


            //if(imagetemp[i][j].rgbtRed != image[i][j].rgbtRed || imagetemp[i][j].rgbtGreen != image[i][j].rgbtGreen || imagetemp[i][j].rgbtBlue != image[i][j].rgbtBlue){
            //    printf("Different!!!\n\n");
            //}


        }

    }


    //printf("____________________________________________________________________________________________________");

    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            //printf("Before: temp: %i, image: %i\n", imagetemp[i][j].rgbtBlue, image[i][j].rgbtBlue);
            if (imagetemp[i][j].rgbtBlue <= 255)
            {
                image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
            }
            else if (imagetemp[i][j].rgbtBlue < 0)
            {
                image[i][j].rgbtBlue = 0;

            }
            else
            {
                image[i][j].rgbtBlue = 255;

            }


            if (imagetemp[i][j].rgbtGreen <= 255)
            {
                image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;

            }
            else if (imagetemp[i][j].rgbtGreen < 0)
            {
                image[i][j].rgbtGreen = 0;

            }
            else
            {
                image[i][j].rgbtGreen = 255;

            }


            if (imagetemp[i][j].rgbtRed <= 255)
            {
                image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;

            }
            else if (imagetemp[i][j].rgbtRed < 0)
            {
                image[i][j].rgbtRed = 0;

            }
            else
            {
                image[i][j].rgbtRed = 255;

            }

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagetemp[height][width];
    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            //initializing variables
            float totalBlueGx = 0;
            float totalGreenGx = 0;
            float totalRedGx = 0;

            float totalBlueGy = 0;
            float totalGreenGy = 0;
            float totalRedGy = 0;


            //Gx kernel

            //middle of box
            //adding to totalBlue, totalGreen, and totalRed. These act as accumalators.
            totalBlueGx = totalBlueGx + (image[i][j].rgbtBlue * 0);
            totalGreenGx = totalGreenGx + (image[i][j].rgbtGreen * 0);
            totalRedGx = totalRedGx + (image[i][j].rgbtRed * 0);


            //left of box
            if ((j - 1) >= 0)
            {
                totalBlueGx = totalBlueGx + (image[i][j - 1].rgbtBlue * -2);
                totalGreenGx = totalGreenGx + (image[i][j - 1].rgbtGreen * -2);
                totalRedGx = totalRedGx + (image[i][j - 1].rgbtRed * -2);

            }

            //right of box
            if ((j + 1) < width)
            {
                totalBlueGx = totalBlueGx + (image[i][j + 1].rgbtBlue * 2);
                totalGreenGx = totalGreenGx + (image[i][j + 1].rgbtGreen * 2);
                totalRedGx = totalRedGx + (image[i][j + 1].rgbtRed * 2);

            }

            //top middle of box
            if ((i - 1) >= 0)
            {
                totalBlueGx = totalBlueGx + (image[i - 1][j].rgbtBlue * 0);
                totalGreenGx = totalGreenGx + (image[i - 1][j].rgbtGreen * 0);
                totalRedGx = totalRedGx + (image[i - 1][j].rgbtRed * 0);

            }

            //top left of box
            if (((i - 1) >= 0) && ((j - 1)) >= 0)
            {
                totalBlueGx = totalBlueGx + (image[i - 1][j - 1].rgbtBlue * -1);
                totalGreenGx = totalGreenGx + (image[i - 1][j - 1].rgbtGreen * -1);
                totalRedGx = totalRedGx + (image[i - 1][j - 1].rgbtRed * -1);

            }

            //top right of box
            if ((((i - 1) >= 0) && ((j + 1)) < width))
            {
                totalBlueGx = totalBlueGx + (image[i - 1][j + 1].rgbtBlue * 1);
                totalGreenGx = totalGreenGx + (image[i - 1][j + 1].rgbtGreen * 1);
                totalRedGx = totalRedGx + (image[i - 1][j + 1].rgbtRed * 1);

            }

            //bottom midle of box
            if ((i + 1) < height)
            {
                totalBlueGx = totalBlueGx + (image[i + 1][j].rgbtBlue * 0);
                totalGreenGx = totalGreenGx + (image[i + 1][j].rgbtGreen * 0);
                totalRedGx = totalRedGx + (image[i + 1][j].rgbtRed * 0);
            }

            //bottom left of box
            if ((((i + 1) < height) && ((j - 1)) >= 0)) // if((i+1) <= (width-1) && (j-1) >= 0)
            {
                totalBlueGx = totalBlueGx + (image[i + 1][j - 1].rgbtBlue * -1);
                totalGreenGx = totalGreenGx + (image[i + 1][j - 1].rgbtGreen * -1);
                totalRedGx = totalRedGx + (image[i + 1][j - 1].rgbtRed * -1);
            }

            //bottom right of box
            if ((i + 1) < height && (j + 1) < width)
            {
                totalBlueGx = totalBlueGx + (image[i + 1][j + 1].rgbtBlue * 1);
                totalGreenGx = totalGreenGx + (image[i + 1][j + 1].rgbtGreen * 1);
                totalRedGx = totalRedGx + (image[i + 1][j + 1].rgbtRed * 1);
            }




            //Gy kernel

            //middle of box
            totalBlueGy  = totalBlueGy + (image[i][j].rgbtBlue * 0);
            totalGreenGy = totalGreenGy + (image[i][j].rgbtGreen * 0);
            totalRedGy = totalRedGy + (image[i][j].rgbtRed * 0);


            //left of box
            if ((j - 1) >= 0)
            {
                totalBlueGy = totalBlueGy + (image[i][j - 1].rgbtBlue * 0);
                totalGreenGy = totalGreenGy + (image[i][j - 1].rgbtGreen * 0);
                totalRedGy = totalRedGy + (image[i][j - 1].rgbtRed * 0);

            }

            //right of box
            if ((j + 1) < width)
            {
                totalBlueGy = totalBlueGy + (image[i][j + 1].rgbtBlue * 0);
                totalGreenGy = totalGreenGy + (image[i][j + 1].rgbtGreen * 0);
                totalRedGy = totalRedGy + (image[i][j + 1].rgbtRed * 0);

            }

            //top middle of box
            if ((i - 1) >= 0)
            {
                totalBlueGy = totalBlueGy + (image[i - 1][j].rgbtBlue * -2);
                totalGreenGy = totalGreenGy + (image[i - 1][j].rgbtGreen * -2);
                totalRedGy = totalRedGy + (image[i - 1][j].rgbtRed * -2);

            }

            //top left of box
            if (((i - 1) >= 0) && ((j - 1)) >= 0)
            {
                totalBlueGy = totalBlueGy + (image[i - 1][j - 1].rgbtBlue * -1);
                totalGreenGy = totalGreenGy + (image[i - 1][j - 1].rgbtGreen * -1);
                totalRedGy = totalRedGy + (image[i - 1][j - 1].rgbtRed * -1);

            }

            //top right of box
            if ((((i - 1) >= 0) && ((j + 1)) < width))
            {
                totalBlueGy = totalBlueGy + (image[i - 1][j + 1].rgbtBlue * -1);
                totalGreenGy = totalGreenGy + (image[i - 1][j + 1].rgbtGreen * -1);
                totalRedGy = totalRedGy + (image[i - 1][j + 1].rgbtRed * -1);

            }

            //bottom midle of box
            if ((i + 1) < height)
            {
                totalBlueGy = totalBlueGy + (image[i + 1][j].rgbtBlue * 2);
                totalGreenGy = totalGreenGy + (image[i + 1][j].rgbtGreen * 2);
                totalRedGy = totalRedGy + (image[i + 1][j].rgbtRed * 2);
            }

            //bottom left of box
            if ((((i + 1) < height) && ((j - 1)) >= 0)) // if((i+1) <= (width-1) && (j-1) >= 0)
            {
                totalBlueGy = totalBlueGy + (image[i + 1][j - 1].rgbtBlue * 1);
                totalGreenGy = totalGreenGy + (image[i + 1][j - 1].rgbtGreen * 1);
                totalRedGy = totalRedGy + (image[i + 1][j - 1].rgbtRed * 1);
            }

            //bottom right of box
            if ((i + 1) < height && (j + 1) < width)
            {
                totalBlueGy = totalBlueGy + (image[i + 1][j + 1].rgbtBlue * 1);
                totalGreenGy = totalGreenGy + (image[i + 1][j + 1].rgbtGreen * 1);
                totalRedGy = totalRedGy + (image[i + 1][j + 1].rgbtRed * 1);
            }



            if (round(sqrt((totalBlueGx * totalBlueGx) + (totalBlueGy * totalBlueGy))) <= 255.0)
            {
                imagetemp[i][j].rgbtBlue = round(sqrt((totalBlueGx * totalBlueGx) + (totalBlueGy * totalBlueGy)));

            }
            else
            {
                imagetemp[i][j].rgbtBlue = 255;

            }

            if (round(sqrt((totalGreenGx * totalGreenGx) + (totalGreenGy * totalGreenGy))) <= 255.0)
            {
                imagetemp[i][j].rgbtGreen = round(sqrt((totalGreenGx * totalGreenGx) + (totalGreenGy * totalGreenGy)));

            }
            else
            {
                imagetemp[i][j].rgbtGreen = 255;

            }

            if (round(sqrt((totalRedGx * totalRedGx) + (totalRedGy * totalRedGy))) <= 255.0)
            {
                imagetemp[i][j].rgbtRed = round(sqrt((totalRedGx * totalRedGx) + (totalRedGy * totalRedGy)));

            }
            else
            {
                imagetemp[i][j].rgbtRed = 255;
            }

            //printf("temp: %i image: %i\n", imagetemp[i][j].rgbtBlue, image[i][j].rgbtBlue);
        }

    }

    //copying imagetemp to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;
        }
    }

}
