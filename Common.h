#pragma once
#include<SDL3/SDL.h>
#define BLOCK_H 15
#define BLOCK_W 11
#define CUBE 40
#define MENU 40
#define WIDTH (BLOCK_W*CUBE)
#define HEIGHT (BLOCK_H*CUBE+MENU)
#define Mines 14

inline bool running;
inline bool isEnding = false;
inline int flag = 0;

enum State { READY, RUN, WIN, LOSE };
enum BState { CLOSE, OPEN, FLAG, ASK };

using namespace std;

struct BlockInfo {
	BState mBState = CLOSE;
	bool Boom = false;
	int num = 0;
};
inline State GameState;
inline bool isPass;
inline bool Timer;
inline int FaceIndex = 2;
inline int timeS = 0;
inline bool resetTime = false;
struct MousePos {
	int x;
	int y;
};
