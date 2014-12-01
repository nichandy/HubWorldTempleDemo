// A car made from cubes, cylinders and disks.
// The car can move forward or backward (see controls in main) causing the wheels to also turn.
#include "Arm.h"
#include "Shapes.h"
#include "Globals.h"

Arm::Arm(): elbowRadius(1), xLoc(0), yLoc(0), zLoc(0), bicepLength(10), bicepRadius(4), foreArmLength(10), foreArmAngle(0)
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
    mv = mv*Translate(xLoc,yLoc,zLoc);
    mv = mv*Scale(elbowRadius,elbowRadius,elbowRadius);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();

}

void
Arm::drawBicep (mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    mv = mv*Translate(xLoc,5*elbowRadius + yLoc,zLoc);
    mv = mv*Scale(elbowRadius, bicepLength, elbowRadius);
    vec4 color(.5,.5,.5,1);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCylinder(color);
    mv = mvMatrixStack.popMatrix();

}
void
Arm::drawForeArm(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    mv = mv*RotateZ(foreArmAngle);
    mv = mv*Translate(5*elbowRadius + xLoc,yLoc,zLoc);
    mv = mv*RotateZ(90);
    mv = mv*Scale(elbowRadius, foreArmLength, elbowRadius);
    vec4 color(.5,.5,.5,1);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCylinder(color);
    mv = mvMatrixStack.popMatrix();

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

    drawForeArm(mv);


}

