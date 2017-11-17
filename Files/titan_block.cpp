#include "SDL.h"
#include "resource.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

titan_block::titan_block()
{
	alive = false;
	inplay = false;
	activated = true;
}

titan_block::titan_block(int x, int y, int gameType)
{
	alive = true;
	inplay = false;
	activated = true;

	clip.x = 148;
	clip.y = 0;
	clip.w = 36;
	clip.h = 20;

	rect.x = x; //block's coordinates
	rect.y = y;

}

void titan_block::update(int bX, int bY)
{
	if (alive)
	{
		if (((bX + 7 >= rect.x) && (bX <= rect.x + 36)) && ((bY + 7 >= rect.y) && (bY <= rect.y + 20))) //ball collision
		{
			//play music
		}
	}
}

void titan_block::establish()
{
	alive = true;
	inplay = false;
	activated = true;
}
