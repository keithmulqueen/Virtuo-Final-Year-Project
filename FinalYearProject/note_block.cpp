/*#include "SDL.h"
#include "resource.h"
#include "note_block.h"
#include "block.h"

note_block::note_block()
{
	alive = false;
}

note_block::note_block(int x, int y)
{

	clip.x = 0;
	clip.y = 0;
	clip.w = 36;
	clip.h = 20;

	rect.x = x; //block's coordinates
	rect.y = y;

}

void block::update(int bX, int bY)
{
	if (alive)
	{
		if (bX + 12 > rect.x && bX < rect.x + 60 && bY + 12 > rect.y && bY < rect.y + 29) //ball collision
		{
			alive = false;
			score += 10;
		}
	}
}
*/