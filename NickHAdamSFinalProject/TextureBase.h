#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include "Angel.h"

class TextureBase
{
public:
    TextureBase();
    TextureBase(int w, int h);
    virtual ~TextureBase();
    GLuint textureID;
    void setUp(GLuint program);
    GLubyte *image;    // this is your texture data
    int width;
    int height;
    void bind(GLuint program);
protected:
public:

};

#endif // TEXTUREBASE_H
