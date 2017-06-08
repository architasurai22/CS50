#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    char* file1 = argv[1];
    char* file2 = argv[2];
    
    FILE* ptr1 = fopen(file1, "r");
    if (ptr1 == NULL)
    {
        fprintf(stderr,"Unable to open input file.\n");
        return 1;
    }
    FILE* ptr2 = fopen(file2, "w");
    if (ptr2 == NULL)
    {
        fclose(ptr1);
        fprintf(stderr, "Unable to open output file.\n");
        return 1;
    }
    BITMAPFILEHEADER b1;
    fread(&b1, sizeof(BITMAPFILEHEADER), 1, ptr1);

    BITMAPINFOHEADER b2;
    fread(&b2, sizeof(BITMAPINFOHEADER), 1, ptr1);

    if (b1.bfType != 0x4d42 || b1.bfOffBits != 54 || b2.biSize != 40 || 
        b2.biBitCount != 24 || b2.biCompression != 0)
    {
        fclose(ptr1);
        fclose(ptr2);
        fprintf(stderr, "File format not supported.\n");
        return 1;
    }

    fwrite(&b1, sizeof(BITMAPFILEHEADER), 1, ptr2);

    fwrite(&b2, sizeof(BITMAPINFOHEADER), 1, ptr2);
    
    int height = abs(b2.biHeight);
    int width = abs(b2.biWidth);

    int padding =  (4 - (b2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    RGBTRIPLE triple;
    
    for (int i = 0;i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fread(&triple, sizeof(RGBTRIPLE), 1, ptr1);
            triple.rgbtGreen = 0x000000;
            triple.rgbtBlue = 0x000000;
            
            fwrite(&triple, sizeof(RGBTRIPLE), 1, ptr2);
        }
    }
    fseek(ptr1, padding, SEEK_CUR);
    for (int k = 0; k < padding; k++)
        fputc(0x00, ptr2);

    fclose(ptr1);
    fclose(ptr2);
    return 0;
}
