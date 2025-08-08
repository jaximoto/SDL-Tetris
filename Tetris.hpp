#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Sprite.hpp"


class Tetris {
public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::vector<Sprite*> sprites;
		Tetris();
		~Tetris();
		bool Init(const char* title, int width, int height, bool fullScreen);
		bool AddSprite(const char* filePath);
		bool HandleEvents(SDL_Event *event);
		void Update();
		void Render();
		void Clean();
		void DestroySprites();
		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	
	void RenderSprites();
	
};
// Tetris.hpp
