#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include <string>
#include <iostream>

#include "SDL.h"

class level_select
{
public:
	level_select();
	~level_select();

	int show(int &begin_lvl, bool &storymode, int bestscore[41]);
private:
	
	SDL_Rect levelclip[2];
	SDL_Rect levelrect[21];
	SDL_Rect bgclip;
	SDL_Rect bgrect;
	SDL_Event event;
	int currOpt;
	int levclip;
	int returned;
	int playIntro = 0;
	int playLevel = 0;
	SDL_Surface *back;
};

#endif