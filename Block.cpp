#include "Block.hpp"

	Block::Block(Math::Vec2 pos,
		float rot,
		Math::Vec2 scale,
		std::string spriteName,
		std::shared_ptr<SpriteManager> spriteManager)
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
		this->spriteManager = spriteManager;
		this->sprite = spriteManager->GetSprite(spriteName);
	}

	bool::Block::ChangeSprite(const std::string& spriteName)
	{
		if (spriteManager)
		{
			auto newSprite = spriteManager->GetSprite(spriteName);
			if (newSprite && newSprite->IsLoaded())
			{
				sprite = newSprite;
				return true;
			}
		}
		return false;
	}
	bool Block::Render(SDL_Renderer* renderer) const
	{
		if (this->sprite && sprite->IsLoaded())
		{
			return sprite->Render(renderer, position, rotation, scale);
		}
		return false;
	}


