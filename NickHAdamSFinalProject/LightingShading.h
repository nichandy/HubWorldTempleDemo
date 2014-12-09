#ifndef LIGHTINGSHADING_H
#define LIGHTINGSHADING_H

#include "Angel.h"

// Currently, we assume there is a single light source
class LightingShading
{
    public:
        LightingShading();
        virtual ~LightingShading();
        vec4 light_position;
        vec4 ambientColor;
        vec4 diffuseColor;
        vec4 specularColor;
        float intensity;

        // Material Properties (really should be assigned to each geometric shape separately)
        float ka;
        float kd;
        float ks;
        float shininess;

        void setUp(GLuint program);

    protected:
    private:
};

#endif // LIGHTINGSHADING_H
