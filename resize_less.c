/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int resize = atoi(argv[1]);
    if(resize < 1 || resize > 100)
    {
        printf("Resize must be between 1 and 100\n");
        return 2;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    BITMAPFILEHEADER outbf;
	BITMAPINFOHEADER outbi;	
	outbf = bf;
	outbi = bi;
	outbi.biWidth = bi.biWidth * resize;
	outbi.biHeight = bi.biHeight * resize;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding =  (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    outbf.bfSize = 54 + outbi.biWidth * abs(outbi.biHeight) * 3 + abs(outbi.biHeight) *  outpadding;
	outbi.biSizeImage = ((((outbi.biWidth * outbi.biBitCount) + 31) & ~31) / 8) * abs(outbi.biHeight);

    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

		// write outfile's BITMAPINFOHEADER
		fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

		for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
		{
				// Write each line factor-times
				for(int n = 0; n < resize; n++)
				{
						// iterate over pixels in scanline
						for (int j = 0; j < bi.biWidth; j++)
						{
								// temporary storage
								RGBTRIPLE triple;

								// read RGB triple from infile
								fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

								// write RGB triple to outfile
								for(int m = 0; m < resize; m++) 
								{
										fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
								}
						}

						// skip over padding in infile
						fseek(inptr, padding, SEEK_CUR);

						// then add it to outfile
						for (int k = 0; k <outpadding; k++)
								fputc(0x00, outptr);

						fseek(inptr, -(bi.biWidth * 3 + padding ), SEEK_CUR);

				}
				fseek(inptr, bi.biWidth*3+padding, SEEK_CUR);
		}

		// close infile
		fclose(inptr);

		// close outfile
		fclose(outptr);

		// sucess
		return 0;
}
