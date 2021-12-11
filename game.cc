/**************************************************************************
 *  game.cc
 * 
 * Author:  Benjamin Bauer
 * Credit: The core of this program and set of files is built off of
 *         Professor Chelberg's notes lec11a, specifically his animate
 *         program, object.h object.cc, and square.h square.cc files
 * 
 * Email:   BB060017@ohio.edu
 * 
 * Description: This program and set of files are responsible for simulating the game
 * Tetris. This file specifically creates the objects, Tetrominos and
 * allows the user to move them and rotate them while a random shape
 * is generated and free falls.
 * 
 * Date: 12/10/2021
 * 
 * ************************************************************************/

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
#include <time.h>

// Bool to determine whether to clear the screen
bool clear = true;

// Holds a randomNumber
int randomNum;

// Keeps track of which position we are for rotation
int rotateCounter = 0;

// X goal, holds the value of where the x position of the free fall should be
int positionX = 450;

// Bool to determine whether to update the animation, used in idle
bool updating = true;

// Pointer to the Iobject (must be initialized after
// initialization of shaders, so leave it as a pointer.
I *I_Tetromino;
O *O_Tetromino;
T *T_Tetromino;
J *J_Tetromino;
L *L_Tetromino;
S *S_Tetromino;
Z *Z_Tetromino;

// Data storage for our geometry for the lines
vec2 *points;

// How big a tetromino to draw.
GLfloat size = 30.0;

// Window Size
GLint windowSizeLoc;

// Window size
int win_h = 0;
int win_w = 0;

GLuint TransformLoc;
mat4 transforms[1];

extern "C" void idle()
{
  if (updating)
  {
    if (randomNum == 0)
    {
      I_Tetromino->update();
      I_Tetromino->change_goal(positionX, 0);
    }
    else if (randomNum == 1)
    {
      O_Tetromino->update();
      O_Tetromino->change_goal(positionX, 0);
    }
    else if (randomNum == 2)
    {
      T_Tetromino->update();
      T_Tetromino->change_goal(positionX, 0);
    }
    else if (randomNum == 3)
    {
      J_Tetromino->update();
      J_Tetromino->change_goal(positionX, 100);
    }
    else if (randomNum == 4)
    {
      L_Tetromino->update();
      L_Tetromino->change_goal(positionX, 100);
    }
    else if (randomNum == 5)
    {
      S_Tetromino->update();
      S_Tetromino->change_goal(positionX, 50);
    }
    else if (randomNum == 6)
    {
      Z_Tetromino->update();
      Z_Tetromino->change_goal(positionX, 50);
    }

    glutPostRedisplay();
  }
}

// Function initalizes a random seed using the computer's clock, makes it so that the program generates a new random number each time its used
extern "C" void initRandomTime()
{
  srand(time(NULL));
}

// Generates a random number and draws the according tetromino based off that number (0-6 one for each tetromino)
extern "C" void drawRandomTetromino()
{
  // Generate a random number
  //randomNum = rand() % 10;
  randomNum = 4;
  if (randomNum > 6)
  {
    drawRandomTetromino();
  }
  else
  {
    // Check the number and draw the according tetromino
    if (randomNum == 0)
    {
      I_Tetromino->draw();
    }
    else if (randomNum == 1)
    {
      O_Tetromino->draw();
    }
    else if (randomNum == 2)
    {
      T_Tetromino->draw();
    }
    else if (randomNum == 3)
    {
      J_Tetromino->draw();
    }
    else if (randomNum == 4)
    {
      L_Tetromino->draw();
    }
    else if (randomNum == 5)
    {
      S_Tetromino->draw();
    }
    else if (randomNum == 6)
    {
      Z_Tetromino->draw();
    }
  }
}

// Simple display draws a Iof size sq_size*2 around mouse
// location.
extern "C" void display()
{
  // What happens if the following is commented out?  Explain.
  if (clear)
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  // Draw one tetromino randomly
  drawRandomTetromino();

  glutSwapBuffers();
}

// Maintains the mapping from screen to world coordinates.
extern "C" void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  win_h = h;
  win_w = w;
  glUniform2f(windowSizeLoc, win_w, win_h); // Pass the window size
                                            // size
  glutPostRedisplay();
}

// Game menu code.
extern "C" void myMenu(int value)
{
  switch (value)
  {
  case 6:
    exit(0);
    break;
  }
  glutPostRedisplay();
}

// Keypress events
extern "C" void key(unsigned char k, int xx, int yy)
{
  switch (k)
  {
  case 'q':
    exit(0);
    break;
  case 'n':
    //draw = true;
    break;
  // Move left option , user could also use left arrow key
  case 'a':
    positionX = positionX - 50;
    if (randomNum == 0)
    {
      I_Tetromino->moveLeft();
    }
    else if (randomNum == 1)
    {
      O_Tetromino->moveLeft();
    }
    else if (randomNum == 2)
    {
      T_Tetromino->moveLeft();
    }
    else if (randomNum == 3)
    {
      J_Tetromino->moveLeft();
    }
    else if (randomNum == 4)
    {
      L_Tetromino->moveLeft();
    }
    else if (randomNum == 5)
    {
      S_Tetromino->moveLeft();
    }
    else if (randomNum == 6)
    {
      Z_Tetromino->moveLeft();
    }
    break;
  // Move right option , user could also use the right arrow key
  case 'd':
    positionX = positionX + 50;
    if (randomNum == 0)
    {
      I_Tetromino->moveRight();
    }
    else if (randomNum == 1)
    {
      O_Tetromino->moveRight();
    }
    else if (randomNum == 2)
    {
      T_Tetromino->moveRight();
    }
    else if (randomNum == 3)
    {
      J_Tetromino->moveRight();
    }
    else if (randomNum == 4)
    {
      L_Tetromino->moveRight();
    }
    else if (randomNum == 5)
    {
      S_Tetromino->moveRight();
    }
    else if (randomNum == 6)
    {
      Z_Tetromino->moveRight();
    }
    break;
  // Move Down
  case 's':
    if (randomNum == 0)
    {
      I_Tetromino->moveDown();
    }
    else if (randomNum == 1)
    {
      O_Tetromino->moveDown();
    }
    else if (randomNum == 2)
    {
      T_Tetromino->moveDown();
    }
    else if (randomNum == 3)
    {
      J_Tetromino->moveDown();
    }
    else if (randomNum == 4)
    {
      L_Tetromino->moveDown();
    }
    else if (randomNum == 5)
    {
      S_Tetromino->moveDown();
    }
    else if (randomNum == 6)
    {
      Z_Tetromino->moveDown();
    }
    break;
  // Rotate Clockwise
  case 'z':
    if (randomNum == 3)
    {
      rotateCounter = rotateCounter + 1;
      J_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        J_Tetromino->firstRotate();
      }
      else if (rotateCounter == 2)
      {
        J_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        J_Tetromino->thirdRotate();
      }
      else
      {
        J_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      J_Tetromino->draw();
    }
    else if (randomNum == 4)
    {
      rotateCounter = rotateCounter + 1;
      L_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        L_Tetromino->firstRotate();
      }
      else if (rotateCounter == 2)
      {
        L_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        L_Tetromino->thirdRotate();
      }
      else
      {
        L_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      L_Tetromino->draw();
    }
    else if (randomNum == 5)
    {
      rotateCounter = rotateCounter + 1;
      S_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        S_Tetromino->firstRotate();
      }
      else if (rotateCounter == 2)
      {
        S_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        S_Tetromino->thirdRotate();
      }
      else
      {
        S_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      S_Tetromino->draw();
    }
    else if (randomNum == 6)
    {
      rotateCounter = rotateCounter + 1;
      Z_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        Z_Tetromino->firstRotate();
      }
      else if (rotateCounter == 2)
      {
        Z_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        Z_Tetromino->thirdRotate();
      }
      else
      {
        Z_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      Z_Tetromino->draw();
    }
    break;
  // Rotate right
  case 'x':
    // For these just calling the same rotate functions in different orders
    if (randomNum == 3)
    {
      rotateCounter = rotateCounter + 1;
      J_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        J_Tetromino->thirdRotate();
      }
      else if (rotateCounter == 2)
      {
        J_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        J_Tetromino->firstRotate();
      }
      else
      {
        J_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      J_Tetromino->draw();
    }
    else if (randomNum == 4)
    {
      rotateCounter = rotateCounter + 1;
      L_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        L_Tetromino->thirdRotate();
      }
      else if (rotateCounter == 2)
      {
        L_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        L_Tetromino->firstRotate();
      }
      else
      {
        L_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      L_Tetromino->draw();
    }
    else if (randomNum == 5)
    {
      rotateCounter = rotateCounter + 1;
      S_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        S_Tetromino->thirdRotate();
      }
      else if (rotateCounter == 2)
      {
        S_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        S_Tetromino->firstRotate();
      }
      else
      {
        S_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      S_Tetromino->draw();
    }
    else if (randomNum == 6)
    {
      rotateCounter = rotateCounter + 1;
      Z_Tetromino->move(425, 875); // With more time I would set this to the last known location instead of the top
      if (rotateCounter == 1)
      {
        Z_Tetromino->thirdRotate();
      }
      else if (rotateCounter == 2)
      {
        Z_Tetromino->secondRotate();
      }
      else if (rotateCounter == 3)
      {
        Z_Tetromino->firstRotate();
      }
      else
      {
        Z_Tetromino->originalPosition();
        rotateCounter = 0;
      }
      glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
      Z_Tetromino->draw();
    }
    break;
  }
  glutPostRedisplay();
}

// Create menu and items.
void setupMenu()
{
  glutCreateMenu(myMenu);
  glutAddMenuEntry("Welcome to Tetris! Use these commands:", 1);
  glutAddMenuEntry("Press 'a' to move left", 2);
  glutAddMenuEntry("Press 'd' to move right", 3);
  glutAddMenuEntry("Press 's' to move down", 4);
  glutAddMenuEntry("Press 'z' to rotate", 5);
  glutAddMenuEntry("Press 'q' to quit", 6);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialize all OpenGL callbacks, create window.
void myinit()
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(20, 20);

  glutCreateWindow("Tetris");

  // Color initializations
  glClearColor(0.0, 0.0, 0.0, 1.0);

  setupMenu();

  // Callbacks
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(myReshape);
  glutKeyboardFunc(key);
}

// This function initializes the buffers and shaders
void init()
{
  // Locations of variables in shaders.
  // Offset of square
  GLint offsetLoc;
  // Size of tetromino
  GLint sizeLoc;
  // Color of tetromino
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

  // Initialize the vertex position attribute from the vertex shader
  windowSizeLoc = glGetUniformLocation(program, "windowSize");
  if (windowSizeLoc == -1)
  {
    std::cerr << "Unable to find windowSize parameter" << std::endl;
  }

  offsetLoc = glGetUniformLocation(program, "offset");
  if (offsetLoc == -1)
  {
    std::cerr << "Unable to find offsetLoc parameter" << std::endl;
  }

  sizeLoc = glGetUniformLocation(program, "size");
  if (sizeLoc == -1)
  {
    std::cerr << "Unable to find sizeLoc parameter" << std::endl;
  }

  colorLoc = glGetUniformLocation(program, "vcolor");
  if (colorLoc == -1)
  {
    std::cerr << "Unable to find colorLoc parameter" << std::endl;
  }

  GLint loc = glGetAttribLocation(program, "vPosition");
  if (loc == -1)
  {
    std::cerr << "Unable to find vPosition parameter" << std::endl;
  }
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glUniform2f(offsetLoc, 0.0, 0.0); // Initial offset
                                    // for mouse loc.

  points = new vec2[I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints];

  // Build the I tetromino
  I_Tetromino = new I(0, points, offsetLoc, sizeLoc, colorLoc);
  I_Tetromino->change_size(size);
  I_Tetromino->move(390, 850);
  //I_Tetromino->selectColor(1.0 / 255.0, 0.0, 0.0);
  I_Tetromino->color(0.0f, 1.0f, 1.0f);

  // Build the O tetromino
  O_Tetromino = new O(I::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  O_Tetromino->change_size(size);
  O_Tetromino->move(425, 825);
  //O_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  O_Tetromino->color(1.0f, 1.0f, 0.0f);

  // Build the T tetromino
  T_Tetromino = new T(I::NumPoints + O::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  T_Tetromino->change_size(size);
  T_Tetromino->move(405, 850);
  //T_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  T_Tetromino->color(0.99f, 0.43f, 0.78f);

  // Build the J tetromino
  J_Tetromino = new J(I::NumPoints + O::NumPoints + T::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  J_Tetromino->change_size(size);
  J_Tetromino->move(450, 875);
  //J_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  J_Tetromino->color(0.0f, 0.0f, 1.0f);

  // Build the L tetromino
  L_Tetromino = new L(I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  L_Tetromino->change_size(size);
  L_Tetromino->move(425, 875);
  //L_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  L_Tetromino->color(1.0f, 0.5f, 0.0f);

  S_Tetromino = new S(I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  S_Tetromino->change_size(size);
  S_Tetromino->move(400, 825);
  //S_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  S_Tetromino->color(0.0f, 1.0f, 0.0f);

  Z_Tetromino = new Z(I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints, points, offsetLoc, sizeLoc, colorLoc);
  Z_Tetromino->change_size(size);
  Z_Tetromino->move(415, 825);
  //Z_Tetromino->selectColor(2.0 / 255.0, 0.0, 0.0);
  Z_Tetromino->color(1.0f, 0.0f, 0.0f);

  // Send the data to the graphics card, after it has been generated
  // by creating the objects in the world (above).
  glBufferData(GL_ARRAY_BUFFER, (I::NumPoints + O::NumPoints + T::NumPoints + J::NumPoints + L::NumPoints + S::NumPoints + Z::NumPoints) * sizeof(vec2), points, GL_STATIC_DRAW);
}

//  Main Program
int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  // Initialize random time
  initRandomTime();

  myinit(); // set window attributes, and initial data

  // Initialize the "magic" that glues all the code together.
  glewInit();

  init(); // set up shaders and display environment

  glutMainLoop(); // enter event loop

  return (EXIT_SUCCESS); // return successful exit code
}