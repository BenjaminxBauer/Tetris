// Class implementation of the I tetromino
//
// Written by Benjamin Bauer, inspired by Prof Chelberg's square implementation
//

#include "i.h"

GLint I::NumPoints = 4;
bool I::inited = false;

void I::init_points()
{
  if (!inited)
  {
    points[0 + index] = vec2(0.0, -0.5);
    points[1 + index] = vec2(0.0, 0.5);
    points[2 + index] = vec2(4, -0.5);
    points[3 + index] = vec2(4, 0.5);
    inited = true;
  }
}

// Default constructor
I::I() : Tetromino(), goal_x(0.0), goal_y(0.0)
{
  init_points();
}

// Constructor if start of I vertices aren't at 0.
I::I(GLuint nindex, vec2 *npoints, GLint noffsetLoc, GLint nsizeLoc, GLint ncolorLoc) : Tetromino()
{
  // Default index is the start (0).
  index = nindex;

  // Update the location of the points array from the main program.
  points = npoints;

  // Update the values of where the variables are in the shaders.
  offsetLoc = noffsetLoc;
  sizeLoc = nsizeLoc;
  colorLoc = ncolorLoc;

  // Default position is (0, 0)
  goal_x = goal_y = 0.0;

  init_points();
}

// Move to the left
void I::moveLeft()
{
  if (x < 25)
  {
    x = x;
  }
  else
  {
    x = x - 50;
  }
}

// Move to the right
void I::moveRight()
{
  if (x > 745)
  {
    x = x;
  }
  else
  {
    x = x + 50;
  }
}

// Move down
void I::moveDown()
{
  if (y < 45)
  {
    y = y;
  }
  else
  {
    y = y - 25;
  }
}

// Code to call to draw a I.
void I::draw(bool select_mode)
{
  // Pass the current size of the I
  glUniform1f(sizeLoc, size);
  glUniform2i(offsetLoc, int(x), int(y));
  // Set color on GPU
  if (select_mode)
  {
    glUniform4f(colorLoc, sr, sg, sb, 1.0);
  }
  else if (selected)
  {
    glUniform4f(colorLoc, 0.0, 1.0, 1.0, 1.0);
  }
  else
  {
    glUniform4f(colorLoc, r, g, b, 1.0);
  }
  glDrawArrays(GL_TRIANGLE_STRIP, index, NumPoints);
}

// Update the position of the I from time
void I::update()
{
  const GLfloat max_speed = 200.0 / 1000.0; // pixels/msec max speed

  vec2 dir = vec2(goal_x - x, goal_y - y);

  if (length(dir) > 3.0)
  {
    dir = (compute_time()) * max_speed * normalize(dir);
    // Update location
    x += dir.x;
    y += dir.y;
  }
  else
  {
    x = goal_x;
    y = goal_y;
  }
  set_last_time();
}

// Change goal location for I
void I::change_goal(GLint nx, GLint ny)
{
  goal_x = nx;
  goal_y = ny;
}

// Change goal location for I
void I::change_goal(vec2 npos)
{
  goal_x = npos.x;
  goal_y = npos.y;
}
