#ifndef STANDARD_BLOCK_H
#define STANDARD_BLOCK_H

#include "SDL.h"
#include "block.h"

class standard_block : public block
{
public:
	standard_block();
	standard_block(int x, int y, int gameType);

	void update(int bX, int bY);
	void establish();
};

#endif