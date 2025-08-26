#include "SpriteManager.hpp"
#include "Sprite.hpp"

SpriteManager::SpriteManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
bool SpriteManager::LoadSprite(const std::string& key, const char* filePath)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(renderer, filePath);
	
	if (!sprite->IsLoaded())
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load sprite from %s: %s", filePath, SDL_GetError());
		return false;
	}
	this->spriteMap.insert({ key, sprite });
	return true;
}

bool SpriteManager::HasSprite(const std::string& key)
{
	return this->spriteMap.find(key) != this->spriteMap.end();
}

std::shared_ptr<Sprite> SpriteManager::GetSprite(const std::string& key)
{
	auto it = this->spriteMap.find(key);
	if (it != this->spriteMap.end())
		return it->second;
	else
	{
		if (fallbackSprite)
			return fallbackSprite;
		else
		{
			SDL_LogError(SDL_LOG_PRIORITY_WARN, "Sprite with key %s not found and no fallback set.", key.c_str());
			return nullptr;
		}
	}
}

void SpriteManager::SetFallbackSprite(std::shared_ptr<Sprite> fallback)
{
	this->fallbackSprite = fallback;
}

SpriteManager::~SpriteManager()
{
	spriteMap.clear();
	fallbackSprite = nullptr;
}