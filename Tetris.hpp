#pragma once
#include <SDL3/SDL.h>
#include <stdio.h>

class Tetris {
public:
		Tetris();
		~Tetris();
		bool Init(const char* title, int width, int height, bool fullScreen);
		bool HandleEvents(SDL_Event *event);
		void Update();
		void Render();
		void Clean();

		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
// Tetris.hpp
