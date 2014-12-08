#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "TextureBase.h"

class ImageTexture : public TextureBase
{
    public:
        ImageTexture();
        ImageTexture(std::string  name);
        virtual ~ImageTexture();
    protected:
    private:
};

#endif // IMAGETEXTURE_H
