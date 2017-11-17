/*#ifndef VIRTUO_BLOCK_H
#define VIRTUO_BLOCK_H

#include "SDL.h"
#include "block.h"

class virtuo_block : public block
{
public:
	virtuo_block();
	virtuo_block(int x, int y);

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