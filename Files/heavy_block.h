#ifndef HEAVY_BLOCK_H
#define HEAVY_BLOCK_H

#include "SDL.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

class heavy_block : public block
{
public:
	heavy_block();
	heavy_block(int x, int y, int gameType);

	void update(int bX, int bY);
	void establish();
};

#endif