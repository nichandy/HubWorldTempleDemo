// creates a Cylinder of radius r and height h  along the y+ axis and centered at the origin

#include "WiredCylinder.h"
#include <iostream>
using std::cout;

WiredCylinder::WiredCylinder(int slices, float radius, float height)
{
    numVertices = 6*slices ;  // using a GL_LINES
    mode = GL_LINES;

    points = new vec4[numVertices];
    colors = new vec4[numVertices];

    vec4 normal(0,1,0,0);
    vec4 black = vec4(0,0,0,1);
    float dAngle = 2*M_PI/slices;

    int ind = 0;
    int &index = ind;

    vec4 topVertices[slices];
    vec4 botVertices[slices];
    for (int i = 0; i < slices ; i++)
    {
        int im = (i+1) % slices;
        topVertices[i]  = vec4(radius*cos(im*dAngle),height/2,radius*sin((im*dAngle)),1);
        botVertices[i]  = vec4(radius*cos(im*dAngle),-height/2,radius*sin((im*dAngle)),1);
    }

    for (int i = 0; i < slices ; i++)
    {
        int im = (i+1) % slices;
        makeline(index,topVertices[i],topVertices[im], black ); //  top rim
        makeline(index,botVertices[i],botVertices[im], black ); //  bottom rim
        makeline(index,topVertices[i],botVertices[i], black );  //  top/bottom edges
    }

    // cout<<"WiredCylinder:\n";
    // printArrays();
    // cout << "numVertices: " << numVertices << "    index = " << index << "\n";
}

void
WiredCylinder::makeline(int &index, vec4 v1, vec4 v2, vec4 col)
{

    colors[index] = col;
    points[index] = v1;
    index++;
    colors[index] = col;
    points[index] = v2;
    index++;
}


