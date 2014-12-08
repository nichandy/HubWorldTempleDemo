#ifndef WIREDDISK_H
#define WIREDDISK_H

#include "Angel.h"
#include "WiredGeometryBase.h"

class WiredDisk: public WiredGeometryBase
{
    public:
        WiredDisk(int slices = 18,float radius=.5);

    protected:
    private:
};

#endif // WIREDDISK_H
