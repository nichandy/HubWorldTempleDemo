#ifndef CYLINDER_H
#define CYLINDER_H

#include "Angel.h"
#include "GeometryBase.h"

class Cylinder: public GeometryBase
{
    public:
        Cylinder(int slices = 36,float radius=.5, float height=1);

    protected:
    private:
};

#endif // CYLINDER_H
