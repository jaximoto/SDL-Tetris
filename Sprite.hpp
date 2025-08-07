#pragma once
#include <SDL3_image/SDL_image.h>

class Sprite {
public:
	Sprite(SDL_Renderer* renderer, const char* filePath);
	~Sprite();
	bool Render(SDL_Renderer* renderer, int x, int y, float width, float height);
	void Clean();

private:
	SDL_Texture* texture;
	float width;
	float height;
	bool isLoaded = false;

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filePath);
	SDL_Renderer* renderer;
};