#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "resource.h"
#include "paddle.h"
#include "ball.h"
#include "block.h"
#include "virtuo_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "heavy_block.h"
#include "standard_block.h"
#include "level.h"

level::level(int levelArray[14][14], int gameType, int ballSpeed)
{

	//background image
	bgClip.x = 0;
	bgClip.y = 0;
	bgClip.w = 520;
	bgClip.h = 640;

	//background position
	bgRect.x = 0;
	bgRect.y = 0;


	for (int x = 0; x <= 13; x++) //make blocks
	{
		for (int y = 0; y <= 13; y++)
		{
			if (levelArray[y][x] == 0)
			{
				blocks.push_back(new block()); //Empty
			}
			
			else if (levelArray[y][x] == 1)
			{
				blocks.push_back(new standard_block(8 + x * 36, 50 + y * 20, gameType)); //Standard
			}

			else if (levelArray[y][x] == 2)
			{
				blocks.push_back(new heavy_block(8 + x * 36, 50 + y * 20, gameType)); //Heavy
			}
		
			else if (levelArray[y][x] == 3)
			{
				blocks.push_back(new titan_block(8 + x * 36, 50 + y * 20, gameType)); //Titan
			}

			else if (levelArray[y][x] == 4)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 0)); //NoteA

			}

			else if (levelArray[y][x] == 5)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 1)); //NoteB
			}

			else if (levelArray[y][x] == 6)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 2)); //NoteC
			}

			else if (levelArray[y][x] == 7)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 3)); //NoteD
			}

			else if (levelArray[y][x] == 8)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 4)); //NoteE
			}

			else if (levelArray[y][x] == 9)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 5)); //NoteF
			}

			else if (levelArray[y][x] == 10)
			{
				blocks.push_back(new note_block(8 + x * 36, 50 + y * 20, gameType, 6)); //NoteG
			}

			else if (levelArray[y][x] == 11)
			{
				blocks.push_back(new virtuo_block(8 + x * 36, 50 + y * 20, gameType)); //Virtuo
			}
		}
	}
		ball ball1(ballSpeed);
}

void level::draw(int paddleSpeed, int ballSpeed, int gameType)
{
	paddle1.update(paddleSpeed);

	for (unsigned int x = 0; x < blocks.size(); x++)
	{
			ball1.update(paddle1.myX(), (*blocks[x]).myX(), (*blocks[x]).myY()); //update ea. ball
			(*blocks[x]).update(ball1.myX(), ball1.myY());				  //and ea. block
	}
	
	SDL_BlitSurface(backgroundImg, &bgClip, screen, &bgRect);
	
	paddle1.draw(gameType);
	ball1.draw();

	for (unsigned int x = 0; x < blocks.size(); x++)
	{
		(*blocks[x]).draw();
	}
		
}

void level::update(SDL_Event event)
{
	Uint8 *keystates = SDL_GetKeyState(NULL);

	if (keystates[SDLK_SPACE])
	{
			ball1.move();	
	}
}

bool level::levelComplete(int gameType)
{
	if (gameType == 1 || gameType == 3)
	{
		for (unsigned int x = 0; x < blocks.size(); x++)
		{
			if (!(*blocks[x]).activeNote())
			{
				return false;
			}
		}
	}

	else if (gameType == 2)
	{
		for (unsigned int x = 0; x < blocks.size(); x++)
		{
			if (!(*blocks[x]).breakoutValid())
			{
				return false;
			}
		}
	}

	return true;
}

bool level::dead(int ballSpeed)
{
	
	if (ball1.myY() < 640) //if ball is not below screen
	{
		return false;
	}

	ball1.reset(ballSpeed);
	
	return true;
}

void level::clearScreen()
{
	for (unsigned int x = 0; x < blocks.size(); x++)
		(*blocks[x]).clearBlock();
}

void level::reset(int ballSpeed)
{
	for (unsigned int x = 0; x < blocks.size(); x++)
	{
		(*blocks[x]).establish();
	}	

	ball1.reset(ballSpeed);
}
