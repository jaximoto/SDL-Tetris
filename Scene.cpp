#include "Scene.hpp"
#include <SDL3/SDL_init.h>
Scene::Scene()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->isRunning = false;
}

Scene::~Scene(){}

bool Scene::Init(const char* title, int width, int height, bool fullScreen)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    if(!SDL_SetAppMetadata("SDL3 Tetris", "1.0", "com.TetrisSDL3"))
    {
        SDL_Log("SDL could not set metadata! SDL_Error: %s", SDL_GetError());
        return false;
    }
    int flags = fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return false;
    }
	isRunning = true;
    return true;
}

bool Scene::AddSprite(const char *filePath, float x, float y, float w, float h)
{
    SDL_FRect* src = new SDL_FRect{ x, y, w, h };
    
    Sprite *newSprite = new Sprite(this->renderer, filePath, src, src);
    
    if (!newSprite->IsLoaded())
    {
        delete newSprite;
        return false;
    }

    this->sprites.push_back(newSprite);
    return true;
}
bool Scene::HandleEvents(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        isRunning = false;
        return false;  /* end the program, reporting success to the OS. */
    }
    return true;
}
void Scene::Update()
{
    return;
}
void Scene::Render()
{
    const char* message = "Hello World!";
    int w = 0, h = 0;
    float x, y;
    const float scale = 4.0f;

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
    this->RenderSprites();
    SDL_RenderPresent(renderer);

    return;
}

void Scene::RenderSprites()
{
    for (int i = 0; i < this->sprites.size(); i++)
    {
        this->sprites[i]->Render(this->renderer);
    }
}
void Scene::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	SDL_Log("Scene cleaned up successfully.");
}

void Scene::DestroySprites()
{
    for (int i = 0; i < this->sprites.size(); i++)
    {
        this->sprites[i]->Clean();
    }
}

