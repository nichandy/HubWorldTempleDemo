// Person.h
// author: Adam Smith and Nick Handy
// A Person made from cubes, cylinders and disks.
// The Person can move forward and turn with the camera

#ifndef Person_H
#define Person_H

#include "mat.h"
#include "vec.h"

class Person
{
    public:
        Person();
        Person(vec3 personLocation, float height, float width, float movementspeed);
        virtual ~Person();
        void drawPerson(mat4& mv);
        void moveForward(float radians);
        //person attributes
        vec3 location;
        float Height;
        float Width;
        float personAngle;
        float armAngle;
        float movementSpeed;
        bool firstPerson;

    protected:
    private:
        void walkAnimation();
        void drawHead(mat4& mv);
        void drawTorso(mat4& mv);
        void drawLegs(mat4& mv);
        void drawArms(mat4& mv);
        bool armSwitch;
};

#endif // Person_H
