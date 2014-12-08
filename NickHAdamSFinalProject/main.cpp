//@file main.cpp
//@author Nick Handy and Adam Smith
//@date November 25th, 2014
//@description Displays a car at the origin. The purpose of this program is to demonstrate
// navigation capabilities - "fly through"  or "Maya controls - tumble, dolly, track. For
// this project the function implemented is Tumble.


#include "Angel.h"
#include <iostream>
using std::cout;

#include "MatrixStack.h"
#include "Shapes.h"
#include "Car.h"
#include "Person.h"

//********  These are available as extern variables in Globals.h **************
GLuint  projection; // projection matrix uniform shader variable location
GLuint  model_view;  // model-view matrix uniform shader variable location
GLuint  model_color;  // model-view matrix uniform shader variable location
GLuint program;  // shader program

MatrixStack mvMatrixStack;  // stores the movel view matrix stack
Shapes shapes;
//********  End extern variables in Globals.h **************

int windowX = 512;
int windowY = 512;

Person person; //a default person centered at origin
//Person person(5,2,-10,8,2); //a person at different coordinates
float personSpeed = 0.4;

// Camera projection transformation parameters
GLfloat  fovy = 45.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 100.0;

// Camera location and orientation parameters
vec4 eyeStart = vec4( 0.0 , 20.0, 30.0 , 1.0); // initial camera location
vec4 eye = eyeStart; // initial camera location - used when reseting parameters
vec4 VPN(0, 0.5, 1, 0);  // used as starting value for setting uvn and the viewRotation
vec4 VUP(0, 1, 0, 0);  // used as starting value for setting uvn and the viewRotation
mat4 viewRotation;  // rotational part of matrix V that transforms between World and Camera coordinates

float alpha = 1.0;  // used to control the amount of a turn during the flythrough

// For controlling Mouse Actions:
enum  actions { TUMBLE, TRACK, DOLLY };
GLint   action;
int     xStart = 0.0, yStart = 0.0;
int t = 0;    // toggles the tumble point between the origin and fixed distance (d) from eye. Starts out at origin
float d = 30; // fixed distance of tumble point in front of camera

//---------------------------------------------------------------------------- printControls
// calculate viewRotation from VPN and VUP
void calcUVN(vec4 VPN, vec4 VUP)
{
    // For example, to cross two *vectors* (not points) stored as vec4's and to save result in a vec4 requires following:
    //a = vec4(cross(b,c),0);
    vec4 n = normalize(VPN);
    vec4 u = vec4(cross(VUP, VPN), 0);
    u = normalize(u);
    vec4 v = vec4(cross(n,u), 0);
    viewRotation = mat4(u, v, n, vec4(0, 0, 0, 1));
}

//---------------------------------------------------------------------------- print controls

void printControls()
{
    cout << "\n\n************  Controls **************" << "\n";
    cout << "q or Q ............ quit" << "\n";
    cout << "f ................. move car forward" << "\n";
    cout << "b ................. move car backward" << "\n";
    cout << "r ................. reset parameters" << "\n";
    cout << "Up arrow .......... turn up" << "\n";
    cout << "Down arrow ........ turn down" << "\n";
    cout << "Right arrow ....... turn right" << "\n";
    cout << "Insert key ........ roll left" << "\n";
    cout << "Page Up ........... roll right" << "\n";
    cout << "Home key .......... move camera forward" << "\n";
    cout << "End key ........... move camera backward" << "\n";
    cout << "Right Mouse drag .. pan up/down/left/right" << "\n";
    cout << "Middle Mouse drag . zoom in/out" << "\n";
    cout << "Left Mouse drag ... tumble about origin or white cube" << "\n";
    cout << "t ................. toggles the tumble point between origin and fixed distance"  << "\n";
    cout << "                    in front of camera. Starts at origin." << "\n";
}

//---------------------------------------------------------------------------- init
// OpenGL initialization
void
init()
{
    calcUVN(VPN, VUP);

    program = InitShader( "U:\\CPSC325\\GitHub\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\vertex.glsl", "U:\\CPSC325\\GitHub\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\fragment.glsl" );
    //program = InitShader( "U:\\documents\\cpsc325\\Final Project\\NickHAdamSFinalProject\\vertex.glsl", "U:\\documents\\cpsc325\\Final Project\\NickHAdamSFinalProject\\fragment.glsl" );
    //program = InitShader( "C:\\Users\\yerion\\Documents\\graphics2014\\Tumble8\\NickHAdamSTumble8\\vertex.glsl", "C:\\Users\\yerion\\Documents\\graphics2014\\Tumble8\\NickHAdamSTumble8\\fragment.glsl" );
    glUseProgram( program );
    // Uniform variables: color and viewing parameters
    model_color = glGetUniformLocation( program, "model_color" );
    model_view = glGetUniformLocation( program, "model_view" );
    projection = glGetUniformLocation( program, "projection" );

    shapes.createVAO(program);

    glUniform4fv( model_color, 1,vec4(1,1,1,1) ); // set color to white initially

    glLineWidth(1);
    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    printControls();
}

//---------------------------------------------------------------------------- drawAxes
// Draw coordinate axes - x is red, y is green, and z is blue
void drawAxes(mat4 &mv)
{
    mvMatrixStack.pushMatrix(mv);

    mv = mv * Scale(.1, 30, .1);
    mv = mv * Translate(0, .5, 0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    glUniform4fv( model_color, 1,vec4(0,1,0,1) );
    shapes.myCylinder.draw();               // y axis
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * RotateX(-90);
    mv = mv * Scale(.1, 30, .1);
    mv = mv * Translate(0, .5, 0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    glUniform4fv( model_color, 1,vec4(0,0,1,1) );
    shapes.myCylinder.draw();   // z axis
    mv = mvMatrixStack.popMatrix();

    mvMatrixStack.pushMatrix(mv);
    mv = mv * RotateZ(-90);
    mv = mv * Scale(.1, 30, .1);
    mv = mv * Translate(0, .5, 0);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    glUniform4fv( model_color, 1,vec4(1,0,0,1) );
    shapes.myCylinder.draw();   // x axis
    mv = mvMatrixStack.popMatrix();
}

//---------------------------------------------------------------------------- display

void
display( void )
{
    // clear the color and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // calculate and set camera projection parameters:
    mat4  p  = Perspective( fovy, aspect, zNear, zFar );
    glUniformMatrix4fv( projection, 1, GL_TRUE, p );

    mat4 mv;  // modelview matrix

    // Draw a cube which is *always* a distance d in front of the camera.
    // This cube is for reference only.  TUMBLE rotations can be about this point.
    // Do you see why the cube needs to be drawn *before* we move and orient the camera (i.e. before the View is set).
    ///mv = mv * Translate(0,0,-d);
    ///glUniformMatrix4fv( model_view, 1, GL_TRUE,mv  );
    ///shapes.drawCube(vec4(1,1,1,1));
    ///drawAxes(mv);  // draw coordinate axis that are centered on the reference cube
    // End: reference cube

    // Set the View matrix which controls the camera orientation and location
    mvMatrixStack.loadIdentity();

    // SET THE CAMERA VIEW MATRIX: mv =  V = viewRotation times EyeTranslation
    mv = viewRotation * Translate(-eye);

    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    ///drawAxes(mv); // draw coordinate axis that are centered at the origin of the World Coordinate System.

    // Draw the People
    person.drawPerson(mv);
    // End: person

    // Draw the ground
    mv = mv * Translate(0, -.1, 0);
    mv = mv * Scale(40, .2, 40);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(.6, .4, .3, 1));
    // End: ground

    glBindVertexArray( 0 );
    glutSwapBuffers();
}

//---------------------------------------------------------------------------- keyboard

void
keyboard( unsigned char key, int x, int y )
{
    float personRadians = person.personAngle * 3.14159 / 180;
    switch( key )
    {
    case 033: // Escape Key
    case 'w': // moves player forward
        person.zLoc -= personSpeed * cos(personRadians);
        person.xLoc += personSpeed * sin(personRadians);
        eye.z -= personSpeed * cos(personRadians);
        eye.x += personSpeed * sin(personRadians);
        person.Walk();
        break;
    case 'a': // moves player left
        person.zLoc -= personSpeed * sin(personRadians);
        person.xLoc -= personSpeed * cos(personRadians);
        eye.z -= personSpeed * sin(personRadians);
        eye.x -= personSpeed * cos(personRadians);
        break;
    case 's': // moves player backward
        person.zLoc += personSpeed * cos(personRadians);
        person.xLoc -= personSpeed * sin(personRadians);
        eye.z += personSpeed * cos(personRadians);
        eye.x -= personSpeed * sin(personRadians);
        break;
    case 'd': // moves player right
        person.zLoc += personSpeed * sin(personRadians);
        person.xLoc += personSpeed * cos(personRadians);
        eye.z += personSpeed * sin(personRadians);
        eye.x += personSpeed * cos(personRadians);
        break;
    case 'q':
    case 'Q':
        exit( EXIT_SUCCESS );
        break;
    case 'f':
        person.armAngle += 5;
       break;
    case 'g':     // drive car backward
        person.armAngle -= 5;
        break;
    case 't':     // toggle tumblepoint
        t = (t + 1) % 2;
        break;
    case 'r':     // reset
        t = 0;  // tumble point at origin
        //car.wheelAngle = 0;
        //car.xLoc = 0;
        person.xLoc = 0;
        person.yLoc = 0;
        person.zLoc = 0;
        eye = eyeStart; // camera location
        calcUVN(VPN,VUP);
        xStart = 0.0;
        yStart = 0.0;
        break;
    }

    glutPostRedisplay();
}

//---------------------------------------------------------------------------- keySpecial
void
keySpecial( int key, int x, int y )
{

    switch( key )
    {
    case GLUT_KEY_UP:   // rotate up around Camera's x
        viewRotation = RotateX(alpha) * viewRotation;
        cout << "KEY_UP";
        break;
    case GLUT_KEY_DOWN: // rotate down around Camera's x
        viewRotation = RotateX(-alpha) * viewRotation;
        cout << "KEY_DOWN";
        break;
    case GLUT_KEY_LEFT: // rotate around Camera's y
        viewRotation = RotateY(alpha) * viewRotation;
        cout << "KEY_LEFT";
        break;
    case GLUT_KEY_RIGHT: // rotate around Camera's y
        viewRotation = RotateY(-alpha) * viewRotation;
        cout << "KEY_RIGHT";
        break;
    case GLUT_KEY_HOME:  // Move camera in -n direction
        //Line 544 in mat.h allows indexing of mat4 matrix
        eye = eye - alpha * viewRotation[2];
        cout << "KEY_HOME";
        break;
    case GLUT_KEY_END:  //Move camera in +n direction
        eye = eye + alpha * viewRotation[2];
        cout << "KEY_END";
        break;
    case GLUT_KEY_INSERT: //Rotate camera around its z axis towards the left
        viewRotation = RotateZ(alpha) * viewRotation;
        cout << "KEY_INSERT";
        break;
    case  GLUT_KEY_PAGE_UP : //Rotate camera around its z axis towards the right
        viewRotation = RotateZ(-alpha) * viewRotation;
        cout << "KEY_PAGE_UP";
        break;
    }
        //Print u, v, n
        printf(" : %f, %f,  %f, %f\n", viewRotation[0][0], viewRotation[0][1], viewRotation[0][2], viewRotation[0][3]);
        printf("            : %f, %f,  %f, %f\n", viewRotation[1][0], viewRotation[1][1], viewRotation[1][2], viewRotation[1][3]);
        printf("            : %f, %f,  %f, %f\n", viewRotation[2][0], viewRotation[2][1], viewRotation[2][2], viewRotation[2][3]);
    glutPostRedisplay();
}

//---------------------------------------------------------------------------- mouse
void
mouse( GLint button, GLint state, GLint x, GLint y )
{
    static GLint buttons_down = 0;

    if (state == GLUT_DOWN)
    {
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            // cout << "     mouse: GLUT_LEFT_BUTTON - TUMBLE\n";
            action = TUMBLE;
            xStart = x;
            yStart = y;
            printf("mouse: button = %d", button);
            printf(" state = %d", state);
            printf(" x,y = %d , %d\n", x, y);
            break;
        case 3: //Mouse roll forward
            //  cout << "     mouse: GLUT_MIDDLE_BUTTON - DOLLY\n";
            eye = eye - 1.1 * viewRotation[2];//Toward point
            printf("mouse: button = %d", button);
            printf(" state = %d", state);
            printf(" x,y = %d , %d\n", x, y);
            glutPostRedisplay();
            break;
        case 4: //Mouse roll backward
            //  cout << "     mouse: GLUT_MIDDLE_BUTTON - DOLLY\n";
            eye = eye + 1.1 * viewRotation[2];//Away from point
            printf("mouse: button = %d", button);
            printf(" state = %d", state);
            printf(" x,y = %d , %d\n", x, y);
            glutPostRedisplay();
            break;
        case GLUT_RIGHT_BUTTON:
            //  cout << "     mouse: GLUT_RIGHT_BUTTON - TRACK\n";
            action = TRACK;
            xStart = x;
            yStart = y;
            printf("mouse: button = %d", button);
            printf(" state = %d", state);
            printf(" x,y = %d , %d\n", x, y);
            break;
        }
    }
}

//---------------------------------------------------------------------------- tumble
// tumble about to location tumblePoint in World Coordinate System.
void tumble(mat4 rx, mat4 ry, vec4 tumblePoint)
{
    //Declaring mat4 and vec4
    mat4 view, transformationY, transformationX, newView, rotationInverse;
    vec4 tumblePointInCCS;

   //Transforms viewRotation to the CCS
   view = viewRotation * Translate(-eye);
   //Transforms the tumblePoint to CCS
   tumblePointInCCS = view * tumblePoint;
   //Rotate in CCS about tumblePointInCCS around the u axis in CCS
   transformationX = Translate(tumblePointInCCS) * rx * Translate(-tumblePointInCCS);
   //Rotate in WCS about the point tumblePoint around the y axis in WCS
   transformationY = Translate(tumblePoint) * ry * Translate(-tumblePoint);
   //maps WCS to CCS
   newView = transformationX * view * transformationY;
   //Maps CCS to WCS
   rotationInverse = transpose(newView);
   //Getting rid of translations
   rotationInverse[3] = vec4(0, 0, 0, 1);
   //Find eye in WCS
   eye = -(rotationInverse * newView * vec4(0, 0, 0, 1));
   //set the new value of view to our original viewRotation
   viewRotation = newView;
   //standard last column for a rotation matrix.
   viewRotation[0][3] = 0;
   viewRotation[1][3] = 0;
   viewRotation[2][3] = 0;
   viewRotation[3][3] = 1;
}

//---------------------------------------------------------------------------- motion
void
motion( GLint x, GLint y )
{
    float dx, dy;
    mat4 ry, rx;
    vec4 tumblePoint;

    switch (action)
    {
    case TUMBLE:
        dx = 0.05 * (x - xStart);
        dy = 0.05 * (y - yStart);

        ry = RotateY(10*dx);
        rx = RotateX(10*dy);

        person.personAngle += 10 * dx; //Changes the value of the person's y-rotation

        // tumble about a point tumblePoint in WCS. Two options currently.
        if (t == 0)   // tumble about origin in  WCS
        {
            tumblePoint =  vec4(person.xLoc, person.yLoc, person.zLoc,1);
            //tumblePoint =  vec4(0,0,0,1);
        }
        else        // tumble about fixed distance in front of camera in  WCS
        {
            tumblePoint =   eye - d * viewRotation[2];
            tumblePoint[3] = 1;
        }

        tumble(rx, ry, tumblePoint);

        xStart = x;
        yStart = y;
        break;
    case TRACK:  // PAN
        dx = -0.05 * (x - xStart);
        dy = 0.05 * (y - yStart);
        eye = eye + dx * viewRotation[0]; //Left/Right
        eye = eye + dy * viewRotation[1]; //Up/Down

        xStart = x;
        yStart = y;
        break;
    case DOLLY:
        dy = 0.05 * (y - yStart);
        dx = 0.05 * (x - xStart);
        eye = eye + dx * viewRotation[2];//Forward
        eye = eye - dy * viewRotation[2];//Backward
        xStart = x;
        yStart = y;
        break;
    default:
        printf("unknown action %d\n", action);
    }

    glutPostRedisplay();
}


//---------------------------------------------------------------------------- reshape

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    aspect = GLfloat(width)/height;
}

//---------------------------------------------------------------------------- main

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( windowX, windowY );
//    glutInitContextVersion( 3, 3 );
//    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Camera Navigation" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutSpecialFunc(keySpecial);
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutReshapeFunc( reshape );

    glutMainLoop();
    return 0;
}
