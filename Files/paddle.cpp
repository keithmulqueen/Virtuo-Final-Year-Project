#include "SDL.h"
#include "resource.h"
#include "options.h"
#include "paddle.h"

paddle::paddle()
{
	clip.w = 83;
	clip.h = 10;
	
	rect.x = 256; //paddle's coordinates
	rect.y = 610;
}

void paddle::update(int paddleSpeed)
{

	Uint8 *keystates = SDL_GetKeyState(NULL);

	
	if (keystates[SDLK_LEFT])
	{
		if (rect.x > 81)
		{
			rect.x -= (paddleSpeed + 2);
		}
		else
		{
			Mix_PlayChannel(1, dockL, 0);
		}
	}


	if (keystates[SDLK_RIGHT])
	{
		if (rect.x + 83 <= 438)
		{
			rect.x += (paddleSpeed + 2);
		}
		
		else
		{
			Mix_PlayChannel(1, dockR, 0);
		}
	}


	if (!Mix_Playing(2))
	{
		if (rect.x + 41 <= 132)
		{
			Mix_PlayChannel(-1, paddleLockA, 0);
		}
		else if (rect.x + 41 <= 183)
		{
			Mix_PlayChannel(-1, paddleLockB, 0);
		}
		else if (rect.x + 41 <= 234)
		{
			Mix_PlayChannel(-1, paddleLockC, 0);
		}
		else if (rect.x + 41 <= 285)
		{
			Mix_PlayChannel(-1, paddleLockD, 0);
		}
		else if (rect.x + 41 <= 336)
		{
			Mix_PlayChannel(-1, paddleLockE, 0);
		}
		else if (rect.x + 41 <= 387)
		{
			Mix_PlayChannel(-1, paddleLockF, 0);
		}
		else
		{
			Mix_PlayChannel(-1, paddleLockG, 0);
		}
	}

}

void paddle::draw(int gameType)
{
	if (gameType == 2)
	{
		clip.x = 74;
		clip.y = 146;
	}
	else if (gameType == 3)
	{
		clip.x = 74;
		clip.y = 136;
	}
	else
	{
		clip.x = 74;
		clip.y = 156;
	}

	SDL_BlitSurface(blockSprites, &clip, screen, &rect);
}

int paddle::myX()
{
	return rect.x;
}
