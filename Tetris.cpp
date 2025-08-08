#include "Tetris.hpp"

Tetris::Tetris()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->isRunning = false;
}

Tetris::~Tetris(){}

bool Tetris::Init(const char* title, int width, int height, bool fullScreen)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
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

bool Tetris::AddSprite(const char *filePath)
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
bool Tetris::HandleEvents(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        isRunning = false;
        return false;  /* end the program, reporting success to the OS. */
    }
    return true;
}
void Tetris::Update()
{
    return;
}
void Tetris::Render()
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

void Tetris::RenderSprites()
{
    for (int i = 0; i < this->sprites.size(); i++)
    {
        this->sprites[i]->Render(this->renderer);
    }
}
void Tetris::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	SDL_Log("Tetris cleaned up successfully.");
}

void Tetris::DestroySprites()
{
    for (int i = 0; i < this->sprites.size(); i++)
    {
        this->sprites[i]->Clean();
    }
}

