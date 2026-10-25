#pragma once

#include"Common.h"
#include<memory>
#include"Source.h"
#include"Compose.h"

class Application {
private:
	SDL_Window* window;
	SDL_Event event;
	SDL_Renderer* render;
	SDL_FRect block = { 0,0,CUBE,CUBE };
	std::unique_ptr<Source> mSource;
	std::unique_ptr<Compose> mCompose;
	SDL_DisplayID myId;
	SDL_Rect boundRst;


	int pickType = 0;
	int pickCount = 0;
	int pickTime = 0;
	int pickFace = 0;
	int current_t = 0;
	int max_t = 23;

	Uint64 fingerDownTime = 0;
	float fingerDownX = 0;
	float fingerDownY = 0;
	int fingerPosX = 0;
	int fingerPosY = 0;

public:
	Application();
	~Application();
	void Update();
	void Render();
	void HandleEvent();
	void Loop();
};