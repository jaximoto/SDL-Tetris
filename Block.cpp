#include "Block.hpp"

	Block::Block(Math::Vec2 pos,
		float rot,
		Math::Vec2 scale,
		std::string spriteName)
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
		this->sprite = 
	}

	bool Block::Render(SDL_Renderer* renderer) const
	{
		if (this->sprite && sprite->IsLoaded())
		{
			return sprite->Render(renderer, position, rotation, scale);
		}
		return false;
	}


