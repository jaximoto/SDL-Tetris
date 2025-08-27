#pragma once
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "IRenderable.hpp"
#include "SpriteManager.hpp"
#include <memory>
#include <string>
class Block : public IRenderable
{
public:
	Math::Vec2 position{ 0.0f, 0.0f };
	float rotation = 0.0f; // In degrees
	Math::Vec2 scale{ 1.0f, 1.0f };
	
	

	
	Block(Math::Vec2 pos = { 1.0f, 1.0f },
		float rot = 0.0f,
		Math::Vec2 scale = { 1.0f, 1.0f },
		std::string spriteName = "",
		std::shared_ptr<SpriteManager> spriteManager = nullptr);
		
	bool ChangeSprite(const std::string& spriteName) override;

	~Block() override = default;

private:
	std::shared_ptr<SpriteManager> spriteManager;
	std::shared_ptr<Sprite> sprite;
	
	bool Render(SDL_Renderer* renderer) const override;
	
		
	
	



	
	
};