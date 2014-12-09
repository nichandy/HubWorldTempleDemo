// Generates the vertices, colors, and normals of a unit cube
// centered at origin, sides aligned with axes.
//
// Generate 12 lines: 24 vertices and 24 colors
//    v5----- v6
//   /|      /|
//  v1------v2|              ^ y
//  | |     | |              |
//  | |v4---|-|v7            -->x
//  |/      |/              /
//  v0------v3              z

#include "WiredCube.h"
#include <iostream>
using std::cout;

// ---------------------------------------------------------------------- default constructor
WiredCube::WiredCube()
{
    numVertices = 24;  // 12 lines, 2 vertices per line
    mode = GL_LINES;

    // These arrays are member variables. We really don't need to keep them permanently after they
    // have been placed in the gpu buffers. However, we will keep them around for the time being.
    points = new vec4[numVertices];
    colors = new vec4[numVertices];

    // These are temporary arrays of the data. Note this data will be placed (with possible duplicates)
    // into the above member variable arrays.  Need to use indexing for more efficient storage.
    // For the meaning of v0, v1, etc, see the diagram at the top of this file.
    vec4 vertices[8];

    vertices[0] = vec4( -0.5, -0.5,  0.5, 1.0 );   // v0
    vertices[1] = vec4( -0.5,  0.5,  0.5, 1.0 );   // v1
    vertices[2] = vec4(  0.5,  0.5,  0.5, 1.0 );   // v2
    vertices[3] = vec4(  0.5, -0.5,  0.5, 1.0 );   // v3
    vertices[4] = vec4( -0.5, -0.5, -0.5, 1.0 );   // v4
    vertices[5] = vec4( -0.5,  0.5, -0.5, 1.0 );   // v5
    vertices[6] = vec4(  0.5,  0.5, -0.5, 1.0 );   // v6
    vertices[7] = vec4(  0.5, -0.5, -0.5, 1.0 );    // v7

    vec4 black = vec4(0,0,0,1);

//    v5----- v6
//   /|      /|
//  v1------v2|              ^ y
//  | |     | |              |
//  | |v4---|-|v7            -->x
//  |/      |/              /
//  v0------v3              z

    int i = 0;
    int &index = i;
    line(index,vertices[0], vertices[1], black );
    line(index,vertices[1], vertices[2], black );
    line(index,vertices[2], vertices[3], black );
    line(index,vertices[3], vertices[0], black );

    line(index,vertices[4], vertices[5], black );
    line(index,vertices[5], vertices[6], black );
    line(index,vertices[6], vertices[7], black );
    line(index,vertices[7], vertices[4], black );

    line(index,vertices[0], vertices[4], black );
    line(index,vertices[3], vertices[7], black );
    line(index,vertices[2], vertices[6], black );
    line(index,vertices[1], vertices[5], black );
    //printArrays();
}

// ---------------------------------------------------------------------- line
// This is a helper function which generates the vertex attributes (points, color,
// normals, texture coordinates) for a single edge of the cube. We will call
// this 12 times, once for each edge.
void
WiredCube::line(int &index, vec4 v1, vec4 v2, vec4 col)
{

    colors[index] = col;
    points[index] = v1;
    index++;
    colors[index] = col;
    points[index] = v2;
    index++;
}









