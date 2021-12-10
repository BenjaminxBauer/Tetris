// Class implementation of base tetromino class
//
// Written by Benjamin Bauer, inspired by Prof Chelberg's Tetromino class implementation
//

#include "tetromino.h"

Tetromino::Tetromino()
{
  // Initially this Tetromino is not selected.
  selected = false;

  // Default index is the start (0).
  index = 0;

  // Default Size = 30.0
  size = 30.0;

  // Default color = white.
  r = g = b = 1.0;

  // Default selection color = black.
  sr = sg = sb = 0.0;

  // Default position is (0, 0)
  x = y = 0.0;

  // When did we last update Tetromino
  //last_time = current_time = glutGet(GLUT_ELAPSED_TIME);

  // Make sure it is initialize to NULL
  points = NULL;
}

// Move the Tetromino to (x, y) in screen coordinates
void Tetromino::move(GLfloat nx, GLfloat ny)
{
  x = nx;
  y = ny;
}

// Rotate
// void Tetromino::rotate()
// {
//   RotateZ(90);
//   glUniformMatrix4v(90, 1, GL_TRUE, model_view);
// }

// Move the Tetromino to where in screen coordinates
void Tetromino::move(vec2 where)
{
  x = where.x;
  y = where.y;
}

// Change the size of the object.
void Tetromino::change_size(GLfloat nsize)
{
  size = nsize;
}

// Update the last time Tetromino was modified to now.
void Tetromino::set_last_time()
{
  // When did we last update Tetromino
  last_time = glutGet(GLUT_ELAPSED_TIME);
}

// Update the last time Tetromino was modified to now.
void Tetromino::reset_time()
{
  // What is the time in the simulation.
  current_time = 0;
}

// Returns the amount of time since we last updated the Tetromino.
GLint Tetromino::compute_time()
{
  return (glutGet(GLUT_ELAPSED_TIME) - last_time);
}

// Change the Tetromino's color to r, g, b value
void Tetromino::color(GLfloat nr, GLfloat ng, GLfloat nb)
{
  r = nr;
  g = ng;
  b = nb;
}

// Change the Tetromino's color to ncolor's value
void Tetromino::color(vec3 ncolor)
{
  r = ncolor.x;
  g = ncolor.y;
  b = ncolor.z;
}