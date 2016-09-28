##Welcome to my repository!
This is where I will be uploading some of the code for the projects that I have done.
I will be listing and describing the projects here:

MiniServo:
####Description: 
Connecting 4 servos and 4 potentiometers to an Arduino board.
####Results: 
3 axis robot that can remember 4 positions and loop through all four positions untill reset is called
####Flow: 
  Everytime the switch is pressed once, the position of all four servos is stored in arrays. 
  When the switch is pressed for the fourth time, the four servos loop through all four positions in predetermined time intervals
  During looping, the switch is toggling between -PLAY- and -PAUSE- modes
  During looping, at any time, if the switch is pressed twice, reset is called
  After reset, the arrays are cleared and goes back to the original position.
  
 
