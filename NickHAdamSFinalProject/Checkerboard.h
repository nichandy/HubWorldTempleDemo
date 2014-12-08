#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include "TextureBase.h"

class Checkerboard : public TextureBase
{
    public:
        Checkerboard();
        Checkerboard(int w, int h);
        virtual ~Checkerboard();
    protected:
    private:
        void makeCheckerboard();
};

#endif // CHECKERBOARD_H
