// creates a disk of radius 1 at the origin with normal facing along y+

#include "Disk.h"
#include <iostream>
using std::cout;

// ---------------------------------------------------------------------- constructor
Disk::Disk(int slices, float radius)
{
    numVertices = slices + 2;
    mode = GL_TRIANGLE_FAN;

    points = new vec4[numVertices];
    colors = new vec4[numVertices];
    normals = new vec4[numVertices];
    tex_coords = new vec2[numVertices];

    vec4 normal(0,1,0,0);    // normal is the same for all triangles. Normal points up along positive y axis
    vec4 color[3] = {vec4(1,0,1,1),vec4(.5,0,1,1)};  // alternate color so we can see triangles
    vec4 center(0,0,0,1);        // center of disk is at origin
    float dAngle = 2*M_PI/slices;    // inner angle of each triangle

    int index = 0;

    // center vertex
    points[index]= center;
    colors[index]= color[index];
    normals[index] = normal;
    tex_coords [index] = vec2(.5,.5);

    for (int i = 0; i < slices; i++)
    {
        index++;
        points[index]= vec4(radius*cos(i*dAngle),0,radius*sin((i*dAngle)),1);
        colors[index]= color[i%2];
        normals[index] = normal;
        tex_coords [index] = vec2(.5+cos(i*dAngle)/2. , .5+sin(i*dAngle)/2 ) ;
    }

    index++;
    points[index]= points[1];
    colors[index]= color[1];
    normals[index] = normal;
    tex_coords [index] = tex_coords [1];

    //cout<< "Disk:\n";
    //printArrays();
}
