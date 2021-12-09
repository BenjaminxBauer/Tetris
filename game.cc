// ** Add Header Comments **

#include <Angel.h>
#include <iostream>
#include <stdlib.h>
#include "i.h"
#include "o.h"
#include "t.h"
#include "j.h"
#include "l.h"
#include "s.h"
#include "z.h"

// Bool to determine whether to clear the screen
bool clear=true;

// Bool to determine whether to update the animation
bool updating=true;

// Pointer to the Iobject (must be initialized after
// initialization of shaders, so leave it as a pointer.
I*I_Tetromino;
O*O_Tetromino;
T*T_Tetromino;
J*J_Tetromino;
L*L_Tetromino;
S*S_Tetromino;
Z*Z_Tetromino;

// Data storage for our geometry for the lines
vec2 *points;

// How big a Ito draw.
GLfloat size=30.0;

// Window Size 
GLint windowSizeLoc;

// Window size
int win_h=0;
int win_w=0;

// Initial parameters of the ellipses
GLfloat angular_offset=3.14;
GLfloat angular_velocity=1.0/230.0;
GLfloat minor_axis=100.0;
GLfloat major_axis=150.0;

// Simple display draws a Iof size sq_size*2 around mouse
// location.
extern "C" void display()
{
  // What happens if the following is commented out?  Explain.
  if (clear) {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  I_Tetromino->draw();
  O_Tetromino->draw();
  T_Tetromino->draw();
  J_Tetromino->draw();
  L_Tetromino->draw();
  S_Tetromino->draw();
  Z_Tetromino->draw();
  

  glutSwapBuffers ();
}


// Maintains the mapping from screen to world coordinates.
extern "C" void myReshape(int w, int h)
{
  glViewport(0,0,w,h);
  win_h = h;
  win_w = w;
  glUniform2f(windowSizeLoc, win_w, win_h);       // Pass the window size
						  // size
  glutPostRedisplay();
}

// Example menu code.
extern "C" void myMenu(int value)
{
  switch (value) {
  case 1:
    // Clear screen
    glClear (GL_COLOR_BUFFER_BIT);
    break;
  case 2:
    // Set clear color to red
    glClearColor (1.0, 0.0, 0.0, 1.0);
    break;
  case 3:
    // Set clear color to black
    glClearColor (0.0, 0.0, 0.0, 1.0);
    break;
  default:
    break;
  }
  glutPostRedisplay(); 
}


// Create menu and items.
// %%%
// %%% What happens if we change the menu's numbering scheme?
// %%%
void setupMenu()
{
  glutCreateMenu(myMenu);
  glutAddMenuEntry("clear screen", 1);
  glutAddMenuEntry("red background", 2);
  glutAddMenuEntry("black background", 3);
  /*  glutAddMenuEntry("The Answer", 42);
  glutAddMenuEntry("clear screen", 32);
  glutAddMenuEntry("red background", 22);
  glutAddMenuEntry("black background", 12);*/

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialize all OpenGL callbacks, create window.
void myinit()
{
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(900,900);
  glutInitWindowPosition(20,20);

  glutCreateWindow("Tetris");

  // Color initializations
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  // Can you do this?  Attach a menu to a button already
  // used for something else?  
  setupMenu();

  // Callbacks
  glutDisplayFunc(display);  
  glutReshapeFunc (myReshape);
}

// This function initializes the buffers and shaders
void init()
{
  // Locations of variables in shaders.
  // Offset of square
  GLint offsetLoc;
  // Size of square
  GLint sizeLoc;
  // Color of I
  GLint colorLoc;

  // Create a vertex array object on the GPU
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create and initialize a buffer object for transferring data to
  // the GPU.
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("vshader.glsl", "fshader.glsl");

  // InitShader does the glUseProgram
  // So the following would be redundant
  // glUseProgram(program);

  // Initialize the vertex position attribute from the vertex shader
  windowSizeLoc = glGetUniformLocation(program, "windowSize");
  if (windowSizeLoc==-1) {
    std::cerr << "Unable to find windowSize parameter" << std::endl;
  }

  offsetLoc  = glGetUniformLocation(program, "offset");
  if (offsetLoc==-1) {
    std::cerr << "Unable to find offsetLoc parameter" << std::endl;
  }

  sizeLoc  = glGetUniformLocation(program, "size");
  if (sizeLoc==-1) {
    std::cerr << "Unable to find sizeLoc parameter" << std::endl;
  }

  colorLoc  = glGetUniformLocation(program, "vcolor");
  if (colorLoc==-1) {
    std::cerr << "Unable to find colorLoc parameter" << std::endl;
  }

  GLint loc = glGetAttribLocation(program, "vPosition");
  if (loc==-1) {
    std::cerr << "Unable to find vPosition parameter" << std::endl;
  }
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


  glUniform2f(offsetLoc, 0.0, 0.0);               // Initial offset
						  // for mouse loc.

  // We need just one square and circle to draw any number of them.
  points = new vec2[I::NumPoints+O::NumPoints+T::NumPoints+J::NumPoints+L::NumPoints+S::NumPoints+Z::NumPoints];
  //points = new vec2[Z::NumPoints];

  // Build the I tetromino
  I_Tetromino = new I(0, points, offsetLoc, sizeLoc, colorLoc);
  I_Tetromino->change_size(size);
  I_Tetromino->move(50, 450);
  I_Tetromino->selectColor(1.0/255.0, 0.0, 0.0);
  I_Tetromino->color(0.0f, 1.0f, 1.0f);

  // Build the O tetromino
  O_Tetromino = new O(I::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  O_Tetromino->change_size(size);
  O_Tetromino->move(200, 425);
  O_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  O_Tetromino->color(1.0f, 1.0f, 0.0f);

  // Build the T tetromino
  T_Tetromino = new T(I::NumPoints+O::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  T_Tetromino->change_size(size);
  T_Tetromino->move(325, 450);
  T_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  T_Tetromino->color(0.99f, 0.43f, 0.78f);

  // Build the J tetromino
  J_Tetromino = new J(I::NumPoints+O::NumPoints+T::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  J_Tetromino->change_size(size);
  J_Tetromino->move(450, 450);
  J_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  J_Tetromino->color(0.0f, 0.0f, 1.0f);

  // Build the L tetromino
  L_Tetromino = new L(I::NumPoints+O::NumPoints+T::NumPoints+J::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  L_Tetromino->change_size(size);
  L_Tetromino->move(550, 450);
  L_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  L_Tetromino->color(1.0f, 0.5f, 0.0f);

  S_Tetromino = new S(I::NumPoints+O::NumPoints+T::NumPoints+J::NumPoints+L::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  S_Tetromino->change_size(size);
  S_Tetromino->move(650, 450);
  S_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  S_Tetromino->color(0.0f, 1.0f, 0.0f);

  Z_Tetromino = new Z(I::NumPoints+O::NumPoints+T::NumPoints+J::NumPoints+L::NumPoints+S::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  Z_Tetromino->change_size(size);
  Z_Tetromino->move(800, 450);
  Z_Tetromino->selectColor(2.0/255.0, 0.0, 0.0);
  Z_Tetromino->color(1.0f, 0.0f, 0.0f);

  // Send the data to the graphics card, after it has been generated
  // by creating the objects in the world (above).
  glBufferData(GL_ARRAY_BUFFER, (I::NumPoints+O::NumPoints+T::NumPoints+J::NumPoints+L::NumPoints+S::NumPoints+Z::NumPoints)*sizeof(vec2), points, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, (Z::NumPoints)*sizeof(vec2), points, GL_STATIC_DRAW);
}

//  Main Program
int main(int argc, char** argv)
{
  // Several people forgot to put in the following line.  This is an
  // error, even if it still works on your machine, a program is
  // incorrect without the following call to initialize GLUT.
  glutInit(&argc,argv);

  myinit();             // set window attributes, and initial data

  // Initialize the "magic" that glues all the code together.
  glewInit();

  init();               // set up shaders and display environment

  glutMainLoop();       // enter event loop

  return(EXIT_SUCCESS); // return successful exit code
}