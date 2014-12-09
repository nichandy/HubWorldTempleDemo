#include "Axes.h"
#include "Shapes.h"
#include "Globals.h"

Axes::Axes()
{}

void
Axes::draw(mat4 &mv, int hasZ)
{
    mvMatrixStack.pushMatrix(mv);

    mv = mv*Scale(.1,30,.1);
    mv = mv*Translate(0,.5,0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    glUniform4fv( model_color, 1,vec4(0,1,0,1) );
    shapes.myCylinder.draw();               // y axis
    mv = mvMatrixStack.popMatrix();

    if (hasZ == 1)  // don't always want to draw the z axis
    {
        mvMatrixStack.pushMatrix(mv);
        mv = mv*RotateX(90);
        mv = mv*Scale(.1,30,.1);
        mv = mv*Translate(0,.5,0);
        glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
        glUniform4fv( model_color, 1,vec4(0,0,1,1) );
        shapes.myCylinder.draw();   // z axis
        mv = mvMatrixStack.popMatrix();
    }

    mvMatrixStack.pushMatrix(mv);
    mv = mv*RotateZ(-90);
    mv = mv*Scale(.1,30,.1);
    mv = mv*Translate(0,.5,0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    glUniform4fv( model_color, 1,vec4(1,0,0,1) );
    shapes.myCylinder.draw();   // x axis
    mv = mvMatrixStack.popMatrix();

}
