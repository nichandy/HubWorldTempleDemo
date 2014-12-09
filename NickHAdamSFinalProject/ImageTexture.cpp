#include "ImageTexture.h"



//using namespace std;

ImageTexture::ImageTexture(char  *c)
{
    TargaLoad t;
    TGAFILE *myTGA = new TGAFILE();

    //char *c = strdup(name.c_str());  // need to convert from a string to a char*
    t.LoadTGAFile(c, myTGA);
    width = myTGA->imageWidth;
    height = myTGA->imageHeight;
    image = myTGA->imageData;
    delete myTGA;

    //cout << "image width = " << width << "\n"; //bad
    //cout << "image height = " << height << "\n"; //bad
}

ImageTexture::ImageTexture()
{

}

ImageTexture::~ImageTexture()
{

}
