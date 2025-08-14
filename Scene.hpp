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
		bool Init(const char* title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen);
		bool AddSprite(const char* filePath, char *name);
		bool ClipSprite(char *name, float clipStartX, float clipStartY, float clipWidth, float clipHeight);
		bool MoveSprite(char *name, float posX, float posY);
		bool ScaleSprite(char *name, float width, float height);
		float GetSpriteWidth(char *name);
		float GetSpriteHeight(char *name);
		float GetSpriteX(char *name);
		float GetSpriteY(char *name);
		bool HandleEvents(SDL_Event *event);
		void Update();
		void Render();
		void Clean();
		void DestroySprites();
		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	Uint64 lastTick;


	Sprite* GetSprite(char *name);
	void RenderSprites();
	float CalculateDeltaTime();

	
};
// Scene.hpp
