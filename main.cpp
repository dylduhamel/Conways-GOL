/**
 * @author Dylan Duhamel { duhadm19@alumni.wfu.edu } 
 * @date Nov. 13, 2023
 *
 * Conway's game of life simulation
 **/

#include "screen.h"
#include <unistd.h>
#include <cmath>

const int GAME_WIDTH = 100;
const int GAME_HEIGHT = 100;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const double PI = 3.14159265358979323846;

bool isAlive(int x, int y, std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> &game)
{
	int aliveNeighbors = 0;

	// Side neighbors
	// // W
	if (x > 0 && game[x - 1][y] == 1)
		aliveNeighbors += 1;
	// E
	if (x < GAME_WIDTH && game[x + 1][y] == 1)
		aliveNeighbors += 1;
	// N
	if (y > 0 && game[x][y - 1] == 1)
		aliveNeighbors += 1;
	// S
	if (y < GAME_HEIGHT && game[x][y + 1] == 1)
		aliveNeighbors += 1;

	// Corner neighbors
	// NW
	if (x > 0 && y > 0 && game[x - 1][y - 1] == 1)
		aliveNeighbors += 1;
	// NE
	if (x < GAME_WIDTH && y > 0 && game[x + 1][y - 1] == 1)
		aliveNeighbors += 1;
	// SW
	if (x > 0 && y < GAME_HEIGHT && game[x - 1][y + 1] == 1)
		aliveNeighbors += 1;
	// SE
	if (x < GAME_WIDTH && y < GAME_HEIGHT && game[x + 1][y + 1])
		aliveNeighbors += 1;

	// Conway's rules
	if (game[x][y] == 1 && aliveNeighbors < 2)
		return false;
	if (game[x][y] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3))
		return true;
	if (game[x][y] == 1 && aliveNeighbors > 3)
		return false;
	if (game[x][y] == 0 && aliveNeighbors == 3)
		return true;

	return false;
}

int main()
{
	// SDL2 graphics object
	G screen(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

	// Both matrix for the swapping on Conways enviornment
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display{};
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap{};

	// Pixel colors
	uint8_t r = static_cast<uint8_t>(255);
	uint8_t g = static_cast<uint8_t>(0);
	uint8_t b = static_cast<uint8_t>(0);
	uint8_t a = static_cast<uint8_t>(255);

	// Speed of color change
	const double colorChangeSpeed = 0.001;

	// Instantiate the display matrix with random points
	for (auto &row : display)
	{
		// Populate either 1 or 0 for each element
		std::generate(row.begin(), row.end(), []()
					  { return rand() % 5 == 0 ? 1 : 0; });
	}

	while (true)
	{
		// Clear rendered pixels
		screen.clearpixels();

		// Calculate a smooth transition for each color component
		unsigned int ticks = SDL_GetTicks();												// Milliseconds since SDL initialization
		r = static_cast<uint8_t>((sin(ticks * colorChangeSpeed) + 1) * 127.5);				// Oscillates between 0 and 255
		g = static_cast<uint8_t>((sin(ticks * colorChangeSpeed + 2 * PI / 3) + 1) * 127.5); // 120 degrees out of phase with red
		b = static_cast<uint8_t>((sin(ticks * colorChangeSpeed + 4 * PI / 3) + 1) * 127.5); // 240 degrees out of phase with red
		
		// Check each pixel based on rules
		for (int i = 0; i < GAME_WIDTH; i++)
		{
			for (int j = 0; j < GAME_HEIGHT; j++)
			{
				// Check pixel for rules
				swap[i][j] = isAlive(i, j, display) ? 1 : 0;
			}
		}

		// Draw pixels
		for (int i = 0; i < GAME_WIDTH; i++)
		{
			for (int j = 0; j < GAME_HEIGHT; j++)
			{
				// Check pixel for rules
				if (swap[i][j])
				{
					screen.drawpixel(i, j, r, g, b, a);
				}
			}
		}

		// Swap matrix
		std::copy(swap.begin(), swap.end(), display.begin());

		// Display to screen
		screen.update();

		// Delay to control frame rate
		SDL_Delay(100);

		// Handle input
		screen.input();
	}

	return 0;
}
