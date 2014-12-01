// A car made from cubes, cylinders and disks.
// The car can move forward or backward (see controls in main) causing the wheels to also turn.
#include "Arm.h"
#include "Shapes.h"
#include "Globals.h"

Arm::Arm(): elbowRadius(3), xLoc(0), yLoc(0), zLoc(0), bicepLength(2), bicepWidth(8), foreArmLength(2), foreArmWidth(.5)
{
    //ctor
}

Arm::~Arm()
{
    //dtor
}

void
Arm::drawElbow(mat4& mv)
{
    mv = mv*Translate(0,0,0);
    mvMatrixStack.pushMatrix(mv);
    vec4 color(0,0,1,1);
    mv = mv*Translate(0,0,0);
    mv = mv*Scale(elbowRadius,elbowRadius,elbowRadius);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();

}

void
Arm::drawBicep (mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    mv = mv*Translate(0,bicepRadius,0);
    mv = mv*RotateX(90);     // rotate about x axis
    mv = mv*Scale(0, 2*bicepRadius, 0.5);
    vec4 color(.5,.5,.5,1);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCylinder(color);
    mv = mvMatrixStack.popMatrix();

}
void
Arm::drawForeArm(mat4& mv)
{

}

void
Arm::drawArm(mat4& mv)
{
    // save the current modelview matrix on the stack
    mvMatrixStack.pushMatrix(mv);

    // Draw car body
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );

    drawElbow(mv);

    drawBicep(mv);

    mv = mvMatrixStack.popMatrix();

}

