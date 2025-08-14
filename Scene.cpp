#include "Scene.hpp"
#include <SDL3/SDL_init.h>
Scene::Scene()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->isRunning = false;
	this->deltaTime = 0.0f;
    this->lastTick = 0.0f;
}

Scene::~Scene(){}

bool Scene::Init(const char* title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen)
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
    if (!SDL_CreateWindowAndRenderer(title, sWidth, sHeight, flags, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return false;
    }
	/* Set logical size */
    if(!SDL_SetRenderLogicalPresentation(renderer, lWidth, lHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX))
    {
        SDL_Log("Couldn't set logical size: %s", SDL_GetError());
        return false;
	}
    this->lastTick = SDL_GetTicks();
	this->isRunning = true;
    return true;
}

//----------------------------------Sprites----------------------
bool Scene::AddSprite(const char *filePath, char *name)
{
   
    
    Sprite *newSprite = new Sprite(this->renderer, filePath);
    
    if (!newSprite->IsLoaded())
    {
        delete newSprite;
        return false;
    }

    this->spriteMap.insert({ name, newSprite });
    return true;
}

bool Scene::ClipSprite(char *name, float clipStartX, float clipStartY, float clipWidth, float clipHeight)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name);
        return false;
    }
    return sprite->Crop(clipStartX, clipStartY, clipWidth, clipHeight);
}

bool Scene::ScaleSprite(char *name, float width, float height)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name);
        return false;
    }

    
    return sprite->SetScreenScale(width, height);
}
bool Scene::MoveSprite(char *name, float posX, float posY)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist %s", name);
        return false;
    }


    return sprite->SetScreenPos(posX, posY);
}

float Scene::GetSpriteX(char *name)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", name);
        return -1;
    }
    return sprite->dRect.x;
}
float Scene::GetSpriteY(char *name)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name);
        return -1;
    }
    return sprite->dRect.y;
}
float Scene::GetSpriteWidth(char *name)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not %s", name);
        return -1;
    }
    return sprite->dRect.w;
}

float Scene::GetSpriteHeight(char *name)
{
    Sprite* sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name);
        return -1;
    }
    return sprite->dRect.h;
}
Sprite* Scene::GetSprite(char *name)
{
   
    auto sprite = this->spriteMap.find(name);

    if (sprite != spriteMap.end()) return nullptr;
    return spriteMap.at(name);
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
    CalculateDeltaTime();
    return;
}

float Scene::CalculateDeltaTime()
{
    Uint64 currentTick = SDL_GetTicks(); 
    this->deltaTime = currentTick - lastTick;
    lastTick = currentTick;
    return deltaTime;
}
void Scene::Render()
{
   

   
   

  
    SDL_RenderClear(renderer);
    this->RenderSprites();
    SDL_RenderPresent(renderer);

    return;
}

void Scene::RenderSprites()
{
    for (auto it = this->spriteMap.begin(); it != this->spriteMap.end(); ++it)
    {
        it->second->Render(this->renderer);
	}
}
void Scene::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	DestroySprites();
    SDL_Quit();
	SDL_Log("Scene cleaned up successfully.");
}

void Scene::DestroySprites()
{
    for (auto it = this->spriteMap.begin(); it != this->spriteMap.end(); ++it)
    {
        it->second->Clean();
    }
}

