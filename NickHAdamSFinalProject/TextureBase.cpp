// base texture object
#include "TextureBase.h"

#include <iostream>
using std::cout;

TextureBase::TextureBase(): width(0), height(0)
{}

TextureBase::TextureBase(int w, int h): width(w), height(h){
}

TextureBase::~TextureBase()
{}

void
TextureBase::setUp(GLuint program)
{
    // Create a texture object
    glGenTextures( 1, &textureID );
    // Binds the texture object (i.e. makes it the "current" texture.)
    glBindTexture( GL_TEXTURE_2D, textureID );
    // Load the image data into the texture, send to GPU
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)image );
    // Set texture parameters
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT  );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    // Selects which texture unit is to be active. In this case, the texture unit is GL_TEXTURE0
    // see http://www.opengl.org/wiki/Texture#Texture_image_units
    // Note, the shader program will reference this texture unit.
    glActiveTexture( GL_TEXTURE0 );
    // Binds the texture object to the active texture unit GL_TEXTURE0.
    glBindTexture( GL_TEXTURE_2D, textureID );

    // associate this texture object with the "texture" uniform variable in the shader program
    glUniform1i( glGetUniformLocation(program, "texture"), 0 );

}


void
TextureBase::bind(GLuint program)
{
    glBindTexture( GL_TEXTURE_2D, textureID );
    glUniform1i( glGetUniformLocation(program, "texture"), 0 );
}


