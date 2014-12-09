// This is the base class for all the geometry classes: Cube, Disk, etc

#ifndef GEOMETRYBASE_H
#define GEOMETRYBASE_H

#include "Angel.h"

class GeometryBase
{
    public:
        GeometryBase();
        virtual ~GeometryBase();
        GeometryBase(const GeometryBase& other);
        GeometryBase& operator=(const GeometryBase& other);

        GLuint vao;             // index for vertex array object
        GLenum mode;            // e.g.  GL_TRIANGLES, GL_LINES, etc
        int numVertices;        // length of the arrays (points, colors, etc)
        vec4 *points;
        vec4 *colors;
        vec4 *normals;
        vec2 *tex_coords;

        void createBuffers(GLint _program );
        void printArrays();
        void draw();
    protected:
    private:
};

#endif // GEOMETRYBASE_H
