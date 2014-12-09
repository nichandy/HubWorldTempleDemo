// creates a Cylinder of radius r and height h  along the y+ axis and centered at the origin

// creates a Cylinder of radius r and height h  along the y+ axis and centered at the origin

#include "Cylinder.h"
#include <iostream>
using std::cout;

Cylinder::Cylinder(int slices, float radius, float height)
{
    numVertices = 2*slices + 2;  // using a GL_TRIANGLE_STRIP
    mode = GL_TRIANGLE_STRIP;

    points = new vec4[numVertices];
    colors = new vec4[numVertices];
    normals = new vec4[numVertices];
    tex_coords = new vec2[numVertices];

    vec4 normal(0,1,0,0);
    vec4 color[4] = {vec4(1,1,0,1),vec4(0,0,1,1),vec4(1,0,0,1),vec4(0,1,0,1)};
    float dAngle = 2*M_PI/slices;

    int index = 0;

    for (int i = 0; i <= slices ; i++)
    {
        int im = i % slices;

        points[index]= vec4(radius*cos(im*dAngle),height/2,radius*sin((im*dAngle)),1);
        colors[index]= color[i%2];
        vec3 normal(radius*cos(im*dAngle),0,radius*sin((im*dAngle)));
        normals[index] = vec4(normalize(normal));
        tex_coords[index] = vec2(1.0*i/slices,1);
        index++;

        points[index]= vec4(radius*cos(im*dAngle),-height/2,radius*sin((im*dAngle)),1);
        colors[index]= color[i%2];
        normals[index] = normal;
        tex_coords[index]= vec2(1.0*i/slices,0);
        index++;
    }

   // cout<<"Cylinder:\n";
   // printArrays();
}


