# Super Mario Bros Clone

## To Do
* Hitbox outlines instead of filled rectangles
* Tweak Mario's velocity/acceleration when hitting a block from the bottom
* When falling and not pressing A, should Mario be jumping or not?

## Bug List
* Goomba-goomba collision is not considered. In particular, if a Goomba falls
on another Goomba, one Goomba falls through the ground
* Mario can walk through pipes with I-Frames
* After bumping into an enemy with Big Mario and shrinking to 
  Small Mario, staying inside the enemy will result in Mario stomping and 
  terminating it instead of Mario being terminated

# CMake Flags
-DDRAW_HITBOX: Set to 1 to enable debug hitboxes, 0 to turn off
-DMANUAL_INPUT: Set to 1 to get hardcoded input from a vector instead of
from the keyboard
