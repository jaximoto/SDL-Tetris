#ifndef Game.hpp
#define Game.hpp
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
Class Game
{
public:
		Game();
		~Game();
		SDL_AppResult Init(const char* title, int width, int height, bool fullScreen);
		void HandleEvents();
		void Update();
		void Render();
		void Clean();

		bool Running() {return isRunning;}
		

		
private:
	bool isRunning;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
};
#endif // Game.hpp
