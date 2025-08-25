#include "Block.hpp"

	Block::Block(Math::Vec2 pos = { 1.0f, 1.0f },
		float rot = 0.0f,
		Math::Vec2 scale = { 1.0f, 1.0f },
		std::unique_ptr<Sprite> sprite)
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
		this->sprite = std::move(sprite);
	}

	bool Block::Render(SDL_Renderer* renderer) const
	{
		if (this->sprite && sprite->IsLoaded())
		{
			return sprite->Render(renderer, position, rotation, scale);
		}
	}


