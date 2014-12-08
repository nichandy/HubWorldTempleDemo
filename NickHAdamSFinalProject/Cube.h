#ifndef CUBE_H
#define CUBE_H

#include "Angel.h"
#include "GeometryBase.h"

class Cube: public GeometryBase
{
    public:
        Cube();

    protected:
    private:
        void quad(int &index, vec4 v1, vec4 v2, vec4 v3, vec4 v4, vec4 col, vec4 norm);
};

#endif // CUBE_H
