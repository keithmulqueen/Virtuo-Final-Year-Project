#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <iostream>

#include "SDL.h"

class options
{
public:
	options();
	~options();

	int show(int &paddleSpeed, int &ballSpeed, int &gameType, int (&bestscore)[41]);

private:
	SDL_Rect option[11];
	SDL_Rect rect[11];
	SDL_Rect bgclip;
	SDL_Rect bgrect;
	SDL_Event event;
	int currOpt;
	int playIntro;
	SDL_Surface *back;
};

#endif