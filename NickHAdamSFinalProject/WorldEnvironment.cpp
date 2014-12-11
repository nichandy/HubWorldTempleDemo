// A Person made from cubes, cylinders and disks.
// The Person can move forward or backward (see controls in main) causing the wheels to also turn.
#include "WorldEnvironment.h"
#include "Shapes.h"
#include "Globals.h"

WorldEnvironment::WorldEnvironment(): xLoc(0), yLoc(0), zLoc(0), Height(100), Width(100), Angle(0)
{
    //ctor
}

WorldEnvironment::WorldEnvironment(float xloc, float yloc, float zloc):
                                    xLoc(xloc), yLoc(yloc), zLoc(zloc)
{

}

WorldEnvironment::~WorldEnvironment()
{
    //dtor
}

void
WorldEnvironment::drawGround(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(0, -.1, 0);
    mv = mv * Scale(Width * 5, .2, Width * 5);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(1, 1, 1, 1));
    mv = mvMatrixStack.popMatrix();
}

void
WorldEnvironment::drawGrass(mat4& mv)
{
    //dtor
}

void
WorldEnvironment::drawWater(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, -.5 + yLoc, 100 + zLoc);
    mv = mv * Scale(1, 1, 1);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(1, 1, 1, 1));
    mv = mvMatrixStack.popMatrix();
}

void
WorldEnvironment::drawBuilding(mat4& mv)
{

    mv = mv * Translate(0, 50, -100);
    mv = mv * Scale(Width / 2, Height, Width / 2);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(1, .7, 1, 1));

}

void
WorldEnvironment::drawSkyBox(mat4& mv)
{
    mv = mv * Translate(0, 0, 0);
    mv = mv * Scale(Width * 70, Height * 70, Width * 70);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(1, .7, 1, 1));
}

void
WorldEnvironment::drawStreet(mat4& mv)
{
    //dtor
}

void
WorldEnvironment::drawWall(mat4& mv)
{
    //dtor
}

void
WorldEnvironment::drawWorldEnvironment(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    drawGround(mv);

//    mvMatrixStack.pushMatrix(mv);
//    drawSkyBox(mv);
//    mv = mvMatrixStack.popMatrix();

    mv = mvMatrixStack.popMatrix();
}


