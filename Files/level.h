#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include "SDL.h"
#include "paddle.h"
#include "ball.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

class level
{
public:
	level(int levelArray[14][14], int gameType, int ballSpeed);
	
	void update(SDL_Event event);
	void draw(int paddleSpeed, int ballSpeed, int gameType);
	bool levelComplete(int gameType);
	bool dead(int ballSpeed);
	void reset(int ballSpeed);
	void clearScreen();

private:
	paddle paddle1;
	ball ball1;
	std::vector<block*> blocks;
	SDL_Rect bgClip;
	SDL_Rect bgRect;
	int backCol;
};

#endif
