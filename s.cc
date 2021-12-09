// Class implementation of the I tetromino
//
// Written by Benjamin Bauer, inspired by Prof Chelberg's square implementation
//

#include "s.h"

GLint S::NumPoints = 9;
bool S::inited = false;

void S::init_points()
{
  if (!inited)
  {
    points[0 + index] = vec2(0, 0);
    points[1 + index] = vec2(0, 1);
    points[2 + index] = vec2(2, 0);
    points[3 + index] = vec2(2, 1);

    points[4 + index] = vec2(1, 0);
    points[5 + index] = vec2(1, 1);
    points[6 + index] = vec2(1, 2);
    points[7 + index] = vec2(3, 1);
    points[8 + index] = vec2(3, 2);

    inited = true;
    // Actually send the data we've created to the GPU.
    // Can't do this here as we aren't sure we have an open OpenGL window yet.
    //    glBufferSubData(GL_ARRAY_BUFFER, index*sizeof(vec2), NumPoints*sizeof(vec2), points);
  }
}

// Default constructor
S::S() : Tetromino(), goal_x(0.0), goal_y(0.0)
{
  init_points();
  // Defaults
  minor_axis = 200.0;
  major_axis = 300.0;
  angle_offset = 0.0;
  angular_velocity = 1.0 / 500.0;
}

// Constructor if start of I vertices aren't at 0.
S::S(GLuint nindex, vec2 *npoints, GLint noffsetLoc, GLint nsizeLoc, GLint ncolorLoc) : Tetromino()
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
  // Defaults
  minor_axis = 200.0;
  major_axis = 300.0;
  angle_offset = 0.0;
  angular_velocity = 1.0 / 500.0;
}

// Move to the left
void S::moveLeft()
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
void S::moveRight()
{
  if (x > 775)
  {
    x = x;
  }
  else
  {
    x = x + 50;
  }
}

// Move down
void S::moveDown()
{
  if (y < 25)
  {
    y = y;
  }
  else
  {
    y = y - 25;
  }
}

// Setter to modify the parameters of the ellipse orbit
void S::set_ellipse_parameters(GLfloat nminor_axis, GLfloat nmajor_axis,
                               GLfloat nangle_offset,
                               GLfloat nangular_velocity)
{
  minor_axis = nminor_axis;
  major_axis = nmajor_axis;
  angle_offset = nangle_offset;
  if (angular_velocity != nangular_velocity)
  {
    GLfloat angle = current_time * angular_velocity;
    GLfloat nangle = current_time * nangular_velocity;
    angle_offset += angle - nangle;
    angular_velocity = nangular_velocity;
  }
}

// Get the parameters of the ellipse movement.
void S::get_ellipse_parameters(GLfloat &nminor_axis, GLfloat &nmajor_axis,
                               GLfloat &nangle_offset,
                               GLfloat &nangular_velocity)
{
  nminor_axis = minor_axis;
  nmajor_axis = major_axis;
  nangle_offset = angle_offset;
  nangular_velocity = angular_velocity;
}

// Code to call to draw a I.
void S::draw(bool select_mode)
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
  //  std::cout << "Drawing I at (" << x << " " << y << ") color = (" << r << ", " << g << ", " << b << ")" << std::endl;
  glDrawArrays(GL_TRIANGLE_STRIP, index, NumPoints);
}

// Update the position of the I from time
void S::update()
{
  const GLfloat max_speed = 200.0 / 1000.0; // pixels/msec max speed

  vec2 dir = vec2(goal_x - x, goal_y - y);
  //  if (length(dir)==0.0) {

  //  }else{
  // Tolerance for arrival at a point (i.e. within 3 pixels)
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

// Update the position of the I from time
void S::update_ellipse()
{
  current_time += compute_time();
  x = goal_x + major_axis * sin(current_time * angular_velocity + angle_offset);
  y = goal_y + minor_axis * cos(current_time * angular_velocity + angle_offset);
  set_last_time();
}

// Change goal location for I
void S::change_goal(GLint nx, GLint ny)
{
  goal_x = nx;
  goal_y = ny;
}

// Change goal location for I
void S::change_goal(vec2 npos)
{
  goal_x = npos.x;
  goal_y = npos.y;
}