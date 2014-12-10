// author: Dr. Jenny Orr of Willamette with help from textbook author
//
// Displays a car at the origin with movement controls. this version
// illustrates the use of a checkboard textrue defined in a class Checkerboard
// and another texture from a tga file

#include "Angel.h"
#include <iostream>
using std::cout;

#include "MatrixStack.h"
#include "Shapes.h"
#include "Car.h"
#include "Axes.h"
#include "Globals.h"
#include "LightingShading.h"
#include "Checkerboard.h"
#include "ImageTexture.h"
#include "Person.h"
#include "WorldEnvironment.h"
//********  These are available as extern variables in Globals.h **************
GLuint  projection; // projection matrix uniform shader variable location
GLuint  model_view;   // model-view matrix uniform shader variable location
GLuint  model_color;  // uniform shader variable location for color
GLuint color_source;  // flag to choose between using a texture (0), vColor (1), or model_color (2) in the shader
GLuint program;  // shader programs
MatrixStack mvMatrixStack;  // stores the model view matrix stack
Shapes shapes;
//********  End extern variables in Globals.h **************

//Camera camera;
LightingShading lightingShading;

Checkerboard checkerboard;

// I tried .gif, .jped, .tga where .tga works on XP OS
//ImageTexture myImageTexture("bulldog.gif");

//ImageTexture myImageTexture("test.tga");

char *myString1 = "U:\\documents\\cpsc325\\Final Project\\Git\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\test.tga";
ImageTexture myImageTexture(myString1);

char *myString2 = "U:\\documents\\cpsc325\\Final Project\\Git\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\wood_texture.tga";
ImageTexture myWoodTexture(myString2);

char *myString3 = "U:\\documents\\cpsc325\\Final Project\\Git\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\textures\\rock_02_textures\\rock_02_dif.tga";
ImageTexture myStoneTexture(myString3);


float animateAngle = 0;  // used for animation

//Car myCar;
Person person; //a default person centered at origin.
WorldEnvironment environment;

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

bool animateOn = true;

Axes axes;

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

//---------------------------------------------------------------------------- printControls

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
    //camera.calcUVN();

   // program = InitShader( "vertex.glsl", "fragment.glsl" );
    //program = InitShader( "vertexGouraud.glsl", "fragmentGouraud.glsl" );
    program = InitShader( "U:\\documents\\cpsc325\\Final Project\\Git\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\vertexPhong.glsl", "U:\\documents\\cpsc325\\Final Project\\Git\\Nick_Adam_CPSC_325_Final_Project\\NickHAdamSFinalProject\\fragmentPhong.glsl" );
    //program = InitShader( "C:\\Users\\yerion\\Documents\\graphics2014\\TexturesLab\\vertexPhong.glsl", "C:\\Users\\yerion\\Documents\\graphics2014\\TexturesLab\\fragmentPhong.glsl" );
    glUseProgram(program );
    lightingShading.setUp(program);

    checkerboard.setUp(program);
    myImageTexture.setUp(program);
    myWoodTexture.setUp(program);
    myStoneTexture.setUp(program);

    // Uniform variables
    model_color = glGetUniformLocation( program, "model_color" );
    model_view  = glGetUniformLocation( program, "model_view" );
    projection  = glGetUniformLocation( program, "projection" );
    color_source = glGetUniformLocation( program, "color_source" );

    glLineWidth(2);  // sets the thickness of the line for the wired shapes
    shapes.createBuffers(program);

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    printControls();
}

//---------------------------------------------------------------------------- drawGround

void drawGround(mat4 mv)
{
// Draw the ground
    mvMatrixStack.pushMatrix(mv);
    mv = mv * Translate(0,-.1,0);
    mv = mv * Scale(30,.2,30);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    shapes.drawCube(vec4(.8,.6,.3,1));
    mv = mvMatrixStack.popMatrix();
}

//----------------------------------------------------------- display

void
display( void )
{
    // clear the color and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // calculate and set camera projection parameters:
    //mat4  p = camera.calcPerspective();
    mat4  p  = Perspective( fovy, aspect, zNear, zFar );
    glUniformMatrix4fv( projection, 1, GL_TRUE, p );


    mat4 mv;  // modelview matrix

    // Initialize the modelview matrix to contain the camera orientation and location
    mvMatrixStack.loadIdentity();

    //mv =  camera.viewRotation * Translate( -camera.eye );
    mv = viewRotation * Translate(-eye);

    //Transform light to eye coordinates which is what shader expect)
    vec4 l_position = mv * RotateZ(animateAngle) * lightingShading.light_position;
    glUniform4fv( glGetUniformLocation(program, "light_position"),
                  1, l_position );
     // draw a cube at the light position
    mvMatrixStack.pushMatrix(mv);
    mv = mv * RotateY(animateAngle);
    mv = mv * Translate(lightingShading.light_position);
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    checkerboard.bind(program);
    shapes.drawCube(vec4(1,1,0,1));
    mv = mvMatrixStack.popMatrix();
    myImageTexture.bind(program);
    glUniform1i(color_source,1);  //  texture=0, vColor=1, model_color=2
    axes.draw(mv, 1);



    myWoodTexture.bind(program);
    //myStoneTexture.bind(program);
    glUniform1i(color_source,0);  //  texture=0, vColor=1, model_color=2
    environment.drawWorldEnvironment(mv);

    mvMatrixStack.pushMatrix(mv);
    checkerboard.bind(program);
    person.drawPerson(mv);


    glBindVertexArray( 0 );
    glutSwapBuffers();
}

//---------------------------------------------------------------------------- isHit
bool
isHit(float radians)
{
    float zDistance = person.movementSpeed * cos(radians);
    float xDistance = person.movementSpeed * sin(radians);
    if(person.xLoc + xDistance < -300  && person.xLoc + xDistance > -200 && person.zLoc + zDistance < 20 && person.zLoc + zDistance > -20)
        return true;
    else
        return false;
}



//---------------------------------------------------------------------------- keyboard

void
keyboard( unsigned char key, int x, int y )
{
    float radians = person.personAngle * 3.14159 / 180;

    switch( key )
    {
    case 033: // Escape Key
    case 'q':
    case 'Q':
        exit( EXIT_SUCCESS );
        break;
    case 'w': // moves player forward
        if(!isHit(radians)){
            person.moveForward(radians);
            eye.z -= person.movementSpeed * cos(radians);
            eye.x += person.movementSpeed * sin(radians);
        }
        break;
    case ' ':     // drive car forward
            //person.jump();
        break;
    case 'b':     // drive car forward
        //myCar.wheelAngle -= 5;
        //myCar.xLoc += 2 * M_PI * 2. * 5 / 360.;
        break;
    case 't':     // toggle tumblepoint
        //camera.toggle();
        break;
    case 'r':     // reset
        //camera.reset();
        break;
    case 's':     // reset
        animateOn = !animateOn;
        break;
    }

    glutPostRedisplay();
}

void keySpecial( int key, int x, int y )
{
    //camera.keySpecial(key,x,y);
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
//---------------------------------------------------------------------------- motion, mouse

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

// Mouse controls
void
motion( GLint x, GLint y )
{
    //camera.tumblePoint = vec4(person.xLoc, person.yLoc, person.zLoc,1);
    //camera.motion(x,y);
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

void
mouse( GLint button, GLint state, GLint x, GLint y )
{
    //camera.mouseControl(button,state,x,y);

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

//---------------------------------------------------------------------------- reshape

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    aspect = GLfloat(width)/height;
    //camera.aspect = GLfloat(width)/height;
}

void idle()
{
    if (animateOn) animateAngle += 0.01;
    //if (animateAngle < 0) animateAngle = 0;

    glutPostRedisplay();
}


//---------------------------------------------------------------------------- main

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );

    glutCreateWindow( "Navigation with Textures" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutSpecialFunc(keySpecial);
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutReshapeFunc( reshape );
    glutIdleFunc(idle); //  need for animation but not mouse interaction

    glutMainLoop();
    return 0;
}
