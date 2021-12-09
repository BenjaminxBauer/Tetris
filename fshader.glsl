// Fragment shader code
// 
// Written by Prof. David M. Chelberg
// 
// A simple fragment shader, a basic pass-through shader.
//
//
// last-modified: Mon Oct  5 20:33:01 2020
//

varying vec4 fcolor;

void main() 
{ 
  gl_FragColor = fcolor;
} 
