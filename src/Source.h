#pragma once
#include<SDL3/SDL.h>

class Source {
private:
	SDL_Renderer* render;
	SDL_Window* window;
	SDL_Texture* faceSurface[3]{};
	SDL_Texture* timeSurface[10]{};
	SDL_Texture* typeSurface[7]{};
	SDL_Texture* countSurface[9]{};
	SDL_FRect blockRst;

public:
	Source(SDL_Renderer* _render);
	void InitType();
	void InitCount();
	void InitTime();
	void InitFace();

	void RenderType(int index, int x, int y);
	void RenderTime(int index, int x, int y);
	void RenderCount(int index, int x, int y);
	void RenderFace(int index, int x, int y);
	~Source();
};