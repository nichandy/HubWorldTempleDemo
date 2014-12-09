// A Person made from cubes, cylinders and disks.
// The Person can move forward or backward (see controls in main) causing the wheels to also turn.
#include "WorldEnvironment.h"
#include "Shapes.h"
#include "Globals.h"

WorldEnvironment::WorldEnvironment(): Height(100), Width(100), Angle(0)
{
    //ctor
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
WorldEnvironment::drawBuilding(mat4& mv)
{

    mv = mv * Translate(0, 0, -100);
    mv = mv * Scale(Width / 2, Height, Width / 2);
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

    mvMatrixStack.pushMatrix(mv);
    drawBuilding(mv);
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(60, 0, 0);
    drawBuilding(mv);
    mv = mvMatrixStack.popMatrix();

    mv = mvMatrixStack.popMatrix();
}


