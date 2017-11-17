#include "options.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "resource.h"

using namespace std;

options::options()
{
	//load image
	back = loadImage("data/OptBack.png");

	//clip for background
	bgclip.x = 0;
	bgclip.y = 0;
	bgclip.w = 520;
	bgclip.h = 640;

	bgrect.x = 0;
	bgrect.y = 0;

	//clips for option select
	option[0].x = 0;
	option[0].y = 641;
	option[0].w = 149;
	option[0].h = 34;

	option[1].x = 150;
	option[1].y = 641;
	option[1].w = 149;
	option[1].h = 34;

	option[2].x = 300;
	option[2].y = 641;
	option[2].w = 149;
	option[2].h = 34;

	option[3].x = 0;
	option[3].y = 676;
	option[3].w = 149;
	option[3].h = 34;

	option[4].x = 150;
	option[4].y = 676;
	option[4].w = 149;
	option[4].h = 34;

	option[5].x = 300;
	option[5].y = 676;
	option[5].w = 149;
	option[5].h = 34;

	option[6].x = 0;
	option[6].y = 711;
	option[6].w = 149;
	option[6].h = 34;

	option[7].x = 150;
	option[7].y = 711;
	option[7].w = 149;
	option[7].h = 34;

	option[8].x = 300;
	option[8].y = 711;
	option[8].w = 149;
	option[8].h = 34;

	option[9].x = 0;
	option[9].y = 746;
	option[9].w = 149;
	option[9].h = 34;

	option[10].x = 150;
	option[10].y = 746;
	option[10].w = 149;
	option[10].h = 34;


	rect[0].x = 32;
	rect[0].y = 166;

	rect[1].x = 185;
	rect[1].y = 166;

	rect[2].x = 338;
	rect[2].y = 166;

	rect[3].x = 32;
	rect[3].y = 275;

	rect[4].x = 185;
	rect[4].y = 275;

	rect[5].x = 338;
	rect[5].y = 275;

	rect[6].x = 32;
	rect[6].y = 384;

	rect[7].x = 185;
	rect[7].y = 384;

	rect[8].x = 338;
	rect[8].y = 384;

	rect[9].x = 32;
	rect[9].y = 461;

	rect[10].x = 304;
	rect[10].y = 579;
}

options::~options()
{
	//clean up
	SDL_FreeSurface(back);
}

int options::show(int &paddleSpeed, int &ballSpeed, int &gameType, int(&bestscore)[41])
{
	if (playIntro == 0)
	{
		Mix_PlayChannel(1, selectBall, 0);
		playIntro = 1;
	}

	if (!Mix_Playing(1) && playIntro == 1)
	{
		Mix_PlayChannel(1, downFoOption, 0);
		playIntro = 2;
	}

	if (!Mix_Playing(1) && playIntro == 2)
	{
		Mix_PlayChannel(1, rightArrow, 0);
		playIntro = 3;
	}
	
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			SDLKey keypressed = event.key.keysym.sym;

			switch (keypressed)
			{
			
				case SDLK_SPACE:
				{
					if (currOpt == 10)
					{
						return 0;
					}

					if (currOpt == 9)
					{
						for (int x = 0; x < 41; x++)
						{
							bestscore[x] = 0;
						}

						std::ofstream file("data/bestscores.txt");
						if (file.is_open())
						{
							for (int count = 0; count < 41; count++)
							{
								file << bestscore[count] << " ";
							}
							
							file.close();
						}
					}
				}
			
				case SDLK_DOWN:
				{
					if (currOpt < 3)
					{
						currOpt = 3;
						Mix_PlayChannel(1, selectPaddle, 0);
					}
				
					else if (currOpt < 6)
					{
						currOpt = 6;
						Mix_PlayChannel(1, selectGame, 0);
					}
				
					else if (currOpt < 9)
					{
						currOpt = 9;
						Mix_PlayChannel(1, resetSpace, 0);
					}

					else if (currOpt == 9)
					{
						currOpt++;
						Mix_PlayChannel(1, returnToMain, 0);
					}

					else if (currOpt == 10)
					{
						currOpt = 0;
						Mix_PlayChannel(-1, selectBall, 0);
					}
					break;
				}

				case SDLK_RIGHT:
				{
					if (currOpt < 3)
					{
						if (currOpt == 0)
						{
							Mix_PlayChannel(1, medium, 0);
						}
						else if (currOpt == 1)
						{
							Mix_PlayChannel(1, high, 0);
						}
						else if (currOpt == 2)
						{
							Mix_PlayChannel(1, low, 0);
						}
						
						currOpt++;
						currOpt = currOpt % 3;
						paddleSpeed = currOpt + 1;
					}
					
					else if (currOpt < 6)
					{
						if (currOpt == 3)
						{
							Mix_PlayChannel(1, medium, 0);
						}
						else if (currOpt == 4)
						{
							Mix_PlayChannel(1, high, 0);
						}
						else if (currOpt == 5)
						{
							Mix_PlayChannel(1, low, 0);
						}

						currOpt++;
						currOpt = currOpt % 3;
						currOpt = currOpt + 3;
						ballSpeed = (currOpt % 3) + 1;
					}

					else if (currOpt < 9)
					{
						if (currOpt == 6)
						{
							Mix_PlayChannel(1, breakout, 0);
						}
						else if (currOpt == 7)
						{
							Mix_PlayChannel(1, virtuoR, 0);
						}
						else if (currOpt == 8)
						{
							Mix_PlayChannel(1, virtuo, 0);
						}
						
						currOpt++;
						currOpt = currOpt % 3;
						currOpt = currOpt + 6;
						gameType = (currOpt % 3) + 1;

						if (gameType != 1)
						{
							score = 0;
						}
					}
				}

				if (event.type == SDL_QUIT)
				{
					return 0; //return STATE_EXIT
				}

				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						return 0; //return STATE_EXIT
					}
				}
			}
		}
	}
	
	//update screen

	SDL_BlitSurface(back, &bgclip, screen, &bgrect);
	SDL_BlitSurface(back, &option[currOpt], screen, &rect[currOpt]);

	SDL_Flip(screen);

	return 3;
}