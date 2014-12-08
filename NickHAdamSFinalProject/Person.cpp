// A Person made from cubes, cylinders and disks.
// The Person can move forward or backward (see controls in main) causing the wheels to also turn.
#include "Person.h"
#include "Shapes.h"
#include "Globals.h"

Person::Person(): xLoc(0), yLoc(0), zLoc(0), Height(12), Width(4), movementSpeed(.4)
{
    //ctor
}

Person::Person(float xloc, float yloc, float zloc, float height, float width, float movementspeed):
        xLoc(xloc), yLoc(yloc), zLoc(zloc), Height(height), Width(width), movementSpeed(movementspeed)
{
    //ctor
}


Person::~Person()
{
    //dtor
}

void
Person::drawHead(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    // assume cylindar has height =1, radius = .5, is centered at the origin, aligned with y axis
    mv = mv * Translate(xLoc, Height * .66 + Width / 2 + yLoc, zLoc);
    mv = mv * RotateX(90);     // rotate about x axis
    mv = mv * Scale(Width, Width / 2, Width);
    vec4 color(.9,.9,1,1);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCylinder(color);
    mv = mv * Translate(0, .5,0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawDisk(color);
    mv = mv * Translate(0, -1, 0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawDisk(color);
    mv = mvMatrixStack.popMatrix();
}

void
Person::drawTorso(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    vec4 color(0,0,1,1);
    mv = mv * Translate(xLoc, Height / 2 + yLoc, zLoc);
    mv = mv * Scale(Width, Height / 3, Width);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);

    mv = mvMatrixStack.popMatrix();
}

void
Person::drawLegs(mat4& mv)
{
    mvMatrixStack.pushMatrix(mv);
    vec4 color(0,0,1,1);
    mv = mv * Translate(xLoc, Height / 6 + yLoc, zLoc);
    mv = mv * Scale(Width / 3, Height / 3, Width / 2);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);

    mv = mvMatrixStack.popMatrix();
}

void
Person::drawArms(mat4& mv)
{
    vec4 color(0,0,1,1);

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, Height / 1.75 + yLoc, zLoc);
    mv = mv * Scale(Width / 3, Height / 6, Width / 3);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc + Height / 1.5, zLoc) * RotateX(40) * Translate(-xLoc, -yLoc - Height / 1.5, -zLoc);
    mv = mv * Translate(xLoc, Height / 2.5 + yLoc, Width / 3 + zLoc);
    mv = mv * Scale(Width / 3, Height / 4, Width / 3);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();
}

void
Person::drawPerson(mat4& mv)
{
    // save the current modelview matrix on the stack
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc, zLoc) * RotateY(-personAngle) * Translate(-xLoc, -yLoc, -zLoc);

    // Draw Person Torso
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawTorso(mv);

    // Draw the Head
    //mvMatrixStack.pushMatrix(mv);
    //mv = mv*Translate(3.5,0,2.4);
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawHead(mv);

    // Draw the 2 Legs
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc + Height / 3, zLoc) * RotateX(-armAngle) * Translate(-xLoc, -yLoc - Height / 3, -zLoc);
    mv = mv * Translate(-Width / 4, 0, 0);
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawLegs(mv);
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc + Height / 3, zLoc) * RotateX(armAngle) * Translate(-xLoc, -yLoc - Height / 3, -zLoc);
    mv = mv * Translate(Width / 4, 0, 0);
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawLegs(mv);
    mv = mvMatrixStack.popMatrix();

    // Draw the 2 Arms
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc + Height / 1.5, zLoc) * RotateX(armAngle) * Translate(-xLoc, -yLoc - Height / 1.5, -zLoc);
    mv = mv * Translate(-Width / 2 - Width / 6, 0, 0);
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawArms(mv);
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(xLoc, yLoc + Height / 1.5, zLoc) * RotateX(-armAngle) * Translate(-xLoc, -yLoc - Height / 1.5, -zLoc);
    mv = mv * Translate(Width / 2 + Width / 6, 0, 0);
    //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    drawArms(mv);
    mv = mvMatrixStack.popMatrix();

    mv = mvMatrixStack.popMatrix();

}

void
Person::walk()
{
    if(armSwitch){
        armAngle += 5;
        if(armAngle > 30) armSwitch = false;
    }
    else if(!armSwitch){
        armAngle -= 5;
        if(armAngle < -30) armSwitch = true;
    }
}

void
Person::moveForward(float radians)
{
    zLoc -= movementSpeed * cos(radians);
    xLoc += movementSpeed * sin(radians);
    walk();
}

/*
void
Person::jump()
{
    while(!jumpSwitch) {
        yLoc += 1;
        Sleep(500);
        if(yLoc > 3) jumpSwitch = true;
    }
    while(jumpSwitch) {
        yLoc -= 1;
        Sleep(500);
        if(yLoc < 0) {
            jumpSwitch = false;
            return;
        }
    }
}
*/
