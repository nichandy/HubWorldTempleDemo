// Lighting and Material Properties
// Note: We really should have a separate Material class where each geometric object has
//    its own material.
#include "LightingShading.h"
#include "Angel.h"

//---------------------------------------------------------------------------- constructor
LightingShading::LightingShading()
{
    // The position in World or Eye Coordinate, depending on how you interpret it in display
    light_position = vec4(50,50,0,1);

    // Light colors all set to white at the moment
    ambientColor = vec4(1.0, 1.0, 1.0, 1.0);
    diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
    specularColor = vec4(1.0, 1.0, 1.0, 1.0);

    intensity = 1.0;

    // These are really material properties and belong with each individual object but
    // for now we will lump them in here and they will apply to all objects.
    ka = 0.2;
    kd = 1.0;
    ks = 0.8;
    shininess = 50.0;

}

//---------------------------------------------------------------------------- destructor
LightingShading::~LightingShading()
{
}

//---------------------------------------------------------------------------- setUp
//  Calculates light-material product and assigns them to the shader variables
void
LightingShading::setUp(GLuint program)
{

    vec4 ambient_product = ka * intensity * ambientColor;
    vec4 diffuse_product = kd * intensity * diffuseColor;
    vec4 specular_product = ks * intensity * specularColor;

    glUniform4fv( glGetUniformLocation(program, "ambient_product"),
                  1, ambient_product );
    glUniform4fv( glGetUniformLocation(program, "diffuse_product"),
                  1, diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "specular_product"),
                  1, specular_product );

    glUniform4fv( glGetUniformLocation(program, "light_position"),
                  1, light_position );

    glUniform1f( glGetUniformLocation(program, "shininess"),
                 shininess );
}
