#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer* renderer, const char* filePath)
{
	// create static sRect and dRect
	this->sRect = SDL_FRect();
	this->dRect = SDL_FRect();
	this->renderer = renderer;
	this->texture = LoadTexture(renderer, filePath);
if (this->texture)
{
	if (!SDL_GetTextureSize(this->texture, &this->dRect.w, &this->dRect.h))
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Error: %s", SDL_GetError());
	}
	this->isLoaded = true;
}
else
SDL_LogError(SDL_LOG_PRIORITY_INVALID, "Texture from location: %s, could not be loaded: %s", filePath, SDL_GetError());

}
// Set ClipPos(float x, flota y) change SRect x and y
bool Sprite::Crop(float x, float y, float w, float h)
{
	if (!isLoaded)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Error, texture is not loaded");
		return false;
	}
		
	this->sRect.x = x;
	this->sRect.y = y;
	this->sRect.w = w;
	this->sRect.h = h;
	return true;
}


// Set ScreenPos(float x, flota y) change SRect x and y
bool Sprite::SetScreenPos(float x, float y)
{
	if (!isLoaded)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Error, texture is not loaded");
		return false;
	}
	this->dRect.x = x;
	this->dRect.y = y;
	return true;
}
// SetScreenScale(w, h) edit SRect width and heght
bool Sprite::SetScreenScale(float w, float h)
{
	if (!isLoaded)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Error, texture is not loaded");
		return false;
	}
	this->dRect.w = w;
	this->dRect.h = h;
	return true;
}
SDL_Texture* Sprite::LoadTexture(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	if (!texture) {
		SDL_Log("Failed to load texture: %s with error: %s", filePath, SDL_GetError());
		return nullptr;
	}
	this->isLoaded = true;
	return texture;
}

bool Sprite::IsLoaded() const
{
	return this->isLoaded;
}

bool Sprite::Render(SDL_Renderer* renderer)
{
	/*
	SDL_Log("Rendering sprite with sRect: x=%f, y=%f, w=%f, h=%f",
		this->sRect.x, this->sRect.y, this->sRect.w, this->sRect.h);

	SDL_Log("Rendering sprite with dRect: x=%f, y=%f, w=%f, h=%f",
		this->dRect.x, this->dRect.y, this->dRect.w, this->dRect.h);
	
	*/
	SDL_FRect* s = SDL_RectEmptyFloat(&this->sRect) ? nullptr : &this->sRect;
	SDL_FRect* d = SDL_RectEmptyFloat(&this->dRect) ? nullptr : &this->dRect;
	
	return SDL_RenderTexture(this->renderer, this->texture, s, d);

}
Sprite::~Sprite()
{
	Clean();
}

void Sprite::Clean()
{
	SDL_DestroyTexture(this->texture);
	texture = nullptr;
}

