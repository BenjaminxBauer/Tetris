#ifndef I_H
#define I_H
// Class definition of the I tetromino
//
// Written by Benjamin Bauer, inspired by Professor Chelberg's square class
//

#include <Angel.h>
#include <iostream>
#include <stdlib.h>
#include "tetromino.h"

class I : public Tetromino
{
public:
  // How many points are needed to specify the I
  static GLint NumPoints;

  // Default constructor
  I();

  // Constructor if start of I vertices aren't at 0.
  I(GLuint nindex, vec2 *npoints, GLint noffsetLoc, GLint nsizeLoc, GLint ncolorLoc);

  // Initialize the points in the points array for I.
  void init_points();

  // Code to call to draw a I.
  // If select is true, then use the selection color.
  void draw(bool select = false);

  // Move to the left
  void moveLeft();

  // Move to the right
  void moveRight();

  // Move down
  void moveDown();

  // Update the position of the I from time
  void update();

  // Update I's position based on ellipse code.
  //void update_ellipse();

  // Change goal location for I
  void change_goal(GLint nx, GLint ny);

  // Change goal location for I
  void change_goal(vec2 npos);

private:
  static bool inited;

  // location of where I wants to go
  GLint goal_x;
  GLint goal_y;
};

#endif