#pragma once
#include "Vec2.hpp"
#include "Sprite.hpp"
#include <memory>
class Block
{
public:
	Math::Vec2 position{ 0.0f, 0.0f };
	float rotation = 0.0f; // In degrees
	Math::Vec2 scale{ 1.0f, 1.0f };
	
	std::unique_ptr<Sprite> sprite = nullptr;

	Block() = default;
	Block(Math::Vec2 pos = { 1.0f, 1.0f },
		float rot = 0.0f,
		Math::Vec2 scale = { 1.0f, 1.0f },
		std::unique_ptr<Sprite> sprite = nullptr)
		: position(pos),
		rotation(rot),
		scale(scale),
		sprite(std::move(sprite))
	{
	}
	
	void Render(SDL_Renderer* renderer)
	{
		if (sprite && sprite->IsLoaded())
		{
			sprite->Render(renderer, position, rotation, scale);
		}
	}
	



	
	
};