#ifndef WORLDENVIRONMENT_H
#define WORLDENVIRONMENT_H

#include "mat.h"

class WorldEnvironment
{
    public:
        WorldEnvironment();
        virtual ~WorldEnvironment();
        void drawWorldEnvironment(mat4& mv);
        float Height;  // height Person
        float Width;  // width of body
        float Angle;


// Viewing transformation parameters
    protected:
    private:
        void drawBuilding(mat4& mv);
        void drawWall(mat4& mv);
        void drawStreet(mat4& mv);
        void drawGrass(mat4& mv);
        void drawGround(mat4& mv);
};

#endif // WorldEnvironment_H

