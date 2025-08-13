#include "Scene.hpp"
#include <SDL3/SDL_init.h>
Scene::Scene()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->isRunning = false;
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
	isRunning = true;
    return true;
}

//----------------------------------Sprites----------------------
bool Scene::AddSprite(const char *filePath)
{
   
    
    Sprite *newSprite = new Sprite(this->renderer, filePath);
    
    if (!newSprite->IsLoaded())
    {
        delete newSprite;
        return false;
    }

    this->sprites.push_back(newSprite);
    return true;
}

bool Scene::ClipSprite(int textureIndex, float clipStartX, float clipStartY, float clipWidth, float clipHeight)
{
    Sprite* sprite = GetSprite(textureIndex);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", textureIndex);
        return false;
    }
    return this->sprites[textureIndex]->Crop(clipStartX, clipStartY, clipWidth, clipHeight);
}

bool Scene::ScaleSprite(int textureIndex, float width, float height)
{
    Sprite* sprite = GetSprite(textureIndex);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", textureIndex);
        return false;
    }

    
    return this->sprites[textureIndex]->SetScreenScale(width, height);
}
bool Scene::MoveSprite(int textureIndex, float posX, float posY)
{
    Sprite* sprite = GetSprite(textureIndex);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", textureIndex);
        return false;
    }


    return this->sprites[textureIndex]->SetScreenPos(posX, posY);
}
float Scene::GetSpriteWidth(int index)
{
    Sprite* sprite = GetSprite(index);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", index);
        return -1;
    }
    return sprite->dRect.w;
}

float Scene::GetSpriteHeight(int index)
{
    Sprite* sprite = GetSprite(index);
    if (sprite == nullptr)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Sprite does not exist at index: %d", index);
        return -1;
    }
    return sprite->dRect.h;
}
Sprite* Scene::GetSprite(int index)
{
   
    if (index < 0 || index >= sprites.size()) return nullptr;
    return sprites[index];
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
   

   
   

  
    SDL_RenderClear(renderer);
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
	DestroySprites();
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

