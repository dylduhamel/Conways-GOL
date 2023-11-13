#include "screen.h"
#include <unistd.h>

const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

bool isAlive(int x, int y, std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game)
{
	int aliveNeighbors = 0;

	// Side neighbors
	// // W
	if (x > 0 && game[x-1][y] == 1) aliveNeighbors += 1;
	// E
	if (x < GAME_WIDTH && game[x+1][y] == 1) aliveNeighbors += 1;
	// N
	if (y > 0 && game[x][y-1] == 1) aliveNeighbors += 1;
	// S
	if (y < GAME_HEIGHT && game[x][y+1] == 1) aliveNeighbors += 1;

	// Corner neighbors
	// NW 
	if (x > 0 && y > 0 && game[x-1][y-1] == 1) aliveNeighbors += 1;
	// NE
	if (x < GAME_WIDTH && y > 0 && game[x+1][y-1] == 1) aliveNeighbors += 1;
	//SW
	if (x > 0 && y < GAME_HEIGHT && game[x-1][y+1] == 1) aliveNeighbors += 1;
	//SE
	if (x < GAME_WIDTH && y < GAME_HEIGHT && game[x+1][y+1]) aliveNeighbors += 1;

	// Conway's rules
	if (game[x][y] == 1 && aliveNeighbors < 2) return false;
	if (game[x][y] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3)) return true;
	if (game[x][y] == 1 && aliveNeighbors > 3) return false;
	if (game[x][y] == 0 && aliveNeighbors == 3) return true;

	return false;
}	

int main() 
{
	// SDL2 graphics object
	G screen;

	// Both matrix for the swapping on Conways enviornment
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display {};
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap {};
	
	// Instantiate the display matrix with random points
	for (auto& row : display)
	{
		// Populate either 1 or 0 for each element
		std::generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1 : 0; });
	}

	while (true) 
	{
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
					screen.drawpixel(i,j);
				}
                        }
                }

		// Swap matrix
		std::copy(swap.begin(), swap.end(), display.begin());

		// Display to screen
		screen.update();
		SDL_Delay(20);
		screen.input();
		screen.clearpixels();
	}

	return 0;
}
