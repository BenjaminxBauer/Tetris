#ifndef TETROMINO_H
#define TETROMINO_H
//The code for this file will define a tetromino tetromino
// implements common functions to all tetrominos that will be drawn/animated

#include <Angel.h>
#include <iostream>
#include <stdlib.h>

class Tetromino
{
public:
  // Default constructor
  Tetromino();

  // Rotate the object
  //void rotate();

  // Move the Tetromino to (x, y) in screen coordinates
  void move(GLfloat nx, GLfloat ny);

  // Move the Tetromino to where in screen coordinates
  void move(vec2 where);

  // Change the Tetromino's color to r, g, b value
  void color(GLfloat nr, GLfloat ng, GLfloat nb);

  // Change the Tetromino's color to ncolor's value
  void color(vec3 ncolor);

  // Get the Tetromino's color as a vec3
  vec3 getColor();

  // Change the size of the object.
  void change_size(GLfloat size);

  // Update the last updated time to now.
  void set_last_time();

  // Reset the simulation time for this Tetromino to 0.
  void reset_time();

  // Returns the time since the last update
  GLint compute_time();

protected:
  GLfloat size; // size of Tetromino (see individual Tetrominos for specific meaning)

  // location of Tetromino (x, y)
  GLfloat x;
  GLfloat y;

  // Color of Tetromino
  GLfloat r;
  GLfloat g;
  GLfloat b;

  // Color for selection drawing of Tetromino
  GLfloat sr;
  GLfloat sg;
  GLfloat sb;

  // Start of vertices to draw in VAO
  GLuint index;
  // Pointer to the points array
  vec2 *points;

  // Locations of variables in shaders.
  // Offset of Tetromino
  GLint offsetLoc;
  // Size of Tetromino
  GLint sizeLoc;
  // Color of Tetromino
  GLint colorLoc;

  // For smooth animation consistent across machines
  GLint last_time;
  GLint current_time;

  // Whether the current Tetromino is selected
  bool selected;
};

#endif