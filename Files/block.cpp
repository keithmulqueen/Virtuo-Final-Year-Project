#include "SDL.h"
#include "resource.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

block::block()
{
	activated = true;
	inplay = false;
	alive = false;
}

block::block(int x, int y, int gameType)
{
	gameForm = gameType;

	rect.x = x; //block's coordinates
	rect.y = y;
}


void block::update(int bX, int bY)
{

}

void block::draw()
{
	if (alive)
	{
		SDL_BlitSurface(blockSprites, &clip, screen, &rect);
	}
		
}

int block::myX()
{
	if (alive)
		return rect.x;
	else
		return 0;
}

int block::myY()
{
	if (alive)
		return rect.y;
	else
		return 0;
}

bool block::activeNote()
{
	if (activated)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool block::breakoutValid()
{
	if (inplay)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool block::gone()
{
	if (alive)
	{
		return false;
	}
		
	else
	{
		return true;
	}
}

void block::establish()
{
	activated = true;
	inplay = false;
	alive = false;
}

void block::clearBlock()
{
	alive = false;
}