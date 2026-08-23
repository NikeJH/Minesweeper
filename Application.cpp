#include"Application.h"
#include"Game.h"
#include<SDL3_image/SDL_image.h>

Application::Application() :window(nullptr), event{}, render(nullptr) {
	running = true;
	myId = SDL_GetPrimaryDisplay();
	window = SDL_CreateWindow("扫雷", WIDTH, HEIGHT, NULL);
	SDL_Surface* icoSurface = IMG_Load("res/mine.png");
	SDL_SetWindowIcon(window, icoSurface);
	SDL_DestroySurface(icoSurface);
	render = SDL_CreateRenderer(window, nullptr);
	mSource = std::make_unique<Source>(render);
	mCompose = std::make_unique<Compose>(*mSource);
	GameInit();
}
void Application::HandleEvent() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_EVENT_QUIT:
		running = false;
		break;
	case SDL_EVENT_KEY_DOWN:
		if (event.key.key == SDLK_SPACE) {
			OpenBasic();
		}
		break;
	case SDL_EVENT_KEY_UP:
		if (event.key.key == SDLK_SPACE) {
			CloseBasic();
		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN: {
		int mouseX = event.button.x;
		int mouseY = event.button.y;

		SDL_MouseButtonFlags buttonFlag = event.button.button;
		MousePos mouse = transformMouse(mouseX, mouseY);
		if (buttonFlag == SDL_BUTTON_RIGHT) {
			if (GetBState(mouse) == FLAG) {
				AskBlock(mouse);
			}
			else if (GetBState(mouse) == ASK) {
				CloseBlock(mouse);
			}
			else if (GetBState(mouse) == CLOSE) {
				FlagBlock(mouse);
			}
			if (GameState == READY) goto StartTimer;
		}
		else if (buttonFlag == SDL_BUTTON_LEFT) {
			if (mouseX > 5 * CUBE && mouseX < 6 * CUBE && mouseY>0 && mouseY < MENU) {
				ResetAll();
			}
			else {
				OpenBlock(mouse);
				if (GameState == READY) goto StartTimer;
			}
		}
	StartTimer:
		if (GameState == READY || !resetTime) {
			Timer = true;
			GameState = RUN;
		}
		break;
	}
	}
}
void Application::Update() {
	mCompose->Refresh();
	CheckGameState();
	current_t++;
	if (current_t > max_t) {
		pickType++;
		if (pickType > 10) {
			pickType = 0;
		}
		current_t = 0;
	}
	if (GameState == WIN) Timer = false;
	if (GameState == LOSE)Timer = false;
}
void Application::Render() {
	SDL_SetRenderDrawColor(render, 185, 185, 185, 255);
	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
	SDL_RenderFillRect(render, &block);
	mCompose->SetMenu(Mines, FaceIndex, Timer);
	if (GameState == RUN || GameState == READY)
	{
		FaceIndex = 2;
		mCompose->SetMenu(Mines, FaceIndex, Timer);
		mCompose->SetMain();
		SDL_RenderPresent(render);
	}
	else if (GameState == LOSE) {
		FaceIndex = 1;
		mCompose->SetMenu(Mines, FaceIndex, Timer);
		mCompose->SetLose();
		SDL_RenderPresent(render);
	}
	else if (GameState == WIN) {
		FaceIndex = 0;
		mCompose->SetMenu(Mines, FaceIndex, Timer);
		mCompose->SetWin();
		SDL_RenderPresent(render);
	}
}
void Application::Loop() {
	while (running) {
		HandleEvent();
		Render();
		Update();
	}
}
Application::~Application() {
	SDL_DestroyWindow(window);
}