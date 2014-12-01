#ifndef Person_H
#define Person_H

#include "mat.h"

class Person
{
    public:
        Person();
        Person(int xloc, int yloc, int zloc, int height, int width);
        virtual ~Person();
        void drawPerson(mat4& mv);
        //float wheelAngle;
        //float wheelRadius;
        float xLoc;
        float yLoc;
        float zLoc;
        float Height;  // height Person
        //float cLength;  // length of body
        float Width;  // width of body
// Viewing transformation parameters
    protected:
    private:
        void drawHead(mat4& mv);
        void drawTorso(mat4& mv);
        void drawLegs(mat4& mv);
        void drawArms(mat4& mv);
};

#endif // Person_H
