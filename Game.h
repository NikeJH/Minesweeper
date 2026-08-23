#pragma once
#include"Common.h"
#include<vector>
using namespace std;

inline vector < vector < BlockInfo >> BlocksState(BLOCK_H, vector<BlockInfo>(BLOCK_W, BlockInfo{ CLOSE,false,0 }));

MousePos& transformMouse(int x, int y);

void GameInit();
BState GetBState(MousePos mouse);
void FlagBlock(int x, int y);
void FlagBlock(MousePos mouse);
void AskBlock(MousePos mouse);
void CloseBlock(MousePos mouse);
void SetType(int index, MousePos mouse);
void OpenBlock(MousePos mouse);
void PrintMinesGrid();
void Calculate(MousePos mouse);
bool GetFlagsAndEndGame();
void OpenBasic();
void CloseBasic();
void CheckGameState();
void CheckWin();
void RespondState();
void ResetAll();