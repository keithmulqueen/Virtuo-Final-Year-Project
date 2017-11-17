#include "SDL.h"
#include "resource.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"
using namespace std;

standard_block::standard_block()
{
	alive = false;
	inplay = false;
	activated = true;
	
}

standard_block::standard_block(int x, int y, int gameType)
{
	gameForm = gameType;

	alive = true;
	inplay = true;
	activated = true;
	
	clip.x = 74;
	clip.y = 0;
	clip.w = 36;
	clip.h = 20;

	rect.x = x; //block's coordinates
	rect.y = y;

}

void standard_block::update(int bX, int bY)
{
	if (alive)
	{
		if (((bX + 7 >= rect.x) && (bX <= rect.x + 36)) && ((bY + 7 >= rect.y) && (bY <= rect.y + 20))) //ball collision
		{
			if (gameForm == 2)
			{
				score++;
			}
			
			alive = false;
			inplay = false;
		}
	}
}

void standard_block::establish()
{
	alive = true;
	inplay = true;
	activated = true;
}

