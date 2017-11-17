#ifndef BLOCK_H
#define BLOCK_H

#include "SDL.h"

class block
{
public:
	block();
	block(int x, int y, int gameType);

	virtual void update(int bX, int bY);
	void draw();
	int myX();
	int myY();
	bool activeNote();
	bool breakoutValid();
	bool gone();
	virtual void establish();
	void clearBlock();

protected:
	int gameForm;
	bool activated;
	bool inplay;
	bool damaged = false;
	bool colDet = false;
	bool alive;
	SDL_Rect rect;
	SDL_Rect clip;

};

#endif