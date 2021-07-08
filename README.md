# BSPAlgorithm

## Introduction

Welcome. 

If you are here is because, you are also curious on old FPS and their engines. If you ever thought, how a single 486 machine could run such amazing graphics in 1992, without a graphic card, the truth is, they didn't. This project explains that.

This is a small engine based on a video I watched from a wonderful developer called [Bisqwit](https://www.youtube.com/channel/UCKTehwyGCKF-b2wo0RKwrcg). In it, he explains how to create a simple fake 3d render using RayCasting and BSP algorithms in Basic and C.

In this project, you can see how I translated that video in a small engine to emulate the same behavior, but in a more OOP way. 

I've also added ImGUI for SDL in the project, and there's no need to install since the dynamic library is embedded in the project already.

There's only two requirements you can see it in action.

## Requirements.

- It is needed for the user to install SDL before running this. You can find it [here](https://www.libsdl.org)
- This project was developed in Xcode and in a Mac. It does not have a makefile nor a VS solution or anything that could be useful for other OS. In fact, the Xcode project installs the libImGUISDL.dylib where it belongs in Mac (inside `/usr/local/lib`). Feel free to make it work in other OS, since it only uses standard c++ and SDL.

## Contents

There are three main folders in this project.

- Classes: Where all the basic classes for the engines are. You'll find everything for the window, game loop, sprites, behavior of the sprites (keystrokes and mouse) and some other useful stuff.
- Test: In the beginning of bisqwit video, he'll explain how you can transform 2D in 3D, based on an absolute map (the player moves but the world stays intact), the transformed map (the world moves but the player stay still), and the perspective transformed map (we apply projection and a viewport to emulate the z axis based on the position of the things). To test this, go to `main.cpp` and change the `#define TEST` to 1.
- BSP: The bsp algorithm in itself is not an algorithm of rendering, but an algorithm of sorting the walls based on the position of the player. That allows to have multiple sectors with different heights. This folder has all the classes to load a simple map (from the file `map-clear.txt`) with vectors, sectors and the player position, and pass it the MapSprite, where the code will render and handle the input to move the player.

There are other folder such as `ThirdParties` and `Utils` but they are only for helping the BSP algorithm to shine.

![Demo](lowe,gif)

## Known bugs

There's only one small bug, where you can jump but the next input does not get detected. That's because, if you press two keys and release one, the other key gets ignored since a key up event already happen. That can be fixed in the event pool, but this project is only an experiment.

# Contact

If you have a question, please contact me at [werewolf2188@gmail.com](mailto:werewolf2188@gmail.com)

# References

- [Creating a Doom-style 3D engine in C](https://www.youtube.com/watch?v=HQYsFshbkYw)

