#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer* renderer, const char* filePath)
{
this->renderer = renderer;
this->texture = LoadTexture(renderer, filePath);
SDL_GetTextureSize( this->texture, &this->width, &this->height);
this->isLoaded = true;
}

SDL_Texture* Sprite::LoadTexture(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	if (!texture) {
		SDL_Log("Failed to load texture: %s with error: %s", filePath, SDL_GetError());
		return nullptr;
	}
	return texture;
}

bool Sprite::Render(SDL_Renderer* renderer, float width, float height)
{
	SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
}
Sprite::~Sprite()
{
	Clean();
}

