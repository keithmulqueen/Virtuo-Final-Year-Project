#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "SDL_mixer.h"
#include "resource.h"
#include "math.h"

#include "ball.h"

ball::ball()
{
	clip.x = 115; //clip for the ball sprite in tiles.png
	clip.y = 105;
	clip.w = 7;
	clip.h = 7;

	rect.x = 290; //ball's coordinates
	rect.y = 430;

	xVel = rand() % 8 - 4; //random beginning velocity between -4 and 4

	if (xVel == 0) //don't want the ball going straight up to start
		xVel = 1;

	moving = false;
	moved = false;

	yVel = -1;
}

ball::ball(int ballSpeed)
{
	clip.x = 48; //clip for the ball sprite in tiles.png
	clip.y = 37;
	clip.w = 7;
	clip.h = 7;

	rect.x = 290; //ball's coordinates
	rect.y = 430;

	xVel = rand()%8-4; //random beginning velocity between -4 and 4
	
	if (xVel == 0) //don't want the ball going straight up to start
		xVel = 1;

	moving = false;
	moved = false;

	yVel = (ballSpeed)*(-1);
}

void ball::update(int pX, int bX, int bY)
{	
	if (moving)
	{
		if (!moved)
		{
			rect.x += xVel;
			rect.y += yVel;

			moved = true;

			//Wall Collisions
			if (rect.y <= 35)
			{
				Mix_PlayChannel(-1, wall1, 0);
				yVel = (yVel)*(-1);
			}

			if (rect.x <= 5)
			{
				Mix_PlayChannel(-1, wall2, 0);
				xVel = (xVel)*(-1);
				rect.x = 6;
			}

			else if (rect.x + 7 >= 515)
			{
				Mix_PlayChannel(-1, wall3, 0);
				xVel = (xVel)*(-1);
				rect.x = 507;
			}

			if ((rect.y + 7 >= 430) && (rect.x <= 80))
			{
				Mix_PlayChannel(-1, wall4, 0);
				xVel = (xVel)*(-1);
				rect.x = 81;
			}

			if ((rect.y + 7 >= 430) && (rect.x + 7 >= 439))
			{
				Mix_PlayChannel(-1, wall5, 0);
				xVel = (xVel)*(-1);
				rect.x = 431;
			}

			if ((rect.y + 7 >= 409) && (rect.y + 7 < 429))
			{
				if ((rect.x >= 59) && (rect.x <= 80))
				{
					Mix_PlayChannel(-1, wall2, 0);
					xVel = ((sqrt(yVel*yVel)) + 1);
					yVel = -((sqrt(yVel*yVel)) + 1);
				}

				else if ((rect.x + 7 >= 439) && (rect.x + 7 <= 468))
				{
					Mix_PlayChannel(-1, wall3, 0);
					xVel = -((sqrt(yVel*yVel)) + 1);
					yVel = -((sqrt(yVel*yVel)) + 1);
				}

				else if (rect.x < 59)
				{
					Mix_PlayChannel(-1, wall2, 0);
					yVel = -yVel;
				}

				else if (rect.x + 7 > 468)
				{
					Mix_PlayChannel(-1, wall3, 0);
					yVel = -yVel;
				}
			}
			
			//Paddle Collisions
			if ((rect.x > pX - 8 && rect.x < pX + 84) && ((rect.y + 7 > 610 && rect.y + 7 < 620)))
			{
				yVel = -yVel;

				Mix_PlayChannel(-1, paddleBounce, 0);
				
				if (rect.x < pX + 2)		{	xVel = -3.5;	}
				else if (rect.x < pX + 12)	{	xVel = -3.0;	}
				else if (rect.x < pX + 22)	{	xVel = -2.2;	}
				else if (rect.x < pX + 32)	{	xVel = -1.4;	}
				else if (rect.x < pX + 44)	{	xVel = 0;		}
				else if (rect.x < pX + 54)	{	xVel = 1.4;		}
				else if (rect.x < pX + 64)	{	xVel = 2.2;		}
				else if (rect.x < pX + 74)	{	xVel = 3.0;		}
				else if (rect.x < pX + 84)	{	xVel = 3.5;		}
			}

		}
			

		//String Collision	
		if (((rect.y + 3 >= 434) && (rect.y + 3 <= 436)) || ((rect.y + 3 > 469) && (rect.y + 3 < 471)) || ((rect.y + 3 > 504) && (rect.y + 3 < 506)) ||
		((rect.y + 3 > 539) && (rect.y + 3 < 541)) || ((rect.y + 3 > 574) && (rect.y + 3 < 576)))
		{
			if (rect.x + 3 <= 132)		{	Mix_PlayChannel(-1, noteA, 0);	}
			else if (rect.x + 3 <= 183)	{	Mix_PlayChannel(-1, noteB, 0);	}
			else if (rect.x + 3 <= 234) {	Mix_PlayChannel(-1, noteC, 0);	}
			else if (rect.x + 3 <= 285)	{	Mix_PlayChannel(-1, noteD, 0);	}
			else if (rect.x + 3 <= 336) {	Mix_PlayChannel(-1, noteE, 0);	}
			else if (rect.x + 3 <= 387)	{	Mix_PlayChannel(-1, noteF, 0);	}
			else
			{	Mix_PlayChannel(-1, noteG, 0);	}
		}

		//BLOCK COLLISION
		if ((rect.x + 7 >= bX && rect.x < bX + 36) && (rect.y + 7 > bY && rect.y + 7 < bY + 3)) //Block Collision TOPBOTTOM
		{
				rect.y = bY - 8;
				yVel = -yVel;	
				Mix_PlayChannel(-1, blockKick, 0);				
		}	
		
		if ((rect.x + 7 >= bX && rect.x < bX + 36) && (rect.y >= bY + 17 && rect.y < bY + 20))
		{
				rect.y = bY + 21;
				yVel = -yVel;
				Mix_PlayChannel(-1, blockKick, 0);
		}
		
		if ((rect.y + 7 >= bY && rect.y <= bY + 20) && ((rect.x + 7 >= bX && rect.x + 7 <= bX + 3) || (rect.x >= bX + 33 && rect.x <= bX + 36)))//Block Collision LEFTRIGHT
		{
			xVel = -xVel;
			Mix_PlayChannel(-1, blockKick, 0);
		}
	} 

	else 
	{ 
		rect.y = 603;
		rect.x = pX+31;
	}
}

void ball::draw()
{
	SDL_BlitSurface(blockSprites, &clip, screen, &rect);
	moved = false;
}

void ball::move()
{
	moving = true;
}

void ball::reset(int ballSpeed)
{
	moving = false;
	
	xVel = rand()%8-4;

	if (xVel == 0)
	{
		xVel = 1;
	}
		
	yVel = (ballSpeed)*(-1);
}

int ball::myX()
{
	return rect.x;
}

int ball::myY()
{
	return rect.y;
}
