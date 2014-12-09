#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "TextureBase.h"
#include "Angel.h"
#include "TargaLoad.h"

class ImageTexture : public TextureBase
{
   public:
        ImageTexture();
        ImageTexture(char  *name);

        virtual ~ImageTexture();
   protected:
   private:
};

#endif // IMAGETEXTURE_H
