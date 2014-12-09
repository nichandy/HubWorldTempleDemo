// Generates the vertices, colors, and normals of a unit cube
// centered at origin, sides aligned with axes.
//
// Generate 12 triangles: 36 vertices and 36 colors
//    v5----- v6
//   /|      /|
//  v1------v2|              ^ y
//  | |     | |              |
//  | |v4---|-|v7            -->x
//  |/      |/              /
//  v0------v3              z
// Always use the Right Hand Rule to generate vertex sequence. We want outward facing normals.

#include "Cube.h"
#include <iostream>
using std::cout;

// ---------------------------------------------------------------------- default constructor
Cube::Cube()
{
    numVertices = 36;
    mode = GL_TRIANGLES;

    // These arrays are member variables. We really don't need to keep them permanently after they
    // have been placed in the gpu buffers. However, we will keep them around for the time being.
    points = new vec4[numVertices];
    colors = new vec4[numVertices];
    normals = new vec4[numVertices];
    tex_coords = new vec2[numVertices];

    // These are temporary arrays of the data. Note this data will be placed (with possible duplicates)
    // into the above member variable arrays.  Need to use indexing for more efficient storage.
    // For the meaning of v0, v1, etc, see the diagram at the top of this file.
    vec4 vertices[8];
    vec4 vertex_colors[8];
    vec4 face_normals[6];

    vertices[0] = vec4( -0.5, -0.5,  0.5, 1.0 );   // v0
    vertices[1] = vec4( -0.5,  0.5,  0.5, 1.0 );   // v1
    vertices[2] = vec4(  0.5,  0.5,  0.5, 1.0 );   // v2
    vertices[3] = vec4(  0.5, -0.5,  0.5, 1.0 );   // v3
    vertices[4] = vec4( -0.5, -0.5, -0.5, 1.0 );   // v4
    vertices[5] = vec4( -0.5,  0.5, -0.5, 1.0 );   // v5
    vertices[6] = vec4(  0.5,  0.5, -0.5, 1.0 );   // v6
    vertices[7] = vec4(  0.5, -0.5, -0.5, 1.0 );    // v7

    vertex_colors[0] =   vec4( 0.0, 0.0, 0.0, 1.0 );  // v0
    vertex_colors[1] =   vec4( 1.0, 0.0, 0.0, 1.0 );  // v1
    vertex_colors[2] =   vec4( 1.0, 1.0, 0.0, 1.0 );  // v2
    vertex_colors[3] =   vec4( 0.0, 1.0, 0.0, 1.0 );  // v3
    vertex_colors[4] =  vec4( 0.0, 0.0, 1.0, 1.0 );  // v4
    vertex_colors[5] =  vec4( 1.0, 0.0, 1.0, 1.0 );  // v5
    vertex_colors[6] =  vec4( 1.0, 1.0, 1.0, 1.0 );  // v6
    vertex_colors[7] =  vec4( 0.0, 1.0, 1.0, 1.0 );  // v7

// outward facing normals. Use right hand rule to determine the normal direction (wrap fingers
// of right hand along the direction of the face's vertices, then the thumb points in the
// direction of the normal.)
    face_normals[0] = vec4(  1.0,  0.0,  0.0, 0.0 );  // +x  0
    face_normals[1] = vec4( -1.0,  0.0,  0.0, 0.0 );  // -x  1
    face_normals[2] = vec4(  0.0,  1.0,  0.0, 0.0 );  // +y  2
    face_normals[3] = vec4(  0.0, -1.0,  0.0, 0.0 );  // -y  3
    face_normals[4] = vec4(  0.0,  0.0,  1.0, 0.0 );  // +z  4
    face_normals[5] = vec4(  0.0,  0.0, -1.0, 0.0 );  // -z  5

    int i = 0;
    int &index = i;  // want to pass by reference and not value.
    quad(index, vertices[1], vertices[0], vertices[3], vertices[2] , vertex_colors[2], face_normals[4]); // front (+z) face
    quad(index, vertices[2], vertices[3], vertices[7], vertices[6] , vertex_colors[1], face_normals[0]); // +x
    quad(index, vertices[3], vertices[0], vertices[4], vertices[7] , vertex_colors[3], face_normals[3]); // -y
    quad(index, vertices[6], vertices[5], vertices[1], vertices[2] , vertex_colors[4], face_normals[2]); // +y
    quad(index, vertices[4], vertices[5], vertices[6], vertices[7] , vertex_colors[5], face_normals[5]); // -z
    quad(index, vertices[5], vertices[4], vertices[0], vertices[1] , vertex_colors[6], face_normals[1]); // -x

    //printArrays();
}

// ---------------------------------------------------------------------- quad
// This is a helper function which generates the vertex attributes (points, color,
// normals, texture coordinates) for a single face of the cube. We will call
// this 6 times, once for each face.
void
Cube::quad(int &index, vec4 v1, vec4 v2, vec4 v3, vec4 v4, vec4 col, vec4 norm)
{
    float texMax = 1;
    colors[index] = col;
    points[index] = v1;
    normals[index] = norm;
    tex_coords[index] = vec2(0,0);
    index++;
    colors[index] = col;
    points[index] = v2;
    normals[index] = norm;
    tex_coords[index] = vec2(texMax,0);
    index++;
    colors[index] = col;
    points[index] = v3;
    normals[index] = norm;
    tex_coords[index] = vec2(texMax,texMax);
    index++;
    colors[index] = col;
    points[index] = v1;
    normals[index] = norm;
    tex_coords[index] = vec2(0,0);
    index++;
    colors[index] = col;
    points[index] = v3;
    normals[index] = norm;
    tex_coords[index] = vec2(texMax,texMax);
    index++;
    colors[index] = col;
    points[index] = v4;
    normals[index] = norm;
    tex_coords[index] = vec2(0,texMax);
    index++;
}







