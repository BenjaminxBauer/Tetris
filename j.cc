// Class implementation of the I tetromino
//
// Written by Benjamin Bauer, inspired by Prof Chelberg's square implementation
//

#include "j.h"

GLint J::NumPoints = 10;
bool J::inited = false;

void J::init_points()
{
  if (!inited)
  {
    points[0 + index] = vec2(0, 0);
    points[1 + index] = vec2(1, 0);
    points[2 + index] = vec2(0, -3);
    points[3 + index] = vec2(1, -3);

    points[4 + index] = vec2(1, -2);
    points[5 + index] = vec2(-1, -3);
    points[6 + index] = vec2(-1, -2);
    points[7 + index] = vec2(-1, -2);
    points[8 + index] = vec2(-1, -2);
    points[9 + index] = vec2(-1, -2);

    inited = true;
  }
}

// Default constructor
J::J() : Tetromino(), goal_x(0.0), goal_y(0.0)
{
  init_points();
}

// Constructor if start of I vertices aren't at 0.
J::J(GLuint nindex, vec2 *npoints, GLint noffsetLoc, GLint nsizeLoc, GLint ncolorLoc) : Tetromino()
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
void J::moveLeft()
{
  if (x < 90)
  {
    x = x;
  }
  else
  {
    x = x - 50;
  }
}

// Move to the right
void J::moveRight()
{
  if (x > 800)
  {
    x = x;
  }
  else
  {
    x = x + 50;
  }
}

// Move down
void J::moveDown()
{
  if (y < 115)
  {
    y = y;
  }
  else
  {
    y = y - 25;
  }
}

// Rotate J Tetromino
void J::firstRotate()
{
  points[0 + index] = vec2(0, 0);
  points[1 + index] = vec2(3, 0);
  points[2 + index] = vec2(3, 1);
  points[3 + index] = vec2(0, 1);

  points[4 + index] = vec2(0, 0);
  points[5 + index] = vec2(0, 2);
  points[6 + index] = vec2(1, 2);
  points[7 + index] = vec2(1, 0);
  points[8 + index] = vec2(0, 0);
  points[9 + index] = vec2(0, 0);
}
void J::secondRotate()
{
  points[0 + index] = vec2(3, 0);
  points[1 + index] = vec2(3, -1);
  points[2 + index] = vec2(1, 0);
  points[3 + index] = vec2(1, -1);

  points[4 + index] = vec2(2, 0);
  points[5 + index] = vec2(2, -3);
  points[6 + index] = vec2(1, -1);
  points[7 + index] = vec2(1, -3);
  points[8 + index] = vec2(1, -3);
  points[9 + index] = vec2(1, -3);
}
void J::thirdRotate()
{
  points[0 + index] = vec2(3, 0);
  points[1 + index] = vec2(3, 1);
  points[2 + index] = vec2(0, 1);
  points[3 + index] = vec2(0, 0);

  points[4 + index] = vec2(3, 0);
  points[5 + index] = vec2(3, 1);
  points[6 + index] = vec2(3, -1);
  points[7 + index] = vec2(2, -1);
  points[8 + index] = vec2(2, 0);
  points[9 + index] = vec2(3, 0);
}
void J::originalPosition()
{
  points[0 + index] = vec2(0, 0);
  points[1 + index] = vec2(1, 0);
  points[2 + index] = vec2(0, -3);
  points[3 + index] = vec2(1, -3);

  points[4 + index] = vec2(1, -2);
  points[5 + index] = vec2(-1, -3);
  points[6 + index] = vec2(-1, -2);
  points[7 + index] = vec2(-1, -2);
  points[8 + index] = vec2(-1, -2);
  points[9 + index] = vec2(-1, -2);
}

// Code to call to draw a I.
void J::draw(bool select_mode)
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
void J::update()
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
void J::change_goal(GLint nx, GLint ny)
{
  goal_x = nx;
  goal_y = ny;
}

// Change goal location for I
void J::change_goal(vec2 npos)
{
  goal_x = npos.x;
  goal_y = npos.y;
}