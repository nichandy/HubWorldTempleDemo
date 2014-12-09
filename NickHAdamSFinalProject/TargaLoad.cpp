#include "TargaLoad.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
using std::cout;

TargaLoad::TargaLoad()
{
    //ctor
}

TargaLoad::~TargaLoad()
{
    //dtor
}

int
TargaLoad::LoadTGAFile(char *filename, TGAFILE *tgaFile)
{
	FILE *filePtr;
	unsigned char ucharBad;
	short int sintBad;
	long imageSize;
	int colorMode;
	long imageIdx;
	unsigned char colorSwap;

	// open the TGA file

	filePtr = fopen(filename, "rb");
	cout << "got to here in TargaLoad 1" << "\n";
	if(!filePtr)
	{
	    perror("Error");
	  printf("%s error number = \n", filename);
	  cout << "filePtr = " << filePtr << "\n";
  	  return 0;
	}

	// read first two bytes of data we don't need
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

        // read in the image type
	fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// for our purposes, the image type should be either a 2 or a 3
	if((tgaFile->imageTypeCode != 2) && (tgaFile->imageTypeCode != 3))
	{
	    cout << "got to here in TargaLoad 2" << "\n";
		fclose(filePtr);
		return 0;
	}

	// read 9 bytes of data we don't need
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// read image dimensions
	fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

	// read image bit depth
	fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

	// read 1 byte of data we don't need
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// colorMode -> 3 = BGF, 4 = BGRA
	colorMode = tgaFile->bitCount / 8;
	imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

	// allocate memory for image data
	tgaFile->imageData = (unsigned char *)malloc(sizeof(unsigned char)*imageSize);
	// read in image data
	fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

	// change BGR to RGB so OpenGL can read the image data
	for (imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx+2] = colorSwap;
	}

	// close the file
	fclose(filePtr);
	return 1;
}
