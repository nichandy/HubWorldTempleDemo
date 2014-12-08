#ifndef WIREDCYLINDER_H
#define WIREDCYLINDER_H

#include "Angel.h"
#include "WiredGeometryBase.h"

class WiredCylinder: public WiredGeometryBase
{
    public:
        WiredCylinder(int slices = 36,float radius=.5, float height=1);

    protected:
    private:
        void makeline(int &index, vec4 v1, vec4 v2, vec4 col);
};

#endif // WIREDCYLINDER_H
