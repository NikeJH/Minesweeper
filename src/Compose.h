#pragma once
#include"Common.h"

class Compose {
private:
	Source render;
	uint64_t timeStart = 0;
	uint64_t now = 0;
	uint64_t delayMs = 1000;
public:
	Compose(Source& _r);
	void AddCounter(int score);
	void AddTimer(bool time);
	void AddFace(int index);
	void SetMenu(int left, int index, bool isBegin);
	void SetMain();
	void Refresh();

	void SetLose();
	void SetWin();
};