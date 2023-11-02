#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

const int windowWidth = 800;
const int windowHeight = 800;

const int gridWidth = 100;
const int gridHeight = 100;
const float cellSizeX = static_cast<float>(windowWidth) / gridWidth;
const float cellSizeY = static_cast<float>(windowHeight) / gridHeight;

vector<vector<sf::Color>> fluidGrid(gridWidth, vector<sf::Color>(gridHeight, sf::Color::Black));

float ComputeNewVelocityX(int x, int y, float currentVx, float currentVy, float dt) {
    // Calculate the new velocity component in the x direction based on advection
    // For simplicity, use a simple Euler method here
    float advectionVx = currentVx - (dt * currentVx);
    
    // You can add more complex calculations here for viscosity, pressure, and other effects
    // For a basic simulation, this is sufficient

    return advectionVx;
}

float ComputeNewVelocityY(int x, int y, float currentVx, float currentVy, float dt) {
    // Calculate the new velocity component in the y direction based on advection
    // For simplicity, use a simple Euler method here
    float advectionVy = currentVy - (dt * currentVy);

    // You can add more complex calculations here for viscosity, pressure, and other effects
    // For a basic simulation, this is sufficient

    return advectionVy;
}

sf::Color ComputeNewDensity(int x, int y, sf::Color currentColor, float dt) {
    // Calculate the new density based on advection
    // For simplicity, use a simple Euler method here
    sf::Color advectionColor = sf::Color(
        static_cast<sf::Uint8>(currentColor.r - (dt * currentColor.r)),
        static_cast<sf::Uint8>(currentColor.g - (dt * currentColor.g)),
        static_cast<sf::Uint8>(currentColor.b - (dt * currentColor.b))
    );

    // You can add more complex calculations here for diffusion, sources, and other effects
    // For a basic simulation, this is sufficient

    return advectionColor;
}



int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Fluid Simulation");

    int centerX = gridWidth / 2;
    int centerY = gridHeight / 2;

    sf::Color initialColor(0, 0, 255);  // High density as blue
    float initialVelocityX = 2.0f;
    float initialVelocityY = 0.0f;

    for (int x = centerX - 10; x < centerX + 10; ++x) {
        for (int y = centerY - 10; y < centerY + 10; ++y) {
            fluidGrid[x][y] = initialColor;
        }
    }

    float dt = 0.1f;
    sf::Vector2f gravity(0.0f, 0.1f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        vector<vector<sf::Color>> updatedGrid(gridWidth, vector<sf::Color>(gridHeight, sf::Color::Black));

        // Velocity advection with gravitational force
        for (int x = 1; x < gridWidth - 1; ++x) {
            for (int y = 1; y < gridHeight - 1; ++y) {
                sf::Color currentColor = fluidGrid[x][y];
                float vy = gravity.y * dt;

                // Calculate new colors based on advection equations
                sf::Color newColor = ComputeNewDensity(x, y, currentColor, dt);
                updatedGrid[x][y] = newColor;

                // Apply gravitational force
                if (y < gridHeight - 1)
                    updatedGrid[x][y + 1] = currentColor;
                else
                    updatedGrid[x][y] = currentColor;
            }
        }

        fluidGrid = updatedGrid;

        window.clear();

        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                float cellX = x * cellSizeX;
                float cellY = y * cellSizeY;

                sf::RectangleShape cellShape(sf::Vector2f(cellSizeX, cellSizeY));
                cellShape.setPosition(cellX, cellY);

                sf::Color cellColor = fluidGrid[x][y];
                cellShape.setFillColor(cellColor);

                window.draw(cellShape);
            }
        }

        window.display();
    }

    return 0;
}
