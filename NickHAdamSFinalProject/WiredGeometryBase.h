// This is the base class for all the geometry classes: Cube, Disk, etc

#ifndef WIREDGEOMETRYBASE_H
#define WIREDGEOMETRYBASE_H

#include "Angel.h"

class WiredGeometryBase
{
    public:
        WiredGeometryBase();
        virtual ~WiredGeometryBase();
        WiredGeometryBase(const WiredGeometryBase& other);
        WiredGeometryBase& operator=(const WiredGeometryBase& other);

        GLuint vao;             // index for vertex array object
        GLenum mode;            // e.g.  GL_TRIANGLES, GL_LINES, etc
        int numVertices;        // length of the arrays (points, colors, etc)
        vec4 *points;
        vec4 *colors;

        void createBuffers(GLint _program );
        void printArrays();
        void draw();
    protected:
    private:
};

#endif // GEOMETRYBASE_H
