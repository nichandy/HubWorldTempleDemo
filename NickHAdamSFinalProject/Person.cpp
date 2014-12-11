// A Person made from cubes, cylinders and disks.
// The Person can move forward or backward (see controls in main) causing the wheels to also turn.
#include "Person.h"
#include "Shapes.h"
#include "Globals.h"
/*
Person::Person(): xLoc(0), yLoc(0), zLoc(0), Height(3), Width(.5), movementSpeed(.4), firstPerson(false)
{
    //ctor
}

Person::Person(float xloc, float yloc, float zloc, float height, float width, float movementspeed):
        xLoc(xloc), yLoc(yloc), zLoc(zloc), Height(height), Width(width), movementSpeed(movementspeed), firstPerson(false)
{
    //ctor
}
*/

Person::Person(): location(vec3(0,0,0)), Height(3), Width(.5), movementSpeed(.4), firstPerson(false)
{
    //ctor
}

Person::Person(vec3 personLocation, float height, float width, float movementspeed):
        location(personLocation), Height(height), Width(width), movementSpeed(movementspeed), firstPerson(false)
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
    mv = mv * Translate(location.x, Height * .66 + Width / 2 + location.y, location.z);
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
    mv = mv * Translate(location.x, Height / 2 + location.y, location.z);
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
    mv = mv * Translate(location.x, Height / 6 + location.y, location.z);
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
    mv = mv * Translate(location.x, Height / 1.75 + location.y, location.z);
    mv = mv * Scale(Width / 3, Height / 6, Width / 3);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(location.x, location.y + Height / 1.5, location.z) * RotateX(40) * Translate(-location.x, -location.y - Height / 1.5, -location.z);
    mv = mv * Translate(location.x, Height / 2.5 + location.y, Width / 1.5 + location.z);
    mv = mv * Scale(Width / 3, Height / 4, Width / 3);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(color);
    mv = mvMatrixStack.popMatrix();
}

void
Person::drawPerson(mat4& mv)
{
    if(!firstPerson){ //if not first person mode, draw the body

        mvMatrixStack.pushMatrix(mv);

        mv = mv * Translate(location) * RotateY(-personAngle) * Translate(-location);

        drawTorso(mv);

        drawHead(mv);

        // Draw the 2 Legs
        mvMatrixStack.pushMatrix(mv);
        mv = mv * Translate(location.x, location.y + Height / 3, location.z) * RotateX(-armAngle) * Translate(-location.x, -location.y - Height / 3, -location.z);
        mv = mv * Translate(-Width / 4, 0, 0);
        //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
        drawLegs(mv);
        mv = mvMatrixStack.popMatrix();

        mvMatrixStack.pushMatrix(mv);
        mv = mv * Translate(location.x, location.y + Height / 3, location.z) * RotateX(armAngle) * Translate(-location.x, -location.y - Height / 3, -location.z);
        mv = mv * Translate(Width / 4, 0, 0);
        //glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
        drawLegs(mv);
        mv = mvMatrixStack.popMatrix();

        // Draw the 2 Arms
        //first arm
        mvMatrixStack.pushMatrix(mv);
        mv = mv * Translate(location.x, location.y + Height / 1.5, location.z) * RotateX(armAngle) * Translate(-location.x, -location.y - Height / 1.5, -location.z);
        mv = mv * Translate(-Width / 2 - Width / 6, 0, 0);
        drawArms(mv);
        mv = mvMatrixStack.popMatrix();

        //second arm
        mvMatrixStack.pushMatrix(mv);
        mv = mv * Translate(location.x, location.y + Height / 1.5, location.z) * RotateX(-armAngle) * Translate(-location.x, -location.y - Height / 1.5, -location.z);
        mv = mv * Translate(Width / 2 + Width / 6, 0, 0);
        drawArms(mv);
        mv = mvMatrixStack.popMatrix();

        mv = mvMatrixStack.popMatrix();
    }
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
    location.z -= movementSpeed * cos(radians);
    location.x += movementSpeed * sin(radians);
    walk();
}
