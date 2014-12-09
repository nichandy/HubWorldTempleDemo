// A class for storing primitive objects: cylinder, cube, disk, Steiner surface

#include "Shapes.h"
#include "Globals.h"

Shapes::Shapes()
{
}

Shapes::~Shapes()
{}

void
Shapes::createBuffers(GLint program) {

    myCube.createBuffers(program);
    myWiredCube.createBuffers(program);

    myDisk.createBuffers(program);
    myWiredDisk.createBuffers(program);

    myCylinder.createBuffers(program);
    myWiredCylinder.createBuffers(program);
}
// draws solid cube and wire cube together. The wire color is always black
void
Shapes::drawCube(vec4 color)
{
    glUniform4fv( model_color, 1,color );
    myCube.draw();
   // glUniform4fv( model_color, 1,vec4(0,0,0,1) );
   // myWiredCube.draw();
}

// draws solid Cylinder and wire Cylinder together. The wire color is always black
void
Shapes::drawCylinder(vec4 color)
{
    glUniform4fv( model_color, 1,color );
    myCylinder.draw();
   // glUniform4fv( model_color, 1,vec4(0,0,0,1) );
   // myWiredCylinder.draw();
}


// draws solid Disk and wire Disk together. The wire color is always black
void
Shapes::drawDisk(vec4 color)
{
    glUniform4fv( model_color, 1,color );
    myDisk.draw();
  //  glUniform4fv( model_color, 1,vec4(0,0,0,1) );
  //  myWiredDisk.draw();
}
