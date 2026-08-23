#include"Application.h"
#include<SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	Application minesweeper;
	minesweeper.Loop();
	return 0;
}