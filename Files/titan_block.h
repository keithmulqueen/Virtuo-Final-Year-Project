#ifndef TITAN_BLOCK_H
#define TITAN_BLOCK_H

#include "SDL.h"
#include "block.h"

class titan_block : public block
{
public:
	titan_block();
	titan_block(int x, int y, int gameType);

	void update(int bX, int bY);
	void establish();
};

#endif