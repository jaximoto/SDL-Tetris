#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer* renderer, const char* filePath, SDL_FRect *sRect, SDL_FRect *dRect)
{
	this->sRect = sRect;
	this->sRect = dRect;
	this->renderer = renderer;
	this->texture = LoadTexture(renderer, filePath);
if (this->texture)
{
	SDL_GetTextureSize(this->texture, NULL, NULL);
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
	
	/*SDL_Log("Rendering sprite with sRect: x=%f, y=%f, w=%f, h=%f",
		this->sRect->x, this->sRect->y, this->sRect->w, this->sRect->h);
	*/
	return SDL_RenderTexture(this->renderer, this->texture, this->sRect, NULL);
}
Sprite::~Sprite()
{
	Clean();
}

void Sprite::Clean()
{
	SDL_DestroyTexture(this->texture);
	SDL_free(this->sRect);
	SDL_free(this->dRect);
	texture = nullptr;
}

