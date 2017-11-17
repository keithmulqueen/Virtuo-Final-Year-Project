/*#ifndef TITAN_BLOCK_H
#define TITAN_BLOCK_H

#include "SDL.h"
#include "block.h"

class titan_block : public block
{
public:
	titan_block();
	titan_block(int x, int y);

	void update(int bX, int bY);
	void draw();
	int myX();
	int myY();
	bool gone();
	void makeAlive();
private:
	bool alive;
	SDL_Rect rect;
	SDL_Rect clip;
};

#endif
*/