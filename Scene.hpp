#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
<<<<<<< HEAD
#include <unordered_map>
#include <memory>
#include "Sprite.hpp"
#include "SpriteManager.hpp"
=======
#include <map>
#include <memory>
#include "Sprite.hpp"
#include "IRenderable.hpp"
>>>>>>> d61c2c4 (Refactored spriteMap to renderMap)


class Scene {
public:
		SDL_Window* window;
		SDL_Renderer* renderer;
<<<<<<< HEAD
		std::shared_ptr<SpriteManager> spriteManager;

=======
		std::multimap<int, std::shared_ptr<IRenderable>> renderMap;
>>>>>>> d61c2c4 (Refactored spriteMap to renderMap)
		
		float deltaTime;

		Scene();
		~Scene();
		bool Init(const char *title, int sWidth, int sHeight, int lWidth, int lHeight, bool fullScreen);
		/*
		bool AddSprite(const char *filePath, std::string name);
		bool ClipSprite(std::string name, float clipStartX, float clipStartY, float clipWidth, float clipHeight);
		bool MoveSprite(std::string name, float posX, float posY);
		bool ScaleSprite(std::string name, float width, float height);
		float GetSpriteWidth(std::string name);
		float GetSpriteHeight(std::string name);
		float GetSpriteX(std::string name);
		float GetSpriteY(std::string name);
		*/
		bool HandleEvents(SDL_Event *event);
		void Update();
		void RenderObjects();
		void Clean();
		//void DestroySprites();
		void DestroyObjects();
		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	Uint64 lastTick;
<<<<<<< HEAD
	
	std::shared_ptr<Sprite> GetSprite(std::string name);
	void RenderSprites();
=======


	//Sprite* GetSprite(std::string name);
	void RenderObjects();
>>>>>>> 6e6a247 (Created IRenderable parent class for renderable objects)
	float CalculateDeltaTime();

	
};
// Scene.hpp
