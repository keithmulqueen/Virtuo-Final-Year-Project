#include <sstream>
#include <string>
#include <fstream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "game.h"
#include "resource.h"
#include "level.h"
#include "menu.h"
#include "level_select.h"
#include "options.h"
#include "block.h"
#include "standard_block.h"
#include "heavy_block.h"
#include "note_block.h"
#include "titan_block.h"
#include "virtuo_block.h"

game::game(int(&bestScore)[41])
{	
	
	//Set starting number of Lives
	lives = 3;
	
	//Clip for Medals
	medalClip[0].x = 0;
	medalClip[0].y = 0;
	medalClip[0].h = 137;
	medalClip[0].w = 135;

	medalClip[1].h = 158;
	medalClip[1].w = 157;
	medalClip[1].y = 139;

	medalClip[2].x = 137;
	medalClip[2].y = 0;
	medalClip[2].h = 137;
	medalClip[2].w = 135;
	
	//Rects for Medals
	medalRect[0].x = 23;
	medalRect[0].y = 225;

	medalRect[1].x = 181;
	medalRect[1].y = 177;

	medalRect[2].x = 360;
	medalRect[2].y = 225;

	//Clip for Life Sprites
	livesClip.x = 74;
	livesClip.y = 105;
	livesClip.w = 40;
	livesClip.h = 28;

	rect[0].x = 10;
	rect[0].y = 5;

	rect[1].x = 40;
	rect[1].y = 5;

	rect[2].x = 70;
	rect[2].y = 5;	
}

game::~game()
{
	
}

int game::gameLoop(int &beginLevel, bool storymode, int paddleSpeed, int ballSpeed, int gameType, int(&bestScore)[41], bool &medalHS, bool &medal3L, bool &medal20, bool &levelAssign)
{		


		int level_1[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0 },
				{ 0, 0, 11, 1, 1, 1, 1, 1, 1, 1, 1, 11, 0, 0 },
				{ 0, 0, 11, 1, 1, 1, 1, 1, 1, 1, 1, 11, 0, 0 },
				{ 0, 0, 11, 11, 0, 0, 0, 0, 0, 0, 11, 11, 0, 0 },
				{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
				{ 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 11, 11, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 1, 1, 3, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_2[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 0 },
				{ 0, 11, 11, 11, 3, 1, 1, 1, 1, 3, 11, 11, 11, 0 },
				{ 0, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0 },
				{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
				{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
				{ 0, 0, 0, 0, 0, 2, 3, 3, 2, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 3, 1, 2, 2, 1, 3, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_3[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 11, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 11, 0 },
				{ 0, 0, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 0, 0 },
				{ 0, 0, 3, 1, 11, 1, 2, 2, 1, 11, 1, 3, 0, 0 },
				{ 0, 0, 1, 0, 0, 2, 5, 7, 2, 0, 0, 1, 0, 0 },
				{ 0, 0, 11, 0, 0, 2, 0, 0, 2, 0, 0, 11, 0, 0 },
				{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
				{ 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0 },
				{ 0, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 0 },
				{ 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_4[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 11, 0, 0, 0, 0, 11, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 3, 0, 0, 0, 0, 3, 1, 0, 0, 0 },
				{ 0, 11, 3, 1, 1, 11, 11, 11, 11, 1, 1, 3, 11, 0 },
				{ 0, 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 0 },
				{ 0, 0, 2, 2, 1, 9, 1, 1, 10, 1, 2, 2, 0, 0 },
				{ 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0 },
				{ 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_5[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
				{ 0, 3, 2, 3, 11, 3, 11, 11, 3, 11, 3, 2, 3, 0 },
				{ 0, 0, 2, 0, 0, 6, 0, 0, 8, 0, 0, 2, 0, 0 },
				{ 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0 },
				{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
				{ 0, 3, 2, 11, 1, 0, 0, 0, 0, 1, 11, 2, 3, 0 },
				{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 11, 11, 0, 0, 0, 0, 11, 11, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_6[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 11, 11, 11, 11, 0, 0, 0, 0, 0 },
				{ 0, 2, 2, 3, 0, 1, 1, 1, 1, 0, 3, 2, 2, 0 },
				{ 0, 0, 11, 2, 0, 0, 1, 1, 0, 0, 2, 11, 0, 0 },
				{ 0, 0, 0, 2, 0, 0, 1, 5, 0, 0, 2, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 4, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 7, 0 },
				{ 0, 0, 0, 2, 11, 3, 0, 0, 3, 11, 2, 0, 0, 0 },
				{ 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0 },
				{ 0, 0, 0, 0, 11, 3, 1, 1, 3, 11, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_7[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0 },
				{ 0, 11, 11, 11, 0, 0, 0, 0, 0, 0, 11, 11, 11, 0 },
				{ 0, 0, 1, 1, 11, 0, 0, 0, 0, 11, 1, 1, 0, 0 },
				{ 0, 0, 0, 1, 1, 11, 0, 0, 11, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
				{ 0, 0, 5, 2, 2, 2, 1, 1, 2, 2, 2, 5, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_8[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 1, 11, 11, 1, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 10, 1, 1, 3, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0 },
				{ 0, 0, 3, 0, 0, 3, 11, 11, 3, 0, 0, 3, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 6, 1, 1, 1, 0, 0, 1, 1, 1, 10, 0, 0 },
				{ 0, 0, 1, 11, 11, 1, 0, 0, 1, 11, 11, 1, 0, 0 },
				{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
				{ 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_9[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 1, 1, 1, 10, 0, 0, 4, 1, 1, 1, 0, 0 },
				{ 0, 0, 0, 1, 1, 11, 0, 0, 11, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 3, 0, 0, 3, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 11, 0, 0, 11, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0 },
				{ 0, 1, 1, 11, 11, 11, 0, 0, 11, 11, 11, 1, 1, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 1, 1, 3, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 7, 1, 3, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_10[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 2, 11, 11, 11, 11, 11, 2, 0 },
				{ 0, 0, 0, 0, 0, 0, 2, 3, 2, 3, 2, 3, 2, 0 },
				{ 0, 0, 2, 3, 2, 3, 2, 1, 1, 1, 1, 1, 2, 0 },
				{ 0, 2, 1, 11, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0 },
				{ 0, 3, 1, 0, 1, 3, 2, 1, 1, 1, 1, 1, 2, 0 },
				{ 0, 2, 1, 0, 1, 2, 2, 1, 1, 4, 1, 1, 2, 0 },
				{ 0, 0, 0, 0, 0, 2, 2, 11, 1, 0, 1, 11, 2, 0 },
				{ 0, 0, 0, 0, 0, 0, 11, 3, 1, 0, 1, 3, 11, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 7, 2, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_11[14][14] = {
				{ 0, 0, 0, 3, 1, 3, 1, 1, 3, 1, 3, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
				{ 0, 0, 1, 11, 0, 0, 0, 0, 0, 0, 11, 1, 0, 0 },
				{ 0, 0, 0, 0, 0, 1, 11, 11, 1, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 1, 1, 3, 0, 0, 0, 0, 0 },
				{ 0, 4, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0 },
				{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
				{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0 },
				{ 0, 0, 0, 11, 1, 5, 1, 1, 4, 1, 11, 0, 0, 0 },
				{ 0, 0, 0, 0, 11, 1, 1, 1, 1, 11, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 11, 1, 1, 11, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_12[14][14] = {
				{ 0, 0, 0, 3, 2, 3, 2, 3, 2, 3, 2, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2 },
				{ 0, 0, 0, 1, 0, 0, 6, 6, 0, 0, 0, 0, 0, 3 },
				{ 0, 11, 11, 1, 0, 0, 11, 11, 0, 0, 0, 0, 0, 2 },
				{ 2, 1, 1, 3, 0, 0, 11, 11, 0, 0, 3, 0, 0, 3 },
				{ 3, 0, 0, 0, 0, 0, 5, 4, 0, 0, 2, 0, 0, 2 },
				{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
				{ 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
				{ 2, 0, 0, 2, 3, 2, 11, 2, 3, 2, 3, 0, 0, 0 },
				{ 3, 0, 0, 3, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0 },
				{ 2, 0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_13[14][14] = {
				{ 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3 },
				{ 2, 1, 2, 1, 11, 2, 1, 1, 2, 11, 1, 2, 1, 2 },
				{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 3, 11, 1, 11, 11, 1, 11, 3, 0, 0, 0 },
				{ 0, 0, 0, 2, 3, 9, 8, 10, 9, 3, 2, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 2, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 2, 0 },
				{ 0, 3, 11, 11, 0, 1, 0, 0, 1, 0, 11, 11, 3, 0 },
				{ 0, 0, 1, 2, 0, 1, 0, 0, 1, 0, 2, 1, 0, 0 },
				{ 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_14[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 2, 2, 2, 3, 3, 2, 2, 3, 0, 0, 0 },
				{ 0, 0, 2, 2, 1, 1, 6, 6, 1, 1, 2, 2, 0, 0 },
				{ 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0 },
				{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
				{ 3, 1, 8, 0, 0, 1, 2, 2, 1, 0, 0, 1, 1, 3 },
				{ 2, 0, 0, 0, 0, 2, 11, 11, 2, 0, 0, 0, 0, 2 },
				{ 3, 0, 0, 0, 3, 2, 11, 11, 2, 3, 0, 0, 0, 3 },
				{ 2, 1, 1, 1, 2, 11, 11, 11, 11, 2, 1, 1, 1, 2 },
				{ 3, 0, 0, 0, 3, 11, 0, 0, 11, 3, 0, 0, 0, 8 },
				{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_15[14][14] = {
				{ 0, 0, 0, 11, 1, 11, 1, 1, 11, 1, 11, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 1, 1, 0, 11, 1, 1, 11, 0, 1, 1, 1, 0 },
				{ 0, 1, 5, 1, 0, 0, 0, 0, 0, 0, 1, 4, 1, 0 },
				{ 0, 1, 1, 1, 0, 0, 11, 11, 0, 0, 1, 1, 1, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 1, 1, 1, 11, 6, 7, 11, 1, 1, 1, 0, 0 },
				{ 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0 },
				{ 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_16[14][14] = {
				{ 0, 0, 0, 0, 1, 2, 0, 0, 2, 1, 0, 0, 0, 0 },
				{ 0, 0, 1, 1, 9, 2, 0, 0, 2, 8, 1, 1, 0, 0 },
				{ 0, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 11, 0, 0, 0, 0, 11, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 11, 0, 0, 0, 0, 11, 10, 0, 0, 0 },
				{ 0, 0, 11, 11, 11, 0, 0, 0, 0, 11, 11, 11, 0, 0 },
				{ 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0 },
				{ 0, 3, 2, 7, 0, 0, 0, 0, 0, 0, 7, 2, 3, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_17[14][14] = {
				{ 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0 },
				{ 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0 },
				{ 0, 3, 11, 3, 11, 3, 6, 2, 3, 11, 3, 11, 3, 0 },
				{ 0, 2, 2, 2, 2, 3, 0, 0, 3, 2, 2, 2, 2, 0 },
				{ 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0 },
				{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
				{ 0, 3, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 3, 0 },
				{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
				{ 0, 3, 1, 1, 1, 11, 0, 0, 11, 1, 1, 1, 3, 0 },
				{ 0, 2, 2, 2, 4, 0, 0, 0, 0, 4, 2, 2, 2, 0 },
				{ 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 0 },
				{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
				{ 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_18[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0 },
				{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
				{ 0, 0, 9, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0 },
				{ 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0 },
				{ 0, 2, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 9, 0 },
				{ 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 3, 1, 3, 3, 1, 3, 0, 0, 0, 0 },
				{ 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 8, 0, 0 },
				{ 0, 0, 0, 0, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0 },
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 4 },
				{ 0, 0, 0, 0, 1, 3, 11, 11, 3, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_19[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 3, 2, 2, 2, 2, 3, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 2, 1, 0, 1, 0, 2, 0, 0, 0, 0 },
				{ 0, 0, 3, 3, 2, 0, 1, 11, 1, 2, 3, 2, 0, 0 },
				{ 0, 3, 3, 5, 2, 1, 0, 1, 0, 2, 6, 2, 3, 0 },
				{ 0, 2, 1, 0, 1, 7, 1, 0, 1, 0, 1, 11, 2, 0 },
				{ 0, 2, 11, 1, 0, 1, 11, 1, 0, 1, 0, 1, 2, 0 },
				{ 2, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 2 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 11, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 11, 0 },
				{ 0, 11, 1, 4, 1, 0, 0, 0, 0, 1, 8, 1, 11, 0 },
				{ 0, 11, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 11, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		int level_20[14][14] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0 },
				{ 0, 2, 1, 1, 7, 0, 0, 0, 0, 9, 1, 1, 2, 0 },
				{ 0, 11, 1, 9, 2, 11, 0, 0, 11, 2, 10, 1, 11, 0 },
				{ 0, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 0 },
				{ 0, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 0 },
				{ 0, 0, 1, 0, 11, 0, 0, 0, 0, 11, 0, 1, 0, 0 },
				{ 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0 },
				{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
				{ 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 10, 3, 0 },
				{ 0, 0, 3, 1, 3, 2, 1, 1, 2, 3, 1, 3, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 2, 1, 1, 1, 0, 0, 1, 1, 1, 2, 0, 0 },
				{ 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0 } };

		if (levelAssign == false)
		{

		levels.push_back(level(level_1, gameType, ballSpeed));
		levels.push_back(level(level_2, gameType, ballSpeed));
		levels.push_back(level(level_3, gameType, ballSpeed));
		levels.push_back(level(level_4, gameType, ballSpeed));
		levels.push_back(level(level_5, gameType, ballSpeed));
		levels.push_back(level(level_6, gameType, ballSpeed));
		levels.push_back(level(level_7, gameType, ballSpeed));
		levels.push_back(level(level_8, gameType, ballSpeed));
		levels.push_back(level(level_9, gameType, ballSpeed));
		levels.push_back(level(level_10, gameType, ballSpeed));
		levels.push_back(level(level_11, gameType, ballSpeed));
		levels.push_back(level(level_12, gameType, ballSpeed));
		levels.push_back(level(level_13, gameType, ballSpeed));
		levels.push_back(level(level_14, gameType, ballSpeed));
		levels.push_back(level(level_15, gameType, ballSpeed));
		levels.push_back(level(level_16, gameType, ballSpeed));
		levels.push_back(level(level_17, gameType, ballSpeed));
		levels.push_back(level(level_18, gameType, ballSpeed));
		levels.push_back(level(level_19, gameType, ballSpeed));
		levels.push_back(level(level_20, gameType, ballSpeed));

		levelAssign = true;
}
	

	//Clip for PaddleSpeed Icon
	if (paddleSpeed == 1)
	{
		paddleSIcon.x = 74;
		paddleSIcon.y = 21;
		paddleSIcon.w = 24;
		paddleSIcon.h = 25;
	}
	else if (paddleSpeed == 2)
	{
		paddleSIcon.x = 98;
		paddleSIcon.y = 21;
		paddleSIcon.w = 24;
		paddleSIcon.h = 25;
	}
	else
	{
		paddleSIcon.x = 122;
		paddleSIcon.y = 21;
		paddleSIcon.w = 24;
		paddleSIcon.h = 25;
	}

	//Clip for BallSpeed Icon
	if (ballSpeed == 1)
	{
		ballSIcon.x = 74;
		ballSIcon.y = 49;
		ballSIcon.w = 24;
		ballSIcon.h = 25;
	}
	else if (ballSpeed == 2)
	{
		ballSIcon.x = 98;
		ballSIcon.y = 49;
		ballSIcon.w = 24;
		ballSIcon.h = 25;
	}
	else
	{
		ballSIcon.x = 122;
		ballSIcon.y = 49;
		ballSIcon.w = 24;
		ballSIcon.h = 25;
	}

	//Clip for game type icon
	if (gameType == 1)
	{
		gameTIcon.x = 74;
		gameTIcon.y = 77;
		gameTIcon.w = 24;
		gameTIcon.h = 24;
	}
	else if (gameType == 2)
	{
		gameTIcon.x = 98;
		gameTIcon.y = 77;
		gameTIcon.w = 24;
		gameTIcon.h = 24;
	}
	else if (gameType == 3)
	{
		gameTIcon.x = 122;
		gameTIcon.y = 77;
		gameTIcon.w = 24;
		gameTIcon.h = 24;
	}
	
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return 0; //return STATE_EXIT
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				beginLevel = 0;
				return 0; //return STATE_MENU
			}
		}

		levels[beginLevel].update(event);
	}

	levels[beginLevel].draw(paddleSpeed, ballSpeed, gameType);

	

	for (int x = 0; x < lives; x++)
	{
		if (x <= 3)
		{
			blit(392 + (x * 43), 2, blockSprites, screen, &livesClip);
		}
	}

	SDL_BlitSurface(blockSprites, &gameTIcon, screen, &rect[0]);
	SDL_BlitSurface(blockSprites, &ballSIcon, screen, &rect[1]);
	SDL_BlitSurface(blockSprites, &paddleSIcon, screen, &rect[2]);


	//convert score to a string and output it
	font = TTF_OpenFont("data/forte.ttf", 20);

	std::stringstream out;
	std::string SScore;
	out << score;
	SScore = out.str();
	printText(320, 5, SScore, 255, 255, 0);
	

	if (levels[beginLevel].levelComplete(gameType) && storymode) //if you complete a level in story mode
	{	
		if (lives == 3)		{ medal3L = true; }
		if (score >= 10)	{ medal20 = true; }

		setHighScore(gameType, beginLevel, bestScore, medalHS);
		gameOver(gameType, beginLevel, bestScore, medalHS, medal3L, medal20);
		
		lives = 3;

		if		(gameType == 1)	{ score = 10; }
		else if (gameType == 3) { score = 0;  }

		levels[beginLevel].reset(ballSpeed);

		if (beginLevel < levels.size() - 1)	
		{	beginLevel++;	}
		else
		{	
			if (gameType == 2)
			{
				score = 0;
			}
			return 0;	
		}			
	}

	else if (levels[beginLevel].levelComplete(gameType) && !storymode) // when you complete a level that is not story mode
	{
		if (lives == 3)	{	medal3L = true;	}
		if (score >= 10){	medal20 = true; }

		setHighScore(gameType, beginLevel, bestScore, medalHS);
		gameOver(gameType, beginLevel, bestScore, medalHS, medal3L, medal20);

		levels[beginLevel].reset(ballSpeed);

		return 2;
	}

	else if (levels[beginLevel].dead(ballSpeed)) // if the ball went below screen ( DIED )
	{
		lives--;

		if (lives <= 0)
		{
			if (gameType == 2)
			{
				setHighScore(gameType, beginLevel, bestScore, medalHS);
				score = 0;
			}
			
			gameOver(gameType, beginLevel, bestScore, medalHS, medal3L, medal20);

			//reset variables			
			lives = 3;
			
			levels[beginLevel].reset(ballSpeed);
				
			return 0;
		}
	}

	SDL_Flip(screen);
	
	return 1;
}



void game::gameOver(int gameType, int beginLevel, int (&bestScore)[41], bool &medalHS, bool &medal3L, bool &medal20)
{
	//Make background
	SDL_Surface *back = loadImage("data/GOBack.png");
	
	Mix_PlayChannel(-1, virtuo, 0);

	//Display everything
	blit(0, 0, back, screen);

	if (gameType == 1)
	{
		medalClip[1].x = 0;

		if(medalHS) {	SDL_BlitSurface(medalSprites, &medalClip[1], screen, &medalRect[1]); }
		if(medal3L) {	SDL_BlitSurface(medalSprites, &medalClip[2], screen, &medalRect[2]); }
		if(medal20) {	SDL_BlitSurface(medalSprites, &medalClip[0], screen, &medalRect[0]); }
	}	
	else if(gameType == 2)
	{		
		medalClip[1].x = 158;

		if (medalHS) { SDL_BlitSurface(medalSprites, &medalClip[1], screen, &medalRect[1]); }
		if (medal3L) { SDL_BlitSurface(medalSprites, &medalClip[2], screen, &medalRect[2]); }
		if (medal20) { SDL_BlitSurface(medalSprites, &medalClip[0], screen, &medalRect[0]); }
	}
	else
	{
		medalClip[1].x = 316;

		if (medalHS) { SDL_BlitSurface(medalSprites, &medalClip[1], screen, &medalRect[1]); }
		if (medal3L) { SDL_BlitSurface(medalSprites, &medalClip[2], screen, &medalRect[2]); }
		if (medal20) { SDL_BlitSurface(medalSprites, &medalClip[0], screen, &medalRect[0]); }
	}

	levels[beginLevel].reset(ballSpeed);

	medalHS, medal3L, medal20 = false;

	SDL_Flip(screen);

	SDL_Delay(6000);

	SDL_FreeSurface(back);
}


void game::setHighScore(int gameType, int beginLevel, int (&bestScore)[41], bool &medalHS)
{
	medalHS = false;
	
	if (gameType == 1)//Virtuo
	{
		if (score > bestScore[beginLevel])
		{
			bestScore[beginLevel] = score;
			medalHS = true;
			score = 10;
		}
	}

	else if (gameType == 2)//Breakout
	{
		if (score > bestScore[40])
		{
			bestScore[40] = score;
			medalHS = true;
		}
	}

	else if (gameType == 3)//VirtuoX
	{
		if (score > bestScore[beginLevel+20])
		{
			bestScore[beginLevel+20] = score;
			medalHS = true;
			score = 0;
		}
	}

	std::ofstream file("data/bestscores.txt");
	if (file.is_open())
	{
		for (int count = 0; count < 41; count++)
		{
			file << bestScore[count] << " ";
		}

		file.close();
	}

}


