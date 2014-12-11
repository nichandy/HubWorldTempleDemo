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
        void walk();
        void moveForward(float radians);
        //float xLoc;
        //float yLoc;
        //float zLoc;
        vec3 location;
        float Height;
        float Width;
        float personAngle;
        float armAngle;
        float movementSpeed;
        bool firstPerson;

    protected:
    private:
        void drawHead(mat4& mv);
        void drawTorso(mat4& mv);
        void drawLegs(mat4& mv);
        void drawArms(mat4& mv);
        bool armSwitch;
};

#endif // Person_H
