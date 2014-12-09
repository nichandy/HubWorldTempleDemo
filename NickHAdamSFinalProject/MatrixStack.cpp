// Represents a stack for storing the 4x4 modelview matrix.

#include "MatrixStack.h"



// ---------------------------------------------------------------------- default constructor

MatrixStack::MatrixStack()
{
   // mat4 id(1);
    m.push(mat4(1));
}

// ---------------------------------------------------------------------- destructor
MatrixStack::~MatrixStack()
{
    //dtor
}

// ---------------------------------------------------------------------- loadIdentity
// Resets the stack so it holds only the identity
void
MatrixStack::loadIdentity() {
     // clear stack
    while ( ! m.empty() )
    {
        m.pop();
    }
    m.push(mat4(1));
}

// ---------------------------------------------------------------------- pushMatrix
// Push an item onto the stack
void
MatrixStack::pushMatrix(mat4 mm){
    m.push(mm);
}

// ---------------------------------------------------------------------- popMatrix
// pop an item off of the matrix and return popped item
mat4
MatrixStack::popMatrix(){
    mat4 t = m.top();
    m.pop();
    return t;
}
