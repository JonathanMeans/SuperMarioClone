# Super Mario Bros Clone

## To Do
* Hitbox outlines instead of filled rectangles
* Tweak Mario's velocity/acceleration when hitting a block from the bottom
* When falling and not pressing A, should Mario be jumping or not?
* It's weird that we can jump into a fireflower without any horizontal movement

## Bug List
* Goomba-goomba collision is not considered. In particular, if a Goomba falls
on another Goomba, one Goomba falls through the ground

# CMake Flags
-DDRAW_HITBOX: Set to 1 to enable debug hitboxes, 0 to turn off
-DMANUAL_INPUT: Set to 1 to get hardcoded input from a vector instead of
from the keyboard
