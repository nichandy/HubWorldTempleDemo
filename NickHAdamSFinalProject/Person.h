#ifndef Person_H
#define Person_H

#include "mat.h"

class Person
{
    public:
        Person();
        Person(float xloc, float yloc, float zloc, float height, float width, float movementspeed);
        virtual ~Person();
        void drawPerson(mat4& mv);
        void walk();
        void moveForward(float radians);
        //void jump();
        //float wheelAngle;
        //float wheelRadius;
        float xLoc;
        float yLoc;
        float zLoc;
        float Height;  // height Person
        float Width;  // width of body
        float personAngle;
        float armAngle;
        float movementSpeed;
// Viewing transformation parameters
    protected:
    private:
        void drawHead(mat4& mv);
        void drawTorso(mat4& mv);
        void drawLegs(mat4& mv);
        void drawArms(mat4& mv);
        bool armSwitch;
        //bool jumpSwitch;
};

#endif // Person_H
