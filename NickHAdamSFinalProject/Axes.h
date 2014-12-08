// Draws coordinate axes
#ifndef AXES_H
#define AXES_H

#include "mat.h"

class Axes
{
    public:
        Axes();
        void draw(mat4 &mv, int hasZ);
    protected:
    private:
};

#endif // AXES_H
