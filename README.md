# 2D Fluid Simulation in C++ with SFML

This is a simple 2D fluid simulation implemented in C++ using the Simple and Fast Multimedia Library (SFML). It demonstrates the basic principles of simulating fluid dynamics in a grid-based system.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Customization](#customization)
- [License](#license)

## Features

- 2D fluid simulation.
- Grid-based representation of fluid.
- Simulation of advection, diffusion, and gravitational force.
- Visualization of the fluid using SFML.

## Requirements

- C++ compiler (C++11 or higher).
- SFML library.

## Getting Started

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/2D-Fluid-Simulation.git
2. Compile the program using your C++ compiler. If you're using g++, you can compile it like this:
    ```bash
    g++ -std=c++11 -o fluid_simulation main.cpp -lsfml-graphics -lsfml-window -lsfml-system
3. Run the compiled program:
    ```bash
    ./fluid_simulation

## Usage
- The program opens a window displaying the 2D fluid simulation.
- The fluid is initially set with some properties (e.g., color, density) in the center of the grid.
- You can customize and extend the simulation by modifying the code in main.cpp.
- The simulation includes basic advection, diffusion, and gravitational force. You can add more complex calculations for additional effects.

## Customization

You can customize the simulation by modifying the parameters and equations in the main.cpp file. Here are some ideas for customization:

- Adjust the simulation grid size (gridWidth and gridHeight) for higher or lower resolution.
- Experiment with different initial conditions and properties of the fluid.
- Implement more advanced fluid dynamics equations and effects.
- Change the gravitational force to achieve different behaviors.
- Tune the diffusion rate (diffusionRate) to control the diffusion of properties.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

Feel free to fork this project and expand upon it as needed for your own use or experimentation.