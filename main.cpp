#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Fluid cell properties
struct Cell {
  float density;
  float vx;
  float vy;
  sf::Vector2f getFlow() const {
    return sf::Vector2f(vx, vy);
  }
};

// Simulation parameters
const int width = 200;
const int height = 200;
const float diffusionRate = 0.0001f;
const float viscosity = 3.0f;
const float gravity = -1.0f;
const int sourceStrength = 10;

std::vector<Cell> cells(width * height);

// Source position
sf::Vector2i sourcePos = sf::Vector2i(width / 2, height / 2);

// Color gradient function
sf::Color getDensityColor(float density) {
  float normalizedDensity = density / 255.0f;
  if (normalizedDensity < 0.25f) {
    return sf::Color::Blue;
  } else if (normalizedDensity < 0.5f) {
    return sf::Color::Cyan;
  } else if (normalizedDensity < 0.75f) {
    return sf::Color::Green;
  } else {
    return sf::Color::Yellow;
  }
}

void updateVelocity(int x, int y, float dt) {
  // Apply gravity
  // cells[y * width + x].vy += dt * gravity;
  
  // Calculate pressure
  float pressure = 0.0f;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nx = x + i;
      int ny = y + j;
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        pressure += cells[ny * width + nx].density;
      }
    }
  }
  pressure /= 9.0f;

  // Update velocity
  cells[y * width + x].vx -= dt * (pressure - cells[y * width + x].density) / 2.0f;
  cells[y * width + x].vy -= dt * gravity;

  // Bounce velocity off boundaries
  if (x == 0) {
    cells[y * width + x].vx *= -1.0f;
  } else if (x == width - 1) {
    cells[y * width + x].vx *= -1.0f;
  }

  if (y == 0) {
    cells[y * width + x].vy *= -1.0f;
  } else if (y == height - 1) {
    cells[y * width + x].vy *= -1.0f;
  }

  // Add diffusion
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nx = x + i;
      int ny = y + j;
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        cells[y * width + x].vx += dt * diffusionRate * (cells[ny * width + nx].vx - cells[y * width + x].vx);
        cells[y * width + x].vy += dt * diffusionRate * (cells[ny * width + nx].vy - cells[y * width + x].vy);
      }
    }
  }

  // Add viscosity
  cells[y * width + x].vx -= dt * viscosity * cells[y * width + x].vx;
  cells[y * width + x].vy -= dt * viscosity * cells[y * width + x].vy;
}

void updateDensity(int x, int y, float dt) {
  // Advection
  float dx = 0.5f * cells[y * width + x].vx * dt;
  float dy = 0.5f * cells[y * width + x].vy * dt;

  float newDensity = cells[y * width + x].density;
  if (x - dx >= 0 && x - dx < width && y - dy >= 0 && y - dy < height) {
    newDensity += cells[(y - dy) * width + x - dx].density;
  }
  if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
    newDensity -= cells[(y + dy) * width + x + dx].density;
  }

  // Source
  if (std::abs(x - sourcePos.x) <= 2 && std::abs(y - sourcePos.y) <= 2) {
    newDensity += dt * sourceStrength;
  }

  cells[y * width + x].density = newDensity;
}

void updateSimulation(float dt) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      updateVelocity(x, y, dt);
    }
  }
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      updateDensity(x, y, dt);
    }
  }
}

void render(sf::RenderWindow& window) {
  window.clear(sf::Color::Black);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      sf::Color color = getDensityColor(cells[y * width + x].density);
      sf::RectangleShape cell(sf::Vector2f(1.0f, 1.0f));
      cell.setPosition(sf::Vector2f(x, y));
      cell.setFillColor(color);
      window.draw(cell);
    }
  }
  // Draw source indicator
  sf::CircleShape source(3.0f, 10);
  source.setFillColor(sf::Color::Red);
  source.setPosition(sf::Vector2f(sourcePos.x, sourcePos.y));
  window.draw(source);
  window.display();
}

void renderVelocityVectors(sf::RenderWindow& window) {
  float scale = 10.0f;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      sf::Vector2f velocity = cells[y * width + x].getFlow() * scale;

      // Draw an arrow at the cell position, pointing in the direction of the velocity
      sf::VertexArray arrow(sf::Lines, 2);
      arrow[0].position = sf::Vector2f(x, y);
      arrow[1].position = arrow[0].position + velocity;

      arrow[0].color = sf::Color::Black; // Set color for the start point
      arrow[1].color = sf::Color::Red; // Set color for the end point

      window.draw(arrow);
    }
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(width, height), "2D Fluid Simulation");

  sf::Clock clock;
  float dt = 0.001f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // Handle mouse click events to update source position
      if (event.type == sf::Event::MouseButtonPressed) {
        sourcePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
      }
    }

    dt = clock.restart().asSeconds();
    updateSimulation(dt);
    render(window);
  }

  return 0;
}
