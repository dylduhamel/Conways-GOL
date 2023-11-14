# Conway's Game of Life Simulation

This program simulates Conway's Game of Life, a cellular automaton that is a zero-player game. Its evolution is determined by its initial state, requiring no further input. Set up the initial configuration of cells, and then observe how it evolves.

## Features

- SDL2 for rendering the Game of Life simulation
- Adjustable grid size and simulation parameters
- Smooth color transitions for cell states
- The screen.h header is inspired by: [TheBuilder-software](https://gist.github.com/TheBuilder-software)

## Compilation and Running (Linux)

Before compiling the program, ensure you have the SDL2 library installed on your system. If you haven't already installed SDL2, you can install it using the following command:

```
bash
sudo apt-get update
sudo apt-get install libsdl2-dev
```

Be sure to include the following flags when compiling:

```
g++ main.cpp -std=c++20 -lSDL2 -o main
```
