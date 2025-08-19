#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "Sprite.hpp"


class Scene {
public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::unordered_map<std::string, Sprite*> spriteMap;
		
		float deltaTime;

		Scene();
		~Scene();
		bool Init(const char *title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen);
		bool AddSprite(const char *filePath, std::string name);
		bool ClipSprite(std::string name, float clipStartX, float clipStartY, float clipWidth, float clipHeight);
		bool MoveSprite(std::string name, float posX, float posY);
		bool ScaleSprite(std::string name, float width, float height);
		float GetSpriteWidth(std::string name);
		float GetSpriteHeight(std::string name);
		float GetSpriteX(std::string name);
		float GetSpriteY(std::string name);
		bool HandleEvents(SDL_Event *event);
		void Update();
		void Render();
		void Clean();
		void DestroySprites();
		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	Uint64 lastTick;


	Sprite* GetSprite(std::string name);
	void RenderSprites();
	float CalculateDeltaTime();

	
};
// Scene.hpp
