#pragma once
#include <SDL3_image/SDL_image.h>
#include "IRenderable.hpp"
#include "Vec2.hpp"

class Sprite {
public:
	SDL_FRect sRect;
	SDL_FRect dRect;
	Sprite(SDL_Renderer* renderer, const char* filePath);
	
	~Sprite();
	// Set ClipPos(float x, flota y) change SRect x and y and width and height
	bool Crop(float x, float y, float w, float h);
	// Set ScreenPos(float x, flota y) change SRect x and y
	bool SetScreenPos(float x, float y);
	// SetScreenScale(w, h) edit SRect width and heght
	bool SetScreenScale(float w, float h);
	bool Render(SDL_Renderer* renderer, Math::Vec2 position, float rotation, Math::Vec2 scale);
	
	void Clean();
	bool IsLoaded() const;

private:
	SDL_FRect clipSize;
	SDL_FRect renderSize;
	SDL_Texture* texture;
	bool isLoaded = false;

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filePath);
	SDL_Renderer* renderer;
};