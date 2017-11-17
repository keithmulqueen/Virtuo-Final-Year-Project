#include "SDL.h"
#include "resource.h"
#include "virtuo_block.h"
#include "block.h"
using namespace std;

virtuo_block::virtuo_block()
{
	alive = false;
}

virtuo_block::virtuo_block(int x, int y, int gameType)
{
	gameForm = gameType;
	
	alive = true;
	inplay = true;
	activated = true;

	if (gameForm == 1) 
	{
		clip.x = 0;
		clip.y = 0;
		clip.w = 36;
		clip.h = 20;
	}
	else if (gameForm == 2)
	{
		clip.x = 148;
		clip.y = 84;
		clip.w = 36;
		clip.h = 20;
	}
	else
	{
		clip.x = 148;
		clip.y = 42;
		clip.w = 36;
		clip.h = 20;
	}

	rect.x = x; //block's coordinates
	rect.y = y;
}

void virtuo_block::update(int bX, int bY)
{
	if (alive)
	{
		if(((bX + 7 >= rect.x) && (bX <= rect.x + 36)) && ((bY + 7 >= rect.y) && (bY <= rect.y + 20))) //ball collision
		{
			if (!damaged)
			{
				damaged = true;

				//sprite change
				if (gameForm == 1)
				{
					clip.x = 37;
					clip.y = 0;
					clip.w = 36;
					clip.h = 20;
				}

				else if (gameForm == 2)
				{
					alive = false;
					inplay = false;
					score = score + 3;
				}
				else
				{
					Mix_PlayChannel(-1, vBlock2, 0);
					alive = false;
					inplay = false;
					score++;
				}

			}

			else if ((damaged) && (gameForm == 1))
			{
				Mix_PlayChannel(-1, vBlock1, 0);
				alive = false;
				inplay = false;
				score--;
			}	
		}
	}
}

void virtuo_block::establish()
{
	alive = true;
	inplay = true;
	activated = true;
}
