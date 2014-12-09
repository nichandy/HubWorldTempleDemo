#include "Checkerboard.h"


Checkerboard::Checkerboard(): TextureBase(64,64)
{
    makeCheckerboard();
}


Checkerboard::Checkerboard(int w, int h): TextureBase(w,h)
{
    makeCheckerboard();
}

Checkerboard::~Checkerboard()
{
    delete[] image;
}

void
Checkerboard::makeCheckerboard()
{
    image = new GLubyte[width*height*3];
    // Create a checkerboard pattern
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            GLubyte c = (((i & 0x8) == 0) ^ ((j & 0x8)  == 0)) * 255;
            int k = i*height*3 + j*3;
            image[k]  = c;
            image[k + 1]  = c;
            image[k + 2]  = c;
        }
    }
}

