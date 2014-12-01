#ifndef ARM_H
#define ARM_H

#include "mat.h"

class Arm
{
    public:
        Arm();
        virtual ~Arm();
        void drawArm(mat4& mv);
        float elbowRadius;
        float xLoc;
        float yLoc;
        float zLoc;
        float bicepLength;
        float bicepRadius;
        float foreArmLength;
        float foreArmAngle;

// Viewing transformation parameters
    protected:
    private:
        void drawElbow(mat4& mv);
        void drawBicep(mat4& mv);
        void drawForeArm(mat4& mv);
};

#endif // CAR_H

