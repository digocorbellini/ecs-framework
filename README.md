# ECS 2D Framework
Project initially made for a college course at the University of Texas at Austin by Benjamin Chen and Rodrigo Okamoto Corbellini Pereira.

Now maintained and updated by Rodrigo Okamoto Corbellini Pereira.

## How to Build and Run 
1) Download the [SFML 2.6.1](https://www.sfml-dev.org/download.php)
2) Place the `SFML-2.6.1` directory in the following path relative to this project: `../SFML-2.6.1`
3) Launch the Visual Studio project found in `/ECS-Framework/ECS-Framework.sln`
4) After trying to run the project, go to `/ECS-Framework/x64/Debug` and place all of the dlls found in `../SFML-2.6.1/lib` here
5) Run the project and play the game!
6) If you would like to change the scene that the game is running, go to `/ECS-Framework/main.cpp` and in `main()` comment out the current scene and uncomment the one you would like to see run.

## How to run premade builds for Windows
1) Go to `/Builds`
2) There are 2 options: `TechDemo.exe` and `Benchmark.exe`. Run whichever one you'd like to see
    - `TechDemo` is a small game with a playable character and a follow camera. There is no end goal but you can move around the scene.
    - `Benchmark` is a scene with 5000 dynamic physics bodies and 1 static physics body which displays the performance of the system at scale.

## Initial Project Report
Initial design specs for the college course: 
[Report](https://docs.google.com/document/d/1vypitFH3rTqleIBHegxu4SyBwkUKwmBZYJimKOHsMIw/edit?usp=sharing)

## Trailer
[Demo Video](https://youtu.be/zXIZc0nwqCI)

## Feature List
- [x] Using contiguous memory allocation for caching benefits
- [x] 2D physics
- [x] A player controller
- [x] A camera controller
- [x] Order based rendering system
- [ ] System for serializing entities and their components
- [ ] Scene system for loading in a list of entities
- [ ] Compatibility with level editing tools such as [Tiled](https://www.mapeditor.org/)
- [ ] Streamlining the creation of systems and components with macros
