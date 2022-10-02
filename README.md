# flasim

FlaSim is a mini game I did as a birthday party gag. It lets you control an anti-aircraft cannon with your joystick. Five jets are then randomly spawned (one after the other) as targets to be engaged by the player. There is a [blog post](https://polylux.eu/blog/4/) about the implementation aspects of the game.

## Controls

You'll need a joystick to play the game. The game starts out with no enemies so you can get used to steering the cannons. Joystick button 1 fires, button 2 reloads the guns (15 seconds penalty). Pressing `F9` activates the game mode which spawns a plane every 45 secs (so scan your horizon!), `F10` quits game mode (same as when 'aircraft remain' is zero), `F12` quits the game.
Successfully engaging a plane rewards you with 1000 points plus bonus for the distance (the further out the more points). Relevant info is shown in the top-left corner.

## About the game

The game uses the irrlicht graphics engine for the eye and cAudio for the ear. It's quite of simple complexity and might hence serve as a good example for someone learning about game and/or graphics programming.
About the visual content shown in the game: I did some parts myself (cannon model, crosshairs, terrain), all other stuff is from free content websites. 

## Building flasim

The game is confirmed to be building on Windows and Linux. Start out with cloning and fetching the submodules.

## Linux

1. Make sure to have `cmake`, `gcc`, `irrlicht` and `openal` installed and ready. If your distro differentiates, pull the dev options for the latter two.
1. `cmake` flasim and build.
1. Done.

## Windows

1. Have `cmake` installed.
1. Next we need the *irrlicht* dependency. Either build it yourself or clone the ready compiled [irrlicht-bin](https://git.socialnerds.org/otto/irrlicht-bin) repo somewhere close to *flasim*
1. For windows, the cmake config needs some extra locations. One is to tell *flasim* where to find *irrlicht*, one where to look for the *OpenAL* binary deps which are included in cAudio. A typical call to `cmake` would look like this (assuming *irrlicht* is just outside the *flasim* folder): `cmake -DIRRLICHT_INC_DIR=../irrlicht-bin/inc -DIRRLICHT_LIB_DIR=../irrlicht-bin/lib -DCAUDIO_DEPENDENCIES_DIR=ext/cAudio/Dependencies64 (...)` for a x64 build.
1. Build flasim using your favorite IDE or `nmake`
1. Once successfully through, manually copy over `Irrlicht.dll` from `irrlicht-bin` to `flasim/bin` and you're ready to launch.
1. Find out how many more steps were necessary compared to Linux.
1. Done.

Questions? Reach me at otto socialnerds.org



