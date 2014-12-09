#ifndef SHAPES_H
#define SHAPES_H

#include "Cube.h"
#include "WiredCube.h"
#include "Disk.h"
#include "WiredDisk.h"
#include "Cylinder.h"
#include "WiredCylinder.h"

class Shapes
{
public:
    Shapes();
    virtual ~Shapes();

   Cube myCube;
    WiredCube myWiredCube;
    Cylinder myCylinder;
    WiredCylinder myWiredCylinder;
    Disk myDisk;
    WiredDisk myWiredDisk;

    void createBuffers(GLint program);

    void drawCube(vec4 color);
    void drawCylinder(vec4 color);
    void drawDisk(vec4 color);

protected:
private:
};

#endif // SHAPES_H
