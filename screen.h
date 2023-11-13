#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm>

#pragma once 

using namespace std;

class G {

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool done;
    SDL_Event event;

    // Pixel scaling
    int matrix_width;
    int matrix_height;
    float cell_width;
    float cell_height;

    public:
    G(int width, int height, int m_width, int m_height) 
    {
       SDL_Init(SDL_INIT_VIDEO); 
       SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
       SDL_RenderSetScale(renderer,1,1);

       matrix_width = m_width;
       matrix_height = m_height;
       cell_width = static_cast<float>(width) / matrix_width;
       cell_height = static_cast<float>(height) / matrix_height;
    }

    void drawpixel(int xm, int ym, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255)
    {
        SDL_Rect rect;
        rect.x = static_cast<int>(xm * cell_width);
        rect.y = static_cast<int>(ym * cell_height);
        rect.w = static_cast<int>(cell_width);
        rect.h = static_cast<int>(cell_height);

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderFillRect(renderer, &rect);
    }

    void clearpixels(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a); // Set the color to clear with.
        SDL_RenderClear(renderer);                    // Clear the renderer with the draw color.
    }

    void update()
    {
        SDL_RenderPresent(renderer); // Present the renderer, which updates the screen with rendered content.
    }

    void input() {
        while( SDL_PollEvent( &event ) )
        {  
            switch( event.type )
            {
                /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;

                default:
                    break;
            }
        }
    }

};
