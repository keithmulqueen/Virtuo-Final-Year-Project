#ifndef VIRTUO_BLOCK_H
#define VIRTUO_BLOCK_H

#include "SDL.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

class virtuo_block : public block
{
public:
	virtuo_block();
	virtuo_block(int x, int y, int gameType);

	void update(int bX, int bY);
	void establish();

};

#endif