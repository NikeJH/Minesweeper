#include"Source.h"
#include"Common.h"
#include<iostream>
#include<string>
#include<format>
#include<SDL3_image/SDL_image.h>

using namespace std;

Source::Source(SDL_Renderer* _render) :render(_render), faceSurface{}, countSurface{}, typeSurface{}, timeSurface{} {
	InitCount();
	InitTime();
	InitFace();
	InitType();
	blockRst.w = CUBE;
	blockRst.h = CUBE;
}
void Source::InitFace() {
	SDL_Surface* temp;
	// Smile
	temp = IMG_Load("res//st_happy.png");
	faceSurface[0] = SDL_CreateTextureFromSurface(render, temp);
	// Cry
	temp = IMG_Load("res//st_sad.png");
	faceSurface[1] = SDL_CreateTextureFromSurface(render, temp);
	// Neutral 
	temp = IMG_Load("res//st_neutral.png");
	faceSurface[2] = SDL_CreateTextureFromSurface(render, temp);
}
void Source::InitType() {
	SDL_Surface* temp;
	temp = IMG_Load("res//blank.png");
	typeSurface[0] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//flag.png");
	typeSurface[1] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//ask.png");
	typeSurface[2] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//flag_wrong.png");
	typeSurface[3] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//mine.png");
	typeSurface[4] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//mine_wrong.png");
	typeSurface[5] = SDL_CreateTextureFromSurface(render, temp);
	temp = IMG_Load("res//mine_blood.png");
	typeSurface[6] = SDL_CreateTextureFromSurface(render, temp);
	SDL_DestroySurface(temp);
}
void Source::InitCount() {
	SDL_Surface* temp;
	int i = 1;
	for (int i = 0; i < 9; i++) {
		string fileName = "res//num_" + format("{}", i) + ".png";
		temp = IMG_Load(fileName.c_str());
		countSurface[i] = SDL_CreateTextureFromSurface(render, temp);
	}
	SDL_DestroySurface(temp);
}
void Source::InitTime() {
	SDL_Surface* temp;
	int i = 1;
	for (int i = 0; i < 10; i++) {
		string fileName = "res//time_" + format("{}", i) + ".png";
		temp = IMG_Load(fileName.c_str());
		timeSurface[i] = SDL_CreateTextureFromSurface(render, temp);
	}
	SDL_DestroySurface(temp);
}
void Source::RenderType(int index, int _x, int _y) {
	blockRst.x = _x;
	blockRst.y = _y;
	if (index < 7 && index >= 0) {
		SDL_RenderTexture(render, typeSurface[index], nullptr, &blockRst);
	}
	else {
		SDL_RenderTexture(render, typeSurface[0], nullptr, &blockRst);
	}

}
void Source::RenderCount(int index, int _x, int _y) {
	blockRst.x = _x;
	blockRst.y = _y;
	if (index < 9 && index >= 0) {
		SDL_RenderTexture(render, countSurface[index], nullptr, &blockRst);
	}
	else {
		SDL_RenderTexture(render, countSurface[0], nullptr, &blockRst);
	}

}
void Source::RenderTime(int index, int _x, int _y) {
	blockRst.x = _x;
	blockRst.y = _y;
	if (index < 10 && index >= 0) {
		SDL_RenderTexture(render, timeSurface[index], nullptr, &blockRst);
	}
	else {
		SDL_RenderTexture(render, timeSurface[0], nullptr, &blockRst);
	}

}
void Source::RenderFace(int index, int _x, int _y) {
	blockRst.x = _x;
	blockRst.y = _y;
	if (index < 3 && index >= 0) {
		SDL_RenderTexture(render, faceSurface[index], nullptr, &blockRst);
	}
	else {
		SDL_RenderTexture(render, faceSurface[0], nullptr, &blockRst);
	}

}
Source::~Source() {
	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(faceSurface[i]);
	}
	for (int i = 0; i < 10; i++) {
		SDL_DestroyTexture(timeSurface[i]);
	}
	for (int i = 0; i < 9; i++) {
		SDL_DestroyTexture(countSurface[i]);
	}
	for (int i = 0; i < 7; i++) {
		SDL_DestroyTexture(typeSurface[i]);
	}
}