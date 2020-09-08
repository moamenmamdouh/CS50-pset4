#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = temp_image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = temp_image[i][width - j - 1].rgbtGreen;
        }
    }
    free(temp_image);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int pixels_counter = 0;
    int red_sum = 0;
    int green_sum = 0;
    int blue_sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixels_counter++;
            red_sum += temp_image[i][j].rgbtRed;
            green_sum += temp_image[i][j].rgbtGreen;
            blue_sum += temp_image[i][j].rgbtBlue;

            if (i > 0)
            {
                pixels_counter++;
                red_sum += temp_image[i - 1][j].rgbtRed;
                green_sum += temp_image[i - 1][j].rgbtGreen;
                blue_sum += temp_image[i - 1][j].rgbtBlue;

                if (j < (width - 1))
                {
                    pixels_counter++;
                    red_sum += temp_image[i - 1][j + 1].rgbtRed;
                    green_sum += temp_image[i - 1][j + 1].rgbtGreen;
                    blue_sum += temp_image[i - 1][j + 1].rgbtBlue;
                }

                if (j > 0)
                {
                    pixels_counter++;
                    red_sum += temp_image[i - 1][j - 1].rgbtRed;
                    green_sum += temp_image[i - 1][j - 1].rgbtGreen;
                    blue_sum += temp_image[i - 1][j - 1].rgbtBlue;
                }
            }

            if (i < (height - 1))
            {
                pixels_counter++;
                red_sum += temp_image[i + 1][j].rgbtRed;
                green_sum += temp_image[i + 1][j].rgbtGreen;
                blue_sum += temp_image[i + 1][j].rgbtBlue;

                if (j < (width - 1))
                {
                    pixels_counter++;
                    red_sum += temp_image[i + 1][j + 1].rgbtRed;
                    green_sum += temp_image[i + 1][j + 1].rgbtGreen;
                    blue_sum += temp_image[i + 1][j + 1].rgbtBlue;
                }

                if (j > 0)
                {
                    pixels_counter++;
                    red_sum += temp_image[i + 1][j - 1].rgbtRed;
                    green_sum += temp_image[i + 1][j - 1].rgbtGreen;
                    blue_sum += temp_image[i + 1][j - 1].rgbtBlue;
                }
            }

            if (j < (width - 1))
            {
                pixels_counter++;
                red_sum += temp_image[i][j + 1].rgbtRed;
                green_sum += temp_image[i][j + 1].rgbtGreen;
                blue_sum += temp_image[i][j + 1].rgbtBlue;
            }

            if (j > 0)
            {
                pixels_counter++;
                red_sum += temp_image[i][j - 1].rgbtRed;
                green_sum += temp_image[i][j - 1].rgbtGreen;
                blue_sum += temp_image[i][j - 1].rgbtBlue;
            }

            image[i][j].rgbtRed = round((float)red_sum / pixels_counter);
            image[i][j].rgbtGreen = round((float)green_sum / pixels_counter);
            image[i][j].rgbtBlue = round((float)blue_sum / pixels_counter);

            red_sum = 0;
            green_sum = 0;
            blue_sum = 0;
            pixels_counter = 0;
        }
    }
    free(temp_image);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int red_Gx = 0, red_Gy = 0;
    int green_Gx = 0, green_Gy = 0;
    int blue_Gx = 0, blue_Gy = 0;
    int red_sum = 0;
    int green_sum = 0;
    int blue_sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 0)
            {
                red_Gy += temp_image[i - 1][j].rgbtRed * -2;
                green_Gy += temp_image[i - 1][j].rgbtGreen * -2;
                blue_Gy += temp_image[i - 1][j].rgbtBlue * -2;

                if (j < (width - 1))
                {
                    red_Gx += temp_image[i - 1][j + 1].rgbtRed;
                    red_Gy += temp_image[i - 1][j + 1].rgbtRed * -1;
                    green_Gx += temp_image[i - 1][j + 1].rgbtGreen;
                    green_Gy += temp_image[i - 1][j + 1].rgbtGreen * -1;
                    blue_Gx += temp_image[i - 1][j + 1].rgbtBlue;
                    blue_Gy += temp_image[i - 1][j + 1].rgbtBlue * -1;
                }

                if (j > 0)
                {
                    red_Gx += temp_image[i - 1][j - 1].rgbtRed * -1;
                    red_Gy += temp_image[i - 1][j - 1].rgbtRed * -1;
                    green_Gx += temp_image[i - 1][j - 1].rgbtGreen * -1;
                    green_Gy += temp_image[i - 1][j - 1].rgbtGreen * -1;
                    blue_Gx += temp_image[i - 1][j - 1].rgbtBlue * -1;
                    blue_Gy += temp_image[i - 1][j - 1].rgbtBlue * -1;
                }
            }

            if (i < (height - 1))
            {
                red_Gy += temp_image[i + 1][j].rgbtRed * 2;
                green_Gy += temp_image[i + 1][j].rgbtGreen * 2;
                blue_Gy += temp_image[i + 1][j].rgbtBlue * 2;

                if (j < (width - 1))
                {
                    red_Gx += temp_image[i + 1][j + 1].rgbtRed;
                    red_Gy += temp_image[i + 1][j + 1].rgbtRed;
                    green_Gx += temp_image[i + 1][j + 1].rgbtGreen;
                    green_Gy += temp_image[i + 1][j + 1].rgbtGreen;
                    blue_Gx += temp_image[i + 1][j + 1].rgbtBlue;
                    blue_Gy += temp_image[i + 1][j + 1].rgbtBlue;
                }

                if (j > 0)
                {
                    red_Gx += temp_image[i + 1][j - 1].rgbtRed * -1;
                    red_Gy += temp_image[i + 1][j - 1].rgbtRed;
                    green_Gx += temp_image[i + 1][j - 1].rgbtGreen * -1;
                    green_Gy += temp_image[i + 1][j - 1].rgbtGreen;
                    blue_Gx += temp_image[i + 1][j - 1].rgbtBlue * -1;
                    blue_Gy += temp_image[i + 1][j - 1].rgbtBlue;
                }
            }

            if (j < (width - 1))
            {
                red_Gx += temp_image[i][j + 1].rgbtRed * 2;
                green_Gx += temp_image[i][j + 1].rgbtGreen * 2;
                blue_Gx += temp_image[i][j + 1].rgbtBlue * 2;
            }

            if (j > 0)
            {
                red_Gx += temp_image[i][j - 1].rgbtRed * -2;
                green_Gx += temp_image[i][j - 1].rgbtGreen * -2;
                blue_Gx += temp_image[i][j - 1].rgbtBlue * -2;
            }

            red_sum = round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
            green_sum = round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
            blue_sum = round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

            if (red_sum > 255)
            {
                red_sum = 255;
            }

            if (green_sum > 255)
            {
                green_sum = 255;
            }

            if (blue_sum > 255)
            {
                blue_sum = 255;
            }

            image[i][j].rgbtRed = red_sum;
            image[i][j].rgbtGreen = green_sum;
            image[i][j].rgbtBlue = blue_sum;

            red_Gx = 0;
            red_Gy = 0;
            green_Gx = 0;
            green_Gy = 0;
            blue_Gx = 0;
            blue_Gy = 0;
            red_sum = 0;
            green_sum = 0;
            blue_sum = 0;

        }
    }
    free(temp_image);
    return;
}
