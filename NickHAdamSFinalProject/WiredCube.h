#ifndef WIREDCUBE_H
#define WIREDCUBE_H

#include "Angel.h"
#include "WiredGeometryBase.h"

class WiredCube: public WiredGeometryBase
{
    public:
        WiredCube();

    protected:
    private:
        void line(int &index, vec4 v1, vec4 v2, vec4 col);
};

#endif // WIREDCUBE_H
