#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Scene.hpp"
#include "Sprite.hpp"



// Consts
static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int LOGICAL_WIDTH = 400;
static const int LOGICAL_HEIGHT = 300;
static float timeAccumulator = 0.0f;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    
	Scene *tetris = new Scene();
    if(!tetris->Init("SDL3 Scene", SCREEN_WIDTH, SCREEN_HEIGHT, LOGICAL_WIDTH, LOGICAL_HEIGHT, false))
    {
		delete(tetris);
        return SDL_APP_FAILURE;
    }
    tetris->AddSprite("C:/GLP/SDLx64-0/Assets/cblock.png", "square");
    tetris->ClipSprite(0, 485, 303, 475, 474);
    //tetris->ClipSprite(0, 485, 303, 600, 600);
    //tetris->ClipSprite(0, 0, 0, 1920, 1080);
    tetris->ScaleSprite(0, 32, 32);
    //SDL_Log("get sprite width: %f", tetris->GetSpriteWidth(0));
    //SDL_Log("get sprite height: %f", tetris->GetSpriteHeight(0));
    //tetris->MoveSprite(0,  ((SCREEN_WIDTH - tetris->GetSpriteWidth(0)) / 2), ((SCREEN_HEIGHT - tetris->GetSpriteHeight(0)) / 2));
    if(tetris->MoveSprite(0, 200,150))
        //SDL_Log("returned true");
    *appstate = tetris;  /* store the Scene instance in appstate */
	*appstate = tetris;  /* store the Scene instance in appstate */
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    Scene* tetris = static_cast<Scene*>(appstate);
	if(!tetris->HandleEvents(event))
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    Scene* tetris = static_cast<Scene*>(appstate);
	tetris->Update();
    float deltaTime = tetris->deltaTime; 
    timeAccumulator += deltaTime;
    float lastTime = 0.0f;

    

    if (timeAccumulator > lastTime + 1000)
    {
        tetris->MoveSprite(0, tetris->GetSpriteX(0), tetris->GetSpriteY(0) + 1 * tetris->deltaTime);
       
        lastTime = timeAccumulator;
    }

	//tetris->MoveSprite(0, tetris->GetSpriteX(0), tetris->GetSpriteY(0) + 1);

    
    tetris->Render();
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    Scene* tetris = static_cast<Scene*>(appstate);
    tetris->Clean();
}


