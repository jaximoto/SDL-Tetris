#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer* renderer, const char* filePath)
{
this->renderer = renderer;
this->texture = LoadTexture(renderer, filePath);
if (this->texture)
{
	SDL_GetTextureSize(this->texture, &this->width, &this->height);
	this->isLoaded = true;
}
else
SDL_LogError(SDL_LOG_PRIORITY_INVALID, "Texture from location: %s, could not be loaded: %s", filePath, SDL_GetError());

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
	return SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
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

