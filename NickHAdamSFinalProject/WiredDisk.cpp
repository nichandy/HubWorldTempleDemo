// creates a disk of radius 1 at the origin with normal facing along y+

#include "WiredDisk.h"
#include <iostream>
using std::cout;

// ---------------------------------------------------------------------- constructor
WiredDisk::WiredDisk(int slices, float radius)
{
    numVertices = 4*slices;
    mode = GL_LINES;

    points = new vec4[numVertices];
    colors = new vec4[numVertices];

    vec4 black = vec4(0,0,0,1);
    vec4 center(0,0,0,1);        // center of disk is at origin
    float dAngle = 2*M_PI/slices;    // inner angle of each triangle

    int index = 0;

    vec4 vertices[slices];
    for (int i = 0; i < slices; i++)
    {
        vertices[i]= vec4(radius*cos(i*dAngle),0,radius*sin((i*dAngle)),1);
    }

    for (int i = 0; i < slices; i++)
    {
        int im = (i + 1) % slices;
         // rim edges
        points[index]= vertices[i];
        colors[index]= black;
        index++;
        points[index]= vertices[im];
        colors[index]= black;
        index++;

        // spoke edges
        points[index]= vertices[i];
        colors[index]= black;
        index++;
        points[index]= center;
        colors[index]= black;
        index++;
    }



    //cout<< "WiredDisk:\n";
   // printArrays();
    //cout << "numVertices: " << numVertices << "    index = " << index << "\n";
}
