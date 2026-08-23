#include"Source.h"
#include"Compose.h"
#include"Common.h"
#include"Game.h"

Compose::Compose(Source& _r) :render(_r) {
	// BlocksState[2][3].mBState = OPEN;
}
void Compose::AddCounter(int time) {
	time = time - flag;
	int units = time % 10;
	int tens = (time / 10) % 10;
	int hundreds = (time / 100) % 10;
	int thousands = (time / 1000);
	render.RenderTime(thousands, 0, 0);
	render.RenderTime(hundreds, 1 * CUBE, 0);
	render.RenderTime(tens, 2 * CUBE, 0);
	render.RenderTime(units, 3 * CUBE, 0);
}
void Compose::AddFace(int index) {
	render.RenderFace(index, 5 * CUBE, 0);
}
void Compose::AddTimer(bool isBegin) {
	{
		static bool i = true;
		if (i) {
			timeStart = SDL_GetTicks();
			i = false;
		}
	}
	now = SDL_GetTicks();

	if (isBegin) {
		if (now - timeStart > delayMs) {
			timeS++;
			timeStart = now;
		}
	}
	int units = timeS % 10;
	int tens = (timeS / 10) % 10;
	int hundreds = (timeS / 100) % 10;
	int thousands = (timeS / 1000);
	render.RenderTime(units, WIDTH - CUBE, 0);
	render.RenderTime(tens, WIDTH - 2 * CUBE, 0);
	render.RenderTime(hundreds, WIDTH - 3 * CUBE, 0);
	render.RenderTime(thousands, WIDTH - 4 * CUBE, 0);
}
void Compose::SetMenu(int left, int index, bool isBegin) {
	AddCounter(left);
	AddFace(index);
	AddTimer(isBegin);
}
void Compose::SetMain() {
	int rows = BlocksState.size();
	int cols = BlocksState[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (BlocksState[i][j].mBState == CLOSE) {
				render.RenderType(0, j * CUBE, i * CUBE + MENU);
			}
			else if (BlocksState[i][j].mBState == FLAG) {
				render.RenderType(1, j * CUBE, i * CUBE + MENU);
			}
			else if (BlocksState[i][j].mBState == OPEN) {
				if (BlocksState[i][j].Boom) {
					render.RenderType(4, j * CUBE, i * CUBE + MENU);
				}
				else {
					render.RenderCount(BlocksState[i][j].num, j * CUBE, i * CUBE + MENU);
				}
			}
			else if (BlocksState[i][j].mBState == ASK) {
				render.RenderType(2, j * CUBE, i * CUBE + MENU);
			}
		}
	}
}
void Compose::Refresh() {
	flag = 0;
	for (int i = 0; i < BLOCK_W; i++) {
		for (int j = 0; j < BLOCK_H; j++) {
			if (BlocksState[j][i].mBState == FLAG) {
				flag += 1;
			}
		}
	}
}

void Compose::SetLose() {
	for (int i = 0; i < BLOCK_H; i++) {
		for (int j = 0; j < BLOCK_W; j++) {
			if (BlocksState[i][j].mBState == CLOSE) {
				if (BlocksState[i][j].Boom) {
					render.RenderType(6, j * CUBE, i * CUBE + MENU);
				}
				else {
					render.RenderType(0, j * CUBE, i * CUBE + MENU);
				}
			}
			else if (BlocksState[i][j].mBState == FLAG) {
				if (BlocksState[i][j].Boom) {
					render.RenderType(4, j * CUBE, i * CUBE + MENU);
				}
				else {
					render.RenderType(3, j * CUBE, i * CUBE + MENU);
				}
			}
			else if (BlocksState[i][j].mBState == OPEN) {
				if (!BlocksState[i][j].Boom)render.RenderCount(BlocksState[i][j].num, j * CUBE, i * CUBE + MENU);
				if (BlocksState[i][j].Boom)render.RenderType(5, j * CUBE, i * CUBE + MENU);
			}
		}
	}
}
void Compose::SetWin() {
	for (int i = 0; i < BLOCK_H; i++) {
		for (int j = 0; j < BLOCK_W; j++) {
			if (BlocksState[i][j].mBState == CLOSE || BlocksState[i][j].mBState == FLAG) {
				if (BlocksState[i][j].Boom) {
					render.RenderType(4, j * CUBE, i * CUBE + MENU);
				}
			}
			else if (BlocksState[i][j].mBState == OPEN) {
				if (!BlocksState[i][j].Boom)render.RenderCount(BlocksState[i][j].num, j * CUBE, i * CUBE + MENU);
			}
		}
	}
}