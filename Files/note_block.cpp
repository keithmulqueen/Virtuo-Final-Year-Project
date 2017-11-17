#include "SDL.h"
#include "resource.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

note_block::note_block()
{
	alive = false;
	activated = true;
	inplay = false;
}

note_block::note_block(int x, int y, int gameType, int note)
{
	gameForm = gameType;
	activated = false;
	inplay = false;
	alive = true;
	
	myNote = note;

	if (myNote == 0)// myNote A
	{
		clip.x = 0;
		clip.y = 21;
		clip.w = 36;
		clip.h = 20;

	}

	else if (myNote == 1)// myNote B
	{
		clip.x = 0;
		clip.y = 42;
		clip.w = 36;
		clip.h = 20;

	}
	
	else if (myNote == 2)// myNote C
	{
		clip.x = 0;
		clip.y = 63;
		clip.w = 36;
		clip.h = 20;

	}

	else if (myNote == 3)// myNote D
	{
		clip.x = 0;
		clip.y = 84;
		clip.w = 36;
		clip.h = 20;

	}

	else if (myNote == 4)// myNote E
	{
		clip.x = 0;
		clip.y = 105;
		clip.w = 36;
		clip.h = 20;

	}

	else if (myNote == 5)// myNote F
	{
		clip.x = 0;
		clip.y = 126;
		clip.w = 36;
		clip.h = 20;

	}

	else if (myNote == 6)// myNote G
	{
		clip.x = 0;
		clip.y = 147;
		clip.w = 36;
		clip.h = 20;

	}

	rect.x = x; //block's coordinates
	rect.y = y;

}

void note_block::update(int bX, int bY)
{
	if (alive)
	{
		if (((bX + 7 >= rect.x) && (bX <= rect.x + 36)) && ((bY + 7 >= rect.y) && (bY <= rect.y + 20))) //ball collision
		{
			if (damaged == false)
			{
				damaged = true;
				activated = true;

				if (gameForm == 2)
				{
					score = score + 5;
				}

				if (myNote == 0)// note A
				{
					clip.x = 37;
					clip.y = 21;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockA, 0);
				}

				else if (myNote == 1)// note B
				{
					clip.x = 37;
					clip.y = 42;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockB, 0);
				}

				else if (myNote == 2)// myNote C
				{
					clip.x = 37;
					clip.y = 63;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockC, 0);
				}

				else if (myNote == 3)// myNote D
				{
					clip.x = 37;
					clip.y = 84;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockD, 0);
				}

				else if (myNote == 4)// myNote E
				{
					clip.x = 37;
					clip.y = 105;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockE, 0);
				}

				else if (myNote == 5)// myNote F
				{
					clip.x = 37;
					clip.y = 126;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockF, 0);
				}

				else if (myNote == 6)// myNote G
				{
					clip.x = 37;
					clip.y = 147;
					clip.w = 36;
					clip.h = 20;

					Mix_PlayChannel(-1, noteBlockG, 0);
				}
			}
		}
	}
}

void note_block::establish()
{
	activated = false;
	inplay = false;
	alive = true;
}

