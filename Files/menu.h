#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>

#include "SDL.h"

class menu
{
public:
	menu();
	~menu();

	int show(int gameType, bool &story);
private:
	SDL_Rect option[5];
	SDL_Rect rect[5];
	SDL_Rect bgclip;
	SDL_Rect bgrect;
	SDL_Event event;
	int currentOpt = 0;
	int playIntro = 0;
	int playInst = 0;
	int playPlay = 0;
	SDL_Surface *back;

};

#endif