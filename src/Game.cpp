#include"Game.h"

using namespace std;

void GameInit() {
	// Plant Mines
	int j, i;
	GameState = READY;
	Timer = false;
	isPass = false;
	resetTime = true;
	timeS = 0;
	for (int t = 0; t < Mines; t++) {
	SetBoom:
		j = SDL_rand(BLOCK_H);
		i = SDL_rand(BLOCK_W);
		if (BlocksState[j][i].Boom == true) {
			goto SetBoom;
		}
		else {
			BlocksState[j][i].Boom = true;
		}
	}
}
BState GetBState(MousePos mouse) {
	return BlocksState[mouse.y][mouse.x].mBState;
}
void FlagBlock(int x, int y) {
	if (y != -1 && BlocksState[y][x].mBState == CLOSE) {
		BlocksState[y][x].mBState = FLAG;
	}
}
void FlagBlock(MousePos mouse) {
	if (mouse.y != -1 && BlocksState[mouse.y][mouse.x].mBState == CLOSE) {
		BlocksState[mouse.y][mouse.x].mBState = FLAG;
	}
}
void AskBlock(MousePos mouse) {
	if (mouse.y != -1 && BlocksState[mouse.y][mouse.x].mBState == FLAG) {
		BlocksState[mouse.y][mouse.x].mBState = ASK;
	}
}
void CloseBlock(MousePos mouse) {
	if (mouse.y != -1 && BlocksState[mouse.y][mouse.x].mBState == ASK) {
		BlocksState[mouse.y][mouse.x].mBState = CLOSE;
	}
}
void SetType(int index, MousePos mouse) {
	if (index == 0) {
		CloseBlock(mouse);
	}
	else if (index == 1) {
		FlagBlock(mouse);
	}
	else if (index == 2) {
		AskBlock(mouse);
	}
	else {
		CloseBlock(mouse);
	}
}
void OpenBlock(MousePos mouse) {
	if (mouse.y != -1 && BlocksState[mouse.y][mouse.x].mBState == CLOSE) {
		Calculate(mouse);
		// BlocksState[mouse.y][mouse.x].mBState = OPEN;
	}
}
MousePos& transformMouse(int _x, int _y) {
	MousePos block{};
	block.x = _x / CUBE;

	if (_y - MENU > 0) {
		block.y = (_y - MENU) / CUBE;
	}
	else {
		block.y = -1;
	}

	return block;
}

void OpenBasic() {
	for (int i = 0; i < BlocksState.size(); i++) {
		for (int j = 0; j < BlocksState[0].size(); j++) {
			BlocksState[i][j].mBState = OPEN;
		}
	}
}
void CloseBasic() {
	for (int i = 0; i < BlocksState.size(); i++) {
		for (int j = 0; j < BlocksState[0].size(); j++) {
			BlocksState[i][j].mBState = CLOSE;
		}
	}
}

void Calculate(MousePos mouse) {
	if (BlocksState[mouse.y][mouse.x].Boom) {
		GameState = LOSE;
		BlocksState[mouse.y][mouse.x].mBState = OPEN;
		return;
	}
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (mouse.x + i >= 0 && mouse.x + i <= BLOCK_W - 1 && mouse.y + j >= 0 && mouse.y + j <= BLOCK_H - 1 && !(i == 0 && j == 0)) {
				if (BlocksState[mouse.y + j][mouse.x + i].Boom) {
					BlocksState[mouse.y][mouse.x].num += 1;
				}
			}
		}
	}
	BlocksState[mouse.y][mouse.x].mBState = OPEN;
	if (BlocksState[mouse.y][mouse.x].num == 0) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (mouse.x + i >= 0 && mouse.x + i <= BLOCK_W - 1 && mouse.y + j >= 0 && mouse.y + j <= BLOCK_H - 1 && !(i == 0 && j == 0)) {
					if (BlocksState[mouse.y + j][mouse.x + i].mBState == CLOSE) {
						Calculate(MousePos{ mouse.x + i,mouse.y + j });
					}
				}
			}
		}
		return;
	}
}
bool GetFlagsAndEndGame() {
	static int oldFlag = 0;

	if (flag != oldFlag) {
		oldFlag = flag;
	}
	if (flag == Mines) {
		{
			int i = 0;
			if (i == 0) {
				i++;
			}
		}
		for (int i = 0; i < BLOCK_H; i++) {
			for (int j = 0; j < BLOCK_W; j++) {
				if (BlocksState[i][j].Boom) {
					if (BlocksState[i][j].mBState != FLAG) {
						isPass = false;
						goto OutJudgement;
					}
					else {
						isPass = true;
					}
				}
			}
		}
	OutJudgement:
		;;
	}

	return isPass;
}
void CheckGameState() {
	if (GameState == RUN) {
		{
			static int i = 1;
			if (i == 1) {
				i = 0;
			}
		}
		CheckWin();
	}
}
void CheckWin() {
	static bool change = true;
	for (int i = 0; i < BLOCK_H; i++) {
		for (int j = 0; j < BLOCK_W; j++) {
			if (BlocksState[i][j].mBState == CLOSE) {
				if (!BlocksState[i][j].Boom) {
					change = false;
					goto StillRunning;
				}
				else {
					change = true;
				}
			}
		}
	}
StillRunning:
	if (change) {
		GameState = WIN;
	}
}
void ResetAll() {
	for (int i = 0; i < BLOCK_H; i++) {
		for (int j = 0; j < BLOCK_W; j++) {
			BlocksState[i][j].mBState = CLOSE;
			BlocksState[i][j].num = 0;
			BlocksState[i][j].Boom = false;
		}
	}
	GameInit();
}

//void CheckAllFlag() {
//	int oldFlag = 
//	if (flag == 10) {
//		SDL_Log("Detect All flags has been plug in");
//	}
//}