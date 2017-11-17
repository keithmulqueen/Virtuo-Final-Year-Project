#include "SDL.h"
#include "resource.h"
#include "heavy_block.h"
#include "block.h"

heavy_block::heavy_block()
{
	alive = false;
	inplay = false;
	activated = true;
}

heavy_block::heavy_block(int x, int y, int gameType)
{
	gameForm = gameType;
	
	alive = true;
	activated = true;
	inplay = true;

	clip.x = 111;
	clip.y = 0;
	clip.w = 36;
	clip.h = 20;

	rect.x = x; //block's coordinates
	rect.y = y;

}

void heavy_block::update(int bX, int bY)
{
	if (alive)
	{		
		if (((bX + 7 >= rect.x) && (bX <= rect.x + 36)) && ((bY + 7 >= rect.y) && (bY <= rect.y + 20))) //ball collision
		{
			if (!damaged)
			{
				damaged = true;

				//sprite change
				clip.x = 148;
				clip.y = 21;
				clip.w = 36;
				clip.h = 20;
			}

			else if (damaged)
			{
				
				if (gameForm == 2)
				{
					score = score + 2;
				}

				inplay = false;
				alive = false;

			}
		}
	}
}

void heavy_block::establish()
{
	alive = true;
	activated = true;
	inplay = true;
}

