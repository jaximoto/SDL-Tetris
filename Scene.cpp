#include "Scene.hpp"
#include <SDL3/SDL_init.h>
#include "SpriteManager.hpp"
Scene::Scene()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->isRunning = false;
	this->deltaTime = 0;
    this->lastTick = 0;
	this->spriteManager = std::make_shared<SpriteManager>(this->renderer);
}



bool Scene::Init(const char *title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen)
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

    this->spriteManager = std::make_shared<SpriteManager>(this->renderer);
    this->lastTick = SDL_GetTicks();
	this->isRunning = true;
    return true;
}

//----------------------------------Sprites----------------------
bool Scene::AddSprite(const char *filePath, std::string name)
{
    //SDL_Log("Added Sprite");
	return this->spriteManager->LoadSprite(name, filePath);
}

bool Scene::ClipSprite(std::string name, float clipStartX, float clipStartY, float clipWidth, float clipHeight)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name.c_str());
        return false;
    }
    return sprite->Crop(clipStartX, clipStartY, clipWidth, clipHeight);
}

bool Scene::ScaleSprite(std::string name, float width, float height)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name.c_str());
        return false;
    }

    
    return sprite->SetScreenScale(width, height);
}
bool Scene::MoveSprite(std::string name, float posX, float posY)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist %s", name.c_str());
        return false;
    }


    return sprite->SetScreenPos(posX, posY);
}

float Scene::GetSpriteX(std::string name)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name.c_str());
        return -1;
    }
    return sprite->dRect.x;
}
float Scene::GetSpriteY(std::string name)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name.c_str());
        return -1;
    }
    return sprite->dRect.y;
}
float Scene::GetSpriteWidth(std::string name)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not %s", name.c_str());
        return -1;
    }
    return sprite->dRect.w;
}

float Scene::GetSpriteHeight(std::string name)
{
    std::shared_ptr<Sprite> sprite = GetSprite(name);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist: %s", name.c_str());
        return -1;
    }
    return sprite->dRect.h;
}
std::shared_ptr<Sprite> Scene::GetSprite(std::string name)
{
   
	return this->spriteManager->GetSprite(name);
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
/*
void Scene::Render()
{
   

   
   

  
    SDL_RenderClear(renderer);
    //this->RenderSprites();
    SDL_RenderPresent(renderer);

    return;
}
<<<<<<< HEAD
<<<<<<< HEAD

/*
=======
=======
*/
/*
* LEGACY CODE
>>>>>>> 992ba22 (Added Vec2 and Block header files)
void Scene::RenderSprites()
{
    for (auto it = this->spriteMap.begin(); it != this->spriteMap.end(); ++it)
    {
        it->second->Render(this->renderer);
	}
}
*/

void Scene::RenderObjects()
{
    for (const auto& pair : renderMap)
    {
        int layer = pair.first;
        const auto& obj = pair.second;
        obj->Render(renderer);
    }


}
Scene::~Scene()
{
    isRunning = false;
    Clean();
}
void Scene::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	DestroyObjects();
    SDL_Quit();
	SDL_Log("Scene cleaned up successfully.");
}

/*
void Scene::DestroySprites()
{
    return;

}
*/
void Scene::DestroyObjects()
{
	this->renderMap.clear();
}

