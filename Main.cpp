#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Tetris.hpp"
#include <SDL3_image/SDL_image.h>



// Consts
static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    
	Tetris *tetris = new Tetris();
    if(!tetris->Init("SDL3 Tetris", SCREEN_WIDTH, SCREEN_HEIGHT, false))
    {
		delete(tetris);
        return SDL_APP_FAILURE;
    }
	
	*appstate = tetris;  /* store the Tetris instance in appstate */
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    Tetris* tetris = static_cast<Tetris*>(appstate);
	if(!tetris->HandleEvents(event))
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    Tetris* tetris = static_cast<Tetris*>(appstate);
	tetris->Update();
    tetris->Render();
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    Tetris* tetris = static_cast<Tetris*>(appstate);
    tetris->Clean();
}


