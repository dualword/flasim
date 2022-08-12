# flasim

FlaSim is a mini game I did as a birthday party gag. It lets you manually control an anti-aircraft cannon with your joystick. Five jets are then randomly spawned (one after the other) as targets to be engaged by the player. There is a [blog post](https://polylux.eu/blog/4/) about the implementation aspects of the game.

## Controls

You'll need a joystick to play the game. The game starts out with no enemies so you can get used to steering the cannons. Joystick button 1 fires, button 2 reloads the guns (15 seconds penalty). Pressing F9 activates the game mode which spawns a plane every 45 secs (so scan your horizon!), F10 quits game mode (same as when 'aircraft remain' is zero), F12 quits the game.
Successfully engaging a plane rewards you with 1000 points plus bonus for the distance (the further out the more points). Relevant info is shown in the top-left corner.

## About the game

The game uses the irrlicht graphics engine for the eye and cAudio for the ear. It's quite of simple complexity and might hence serve as a good example for someone learning about game and/or graphics programming.
About the visual content shown in the game: I did some parts myself (cannon model, crosshairs, terrain), all other stuff is from free content websites. 

## Building flasim

Currently only *Linux* works, should have a Windows buildability *in a couple of days* (yea, sure).
The game uses the CMake build system. Make sure you have GCC, Irrlicht and OpenAL available on your system.

1. Fetch the submodules.
1. Very recent versions of CMake have issues with the dated config in *cAudio*. If it complains about *flasim* not being defined inside *cAudio* open `ext/cAudio/CMakeLists.txt` and head to line 29 and 30. Replace `${CMAKE_PROJECT_NAME}` by the word `cAudio`.
1. CMake & build *flasim*


Questions? Reach me at otto@socialnerds.org



