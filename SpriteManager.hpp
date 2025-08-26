#pragma once
#include "Sprite.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <SDL3_image/SDL_image.h>

class SpriteManager
{
	public:
		SpriteManager(SDL_Renderer *renderer);
		~SpriteManager();
		bool LoadSprite(const std::string& key, const char* filePath);
		std::shared_ptr<Sprite> GetSprite(const std::string& key);
		bool HasSprite(const std::string& key);
		void SetFallbackSprite(std::shared_ptr<Sprite> fallback);

private:
	std::unordered_map<std::string, std::shared_ptr<Sprite>> spriteMap;
	std::shared_ptr<Sprite> fallbackSprite = nullptr;
	SDL_Renderer* renderer;
};

