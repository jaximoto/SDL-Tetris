#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Sprite.hpp"


class Scene {
public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::vector<Sprite*> sprites;
		float deltaTime;

		Scene();
		~Scene();
		bool Init(const char* title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen);
		bool AddSprite(const char* filePath);
		bool ClipSprite(int textureIndex, float clipStartX, float clipStartY, float clipWidth, float clipHeight);
		bool MoveSprite(int textureIndex, float posX, float posY);
		bool ScaleSprite(int textureIndex, float width, float height);
		float GetSpriteWidth(int index);
		float GetSpriteHeight(int index);
		float GetSpriteX(int index);
		float GetSpriteY(int index);
		bool HandleEvents(SDL_Event *event);
		void Update();
		void Render();
		void Clean();
		void DestroySprites();
		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	Uint64 lastTick;


	Sprite* GetSprite(int index);
	void RenderSprites();
	float CalculateDeltaTime();

	
};
// Scene.hpp
