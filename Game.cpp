#import <Game.h>

Game::Game{}
Game::~Game{}

SDL_AppResult Game::Init(const char* title, int width, int height, bool fullScreen)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int flags = 0;

    if(fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    } else {
        flags = SDL_WINDOW_RESIZABLE;
	}
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        isRunning = false;
        return SDL_APP_FAILURE;
    }
	isRunning = true;
    return SDL_APP_CONTINUE;
}
Game::void HandleEvents()
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        isRunning = false;
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}
Game::void Update()
{
    return;
}
Game::void Render()
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
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}
Game::void Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Log("Game cleaned up successfully.");
}

