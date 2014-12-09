#ifndef DISK_H
#define DISK_H

#include "Angel.h"
#include "GeometryBase.h"

class Disk: public GeometryBase
{
    public:
        Disk(int slices = 18,float radius=.5);

    protected:
    private:
};

#endif // DISK_H
