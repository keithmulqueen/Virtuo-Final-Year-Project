#include <sstream>
#include <fstream>
#include <string>

#include "level_select.h"
#include "game.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "resource.h"
using namespace std;

level_select::level_select()
{
	//load image
	back = loadImage("data/LvlBack.png");

	//clip for background
	bgclip.x = 0;
	bgclip.y = 0;
	bgclip.w = 520;
	bgclip.h = 640;

	bgrect.x = 0;
	bgrect.y = 0;

	//clips for play select
	levelclip[0].x = 0;
	levelclip[0].y = 641;
	levelclip[0].w = 64;
	levelclip[0].h = 33;

	levelclip[1].x = 65;
	levelclip[1].y = 641;
	levelclip[1].w = 64;
	levelclip[1].h = 33;

	//create array for urect possitions [73(+96)x382(+50)]
	levelrect[0].x = 73;
	levelrect[0].y = 296;

	levelrect[1].x = 73;
	levelrect[1].y = 346;

	levelrect[2].x = 73;
	levelrect[2].y = 396;

	levelrect[3].x = 73;
	levelrect[3].y = 446;

	levelrect[4].x = 175;
	levelrect[4].y = 296;

	levelrect[5].x = 175;
	levelrect[5].y = 346;

	levelrect[6].x = 175;
	levelrect[6].y = 396;

	levelrect[7].x = 175;
	levelrect[7].y = 446;

	levelrect[8].x = 276;
	levelrect[8].y = 296;

	levelrect[9].x = 276;
	levelrect[9].y = 346;

	levelrect[10].x = 276;
	levelrect[10].y = 396;

	levelrect[11].x = 276;
	levelrect[11].y = 446;

	levelrect[12].x = 379;
	levelrect[12].y = 296;

	levelrect[13].x = 379;
	levelrect[13].y = 346;

	levelrect[14].x = 379;
	levelrect[14].y = 396;

	levelrect[15].x = 379;
	levelrect[15].y = 446;

	levelrect[16].x = 379;
	levelrect[16].y = 496;

	levelrect[17].x = 276;
	levelrect[17].y = 496;

	levelrect[18].x = 175;
	levelrect[18].y = 496;

	levelrect[19].x = 73;
	levelrect[19].y = 496;

	levelrect[20].x = 361;
	levelrect[20].y = 581;
}

level_select::~level_select()
{
	//clean up
	SDL_FreeSurface(back);
}

int level_select::show(int &begin_lvl, bool &storymode, int bestscore[41])
{
	//storymode = false;
	
	if (playIntro == 0)
	{
		Mix_PlayChannel(1, downFoOption, 0);
		playIntro = 1;
	}

	if (!Mix_Playing(1) && playIntro == 1)
	{
		Mix_PlayChannel(1, spaceForEnter, 0);
		playIntro = 2;
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
					if (currOpt == 20)
					{
						playIntro = 0;
						return 0;
					}
				
					else
					{
						begin_lvl = currOpt;
						storymode = false;
						playIntro = 0;

						return 1;
					}


				}

				case SDLK_DOWN:
				{
					if (currOpt == 19)
					{
						currOpt++;
						Mix_PlayChannel(1, returnToMain, 0);
					}
					else if (currOpt == 20)
					{
						currOpt = 0;
					}
					else
					{
						currOpt = currOpt++;
					}

					if (currOpt != 20)
					{
						levclip = 0;
					}
					else
					{
						levclip = 1;
					}

					playLevel = 0;
				}
			}
		}

		if (event.type == SDL_QUIT)
		{
			return 0;
		}

		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return 0;
			}
		}
	}


	//update screen
	SDL_BlitSurface(back, &bgclip, screen, &bgrect);
	
	//update these inside of an array
	SDL_BlitSurface(back, &levelclip[levclip], screen, &levelrect[currOpt]);

	std::stringstream out;
	std::string levelOut;
	out << (currOpt + 1);
	levelOut = out.str();

	std::stringstream out2;
	std::string virtuoOut;
	out2 << bestscore[currOpt];
	virtuoOut = out2.str();

	std::stringstream out3;
	std::string virtuoXOut;
	out3 << bestscore[currOpt+20];
	virtuoXOut = out3.str();

	std::stringstream out4;
	std::string breakoutOut;
	out4 << bestscore[40];
	breakoutOut = out4.str();

	if (currOpt != 20)
	{
		font = TTF_OpenFont("data/forte.ttf", 36);
		printText(140, 118, levelOut, 255, 255, 0);

		font = TTF_OpenFont("data/forte.ttf", 20);
		printText(260, 178, virtuoOut, 255, 255, 255);
		printText(260, 212, breakoutOut, 255, 255, 255);
		printText(260, 246, virtuoXOut, 255, 255, 255);
	}

	if (!Mix_Playing(1) && (playLevel == 0) && (currOpt!=20) && (playIntro == 2))
	{
		Mix_PlayChannel(1, levelNum, 0);
		playLevel = 1;
	}

	if (!Mix_Playing(1) && playLevel == 1)
	{
		if (currOpt == 0)
		{
			Mix_PlayChannel(1, one, 0);
			playLevel = 2;
		}
		else if (currOpt == 1)
		{
			Mix_PlayChannel(1, two, 0);
			playLevel = 2;
		}
		else if (currOpt == 2)
		{
			Mix_PlayChannel(1, three, 0);
			playLevel = 2;
		}
		else if (currOpt == 3)
		{
			Mix_PlayChannel(1, four, 0);
			playLevel = 2;
		}
		else if (currOpt == 4)
		{
			Mix_PlayChannel(1, five, 0);
			playLevel = 2;
		}
		else if (currOpt == 5)
		{
			Mix_PlayChannel(1, six, 0);
			playLevel = 2;
		}
		else if (currOpt == 6)
		{
			Mix_PlayChannel(1, seven, 0); 
			playLevel = 2;
		}
		else if (currOpt == 7)
		{
			Mix_PlayChannel(1, eight, 0); 
			playLevel = 2;
		}
		else if (currOpt == 8)
		{
			Mix_PlayChannel(1, nine, 0); 
			playLevel = 2;
		}
		else if (currOpt == 9)
		{
			Mix_PlayChannel(1, ten, 0); 
			playLevel = 2;
		}
		else if (currOpt == 10)
		{
			Mix_PlayChannel(1, eleven, 0); 
			playLevel = 2;
		}
		else if (currOpt == 11)
		{
			Mix_PlayChannel(1, twelve, 0); 
			playLevel = 2;
		}
		else if (currOpt == 12)
		{
			Mix_PlayChannel(1, thirteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 13)
		{
			Mix_PlayChannel(1, fourteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 14)
		{
			Mix_PlayChannel(1, fifteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 15)
		{
			Mix_PlayChannel(1, sixteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 16)
		{
			Mix_PlayChannel(1, seventeen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 17)
		{
			Mix_PlayChannel(1, eighteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 18)
		{
			Mix_PlayChannel(1, ninteen, 0); 
			playLevel = 2;
		}
		else if (currOpt == 19)
		{
			Mix_PlayChannel(1, twenty, 0); 
			playLevel = 2;
		}

	}

	if (!Mix_Playing(1) && playLevel == 2)
	{
		if ((bestscore[currOpt]) != 0)
		{
			Mix_PlayChannel(1, VHSis, 0);
			playLevel = 3;
		}
		else
		{
			playLevel = 4;
		}

	}

	if (!Mix_Playing(1) && playLevel == 3)
	{
		if (bestscore[currOpt] == 1)
		{
			Mix_PlayChannel(1, one, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 2)
		{
			Mix_PlayChannel(1, two, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 3)
		{
			Mix_PlayChannel(1, three, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 4)
		{
			Mix_PlayChannel(1, four, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 5)
		{
			Mix_PlayChannel(1, five, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 6)
		{
			Mix_PlayChannel(1, six, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 7)
		{
			Mix_PlayChannel(1, seven, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 8)
		{
			Mix_PlayChannel(1, eight, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 9)
		{
			Mix_PlayChannel(1, nine, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 10)
		{
			Mix_PlayChannel(1, ten, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 11)
		{
			Mix_PlayChannel(1, eleven, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 12)
		{
			Mix_PlayChannel(1, twelve, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 13)
		{
			Mix_PlayChannel(1, thirteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 14)
		{
			Mix_PlayChannel(1, fourteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 15)
		{
			Mix_PlayChannel(1, fifteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 16)
		{
			Mix_PlayChannel(1, sixteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 17)
		{
			Mix_PlayChannel(1, seventeen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 18)
		{
			Mix_PlayChannel(1, eighteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 19)
		{
			Mix_PlayChannel(1, ninteen, 0); playLevel = 4;
		}
		else if (bestscore[currOpt] == 20)
		{
			Mix_PlayChannel(1, twenty, 0);
			playLevel = 4;
		}
	}

	if (!Mix_Playing(1) && (playLevel == 4))
	{
		if ((bestscore[currOpt + 20]) != 0)
		{
			Mix_PlayChannel(1, VRHSis, 0);
			playLevel = 5;
		}
		else
		{
			playLevel = 6;
		}
	}

	if (!Mix_Playing(1) && (playLevel == 5))
	{
		if (bestscore[currOpt + 20] == 1)
		{
			Mix_PlayChannel(1, one, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 2)
		{
			Mix_PlayChannel(1, two, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 3)
		{
			Mix_PlayChannel(1, three, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 4)
		{
			Mix_PlayChannel(1, four, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 5)
		{
			Mix_PlayChannel(1, five, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 6)
		{
			Mix_PlayChannel(1, six, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 7)
		{
			Mix_PlayChannel(1, seven, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 8)
		{
			Mix_PlayChannel(1, eight, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 9)
		{
			Mix_PlayChannel(1, nine, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 10)
		{
			Mix_PlayChannel(1, ten, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 11)
		{
			Mix_PlayChannel(1, eleven, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 12)
		{
			Mix_PlayChannel(1, twelve, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 13)
		{
			Mix_PlayChannel(1, thirteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 14)
		{
			Mix_PlayChannel(1, fourteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 15)
		{
			Mix_PlayChannel(1, fifteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 16)
		{
			Mix_PlayChannel(1, sixteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 17)
		{
			Mix_PlayChannel(1, seventeen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 18)
		{
			Mix_PlayChannel(1, eighteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 19)
		{
			Mix_PlayChannel(1, ninteen, 0); playLevel = 6;
		}
		else if (bestscore[currOpt + 20] == 20)
		{
			Mix_PlayChannel(1, twenty, 0); playLevel = 6;
		}

		playLevel = 6;

	}

	SDL_Flip(screen);

	return 2;
}
