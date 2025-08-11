#pragma once
#include <SDL3_image/SDL_image.h>

class Sprite {
public:
	SDL_FRect *sRect;
	SDL_FRect *dRect;
	Sprite(SDL_Renderer* renderer, const char* filePath, SDL_FRect* sRect = nullptr, SDL_FRect* dRect = nullptr);
	
	~Sprite();
	//SetSpriteSize(float x, float y, float w, float h)
	bool Render(SDL_Renderer* renderer);
	void Clean();
	bool IsLoaded() const;

private:
	SDL_Texture* texture;
	bool isLoaded = false;

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filePath);
	SDL_Renderer* renderer;
};