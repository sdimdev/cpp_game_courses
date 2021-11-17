//
// Created by dzmitry on 17.11.2021.
//

#include <stdio.h>
#include "Engine.hpp"
#include <SDL_version.h>
#include <SDL.h>

void Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Not inited");
    } else
    {
        SDL_version version = {0, 0, 0};
        SDL_GetVersion(&version);
        printf("version %d.%d.%d", version.major, version.minor, version.patch);
    }
}

void Engine::showWindow(int width, int height)
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Update the surface
        SDL_UpdateWindowSurface( window );

        //Wait two seconds
        SDL_Delay( 2000 );
    }

}
