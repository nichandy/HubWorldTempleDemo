#include "ImageTexture.h"

#include "Angel.h"
#include "TargaLoad.h"

ImageTexture::ImageTexture(std::string name)
{
    TargaLoad t;
    TGAFILE *myTGA = new TGAFILE();

    char *c = strdup(name.c_str());  // need to convert from a string to a char*
    t.LoadTGAFile(c, myTGA);
    width = myTGA->imageWidth;
    height = myTGA->imageHeight;
    image = myTGA->imageData;
    delete myTGA;

    cout << "image width = " << width << "\n";
    cout << "image height = " << height << "\n";
}

ImageTexture::~ImageTexture()
{

}
