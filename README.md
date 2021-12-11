# Tetris
Implemented as part of my Final Project for my Graphics class

Notes on running the program:
  Current Bugs:
    Random Shape generation does not work with movement or freefall, the result is a flashing of random shapes throughout the movement
      Work Around: 
        For running this program you can comment out where randomNum is set equal to the result of a random number and uncomment the hard coded declaration. Supported values are 0-6 and represent each tetromino
        
    Freefall when enabled in idle seems to ignore movement restrictions on the x-axis allowing the user to go too far left or too far right. Freefall also only works for shapes 3-6. 
      Work Around: 
        If you would like to see all the shapes comment out the contents of the idle function. Otherwise restrict your randomNum values to those 3-6.
