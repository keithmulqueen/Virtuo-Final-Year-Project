#include "menu.h"
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "resource.h"

menu::menu()
{ 
	back = loadImage("data/menuBack.png");

	bgclip.x = 0;
	bgclip.y = 0;
	bgclip.w = 520;
	bgclip.h = 640;

	bgrect.x = 0;
	bgrect.y = 0;

	option[0].x = 521;
	option[0].y = 0;
	option[0].w = 387;
	option[0].h = 68;

	option[1].x = 521;
	option[1].y = 77;
	option[1].w = 387;
	option[1].h = 68;

	option[2].x = 521;
	option[2].y = 154;
	option[2].w = 387;
	option[2].h = 68;

	option[3].x = 521;
	option[3].y = 231;
	option[3].w = 387;
	option[3].h = 68;

	option[4].x = 521;
	option[4].y = 308;
	option[4].w = 387;
	option[4].h = 68;

	rect[0].x = 0;
	rect[0].y = 233;

	rect[1].x = 0;
	rect[1].y = 310;

	rect[2].x = 0;
	rect[2].y = 387;

	rect[3].x = 0;
	rect[3].y = 464;

	rect[4].x = 0;
	rect[4].y = 541;

}

menu::~menu()
{
	SDL_FreeSurface(back);
}

int menu::show(int gameType, bool &story)
{
	story = true;

	if (playIntro == 0)
	{
		Mix_PlayChannel(1, welcome, 0);
		playIntro = 1;
	}
	
	if (!Mix_Playing(1) && playIntro == 1)
	{
		Mix_PlayChannel(1, downFoOption, 0);	
		playIntro = 2;
	}

	if (!Mix_Playing(1) && playIntro == 2)
	{
		Mix_PlayChannel(1, spaceForEnter, 0);
		playIntro = 3;
	}

	if ((currentOpt == 0) && (!Mix_Playing(1)))
	{
		if (playPlay == 1)
		{
			Mix_PlayChannel(1, currentRuleIs, 0);
			playPlay = 2;
		}

		else if (playPlay == 2)
		{
			if (gameType == 1)
			{
				Mix_PlayChannel(1, virtuo, 0);
				playPlay = 0;
			}
			else if (gameType == 2)
			{
				Mix_PlayChannel(1, breakout, 0);
				playPlay = 0;
			}
			else
			{
				Mix_PlayChannel(1, virtuoR, 0);
				playPlay = 0;
			}
		}
	}

	if ((currentOpt == 3) && (!Mix_Playing(1)))
	{
		if ((playInst == 1) && (gameType == 2))
		{
			Mix_PlayChannel(1, advance2, 0);
			
			playInst = 2;
		}

		else if ((playInst == 1) && ((gameType == 1) || (gameType == 3)))
		{
			Mix_PlayChannel(1, advance13, 0);
			
			playInst = 2;
		}

		if ((playInst == 2) && (gameType == 1))
		{
			Mix_PlayChannel(1, HSvirtuo, 0);
			
			playInst = 0;
		}

		else if ((playInst == 2) && (gameType == 2))
		{
			Mix_PlayChannel(1, HSvirtuoR, 0);

			playInst = 0;
		}


	}

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			SDLKey keypressed = event.key.keysym.sym;

			switch (keypressed)
			{
				case SDLK_SPACE:
				{
					if (currentOpt == 4)
					{
						Mix_PlayChannel(-1, instructions, 0);

						if (gameType == 1 || gameType == 3)
						{
							Mix_PlayChannel(-1, advance13, 0);
						}
						else
						{
							Mix_PlayChannel(-1, advance2, 0);
						}
					}
					
					else if (currentOpt == 5)
					{
						Mix_PlayChannel(-1, credits, 0);
					}

					return (currentOpt + 1);
				}

				case SDLK_DOWN:
				{
					if (currentOpt == 0)
					{
						currentOpt = 1;
						Mix_PlayChannel(1, levelselect, 0);
					}
					else if (currentOpt == 1)
					{
						currentOpt = 2;
						Mix_PlayChannel(1, optionsMenu, 0);
					}
					else if (currentOpt == 2)
					{
						currentOpt = 3;
						playInst = 1;
						Mix_PlayChannel(1, instructions, 0);
					}
					else if (currentOpt == 3)
					{
						currentOpt = 4;
						Mix_PlayChannel(1, credits, 0);
					}
					else if (currentOpt == 4)
					{
						currentOpt = 0;
						playPlay = 1;
						Mix_PlayChannel(1, playgame, 0);
					}
				}
			}
		}
		
		if (event.type == SDL_QUIT)
		{
			return 6;
		}

		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return 6;
			}
		}
	}

	SDL_BlitSurface(back, &bgclip, screen, &bgrect);
	SDL_BlitSurface(back, &option[currentOpt], screen, &rect[currentOpt]);

	SDL_Flip(screen);

	return 0;
}

