#pragma once
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "IRenderable.hpp"
#include <memory>
class Block : public IRenderable
{
public:
	Math::Vec2 position{ 0.0f, 0.0f };
	float rotation = 0.0f; // In degrees
	Math::Vec2 scale{ 1.0f, 1.0f };
	
	

	
	Block(Math::Vec2 pos = { 1.0f, 1.0f },
		float rot = 0.0f,
		Math::Vec2 scale = { 1.0f, 1.0f },
		std::unique_ptr<Sprite> sprite)
		: position(pos),
		rotation(rot),
		scale(scale),
		sprite(std::move(sprite))
	{
	}
	~Block() override = default;

private:
	std::unique_ptr<Sprite> sprite;
	
	bool Render(SDL_Renderer* renderer) const override;
	
		
	
	



	
	
};