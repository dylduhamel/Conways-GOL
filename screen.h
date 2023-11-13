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
    vector<SDL_FPoint> points;
    vector<SDL_Color> colors;
    SDL_Event event;
    public:
    G(int width, int height) 
    {
       SDL_Init(SDL_INIT_VIDEO); 
       SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
       SDL_RenderSetScale(renderer,4,4);
    }

    void drawpixel(double xm, double ym, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255) 
    {
        points.emplace_back(xm,ym);
        colors.emplace_back(r,g,b,a);
    }
    
    void clearpixels()
    {
        points.clear();
    }

    void update(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
        
        for(long unsigned int i = 0; i < points.size(); i++)
        {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderDrawPointF(renderer, points[i].x,points[i].y);
        }


        SDL_RenderPresent(renderer);
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
