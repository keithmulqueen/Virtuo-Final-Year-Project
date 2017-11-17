#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include <fstream>

#include "resource.h"

SDL_Surface *loadImage(std::string filename)
{
    SDL_Surface* LoadedImg = NULL;
    SDL_Surface* OptImg = NULL;
    LoadedImg = IMG_Load(filename.c_str()); 

    if (LoadedImg != NULL)
    {
        OptImg = SDL_DisplayFormat(LoadedImg); 
        SDL_FreeSurface(LoadedImg);
    }
	else
	{
		error("Could Not Open " + filename);
	}
    
	return OptImg;
}

void blit(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(source, clip, destination, &rect);
}

void printText(int x, int y, std::string words, int red, int green, int blue)
{
	SDL_Color color = {red, green, blue};

	message = TTF_RenderText_Solid(font, words.c_str(), color);
	blit(x, y, message, screen);
	SDL_FreeSurface(message);
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{ 
		return false; 
	} 
	
	screen = SDL_SetVideoMode(520, 640, 32, SDL_SWSURFACE);
	
	if (screen == NULL)												{ return false;	 }
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)	{ return false;  }	
	if( TTF_Init() == -1 )											{ return false;	 }

	SDL_Surface* icon = loadImage("data/icon.png");
	SDL_WM_SetIcon(icon, NULL);
	SDL_WM_SetCaption("Virtuo : Breakout Remake for the Visually Impaired", NULL); 	
	SDL_FreeSurface(icon);
	return true;
}

void close()
{
	if (welcome != NULL) Mix_FreeChunk(welcome);
	if (playgame != NULL) Mix_FreeChunk(playgame);
	if (breakout != NULL) Mix_FreeChunk(breakout);
	if (virtuo != NULL) Mix_FreeChunk(virtuo);
	if (virtuoR != NULL) Mix_FreeChunk(virtuoR);
	if (spaceForOption != NULL) Mix_FreeChunk(spaceForOption);
	if (spaceForEnter != NULL) Mix_FreeChunk(spaceForEnter);
	if (downFoOption != NULL) Mix_FreeChunk(downFoOption);
	if (levelselect != NULL) Mix_FreeChunk(levelselect);
	if (currentRuleIs != NULL) Mix_FreeChunk(currentRuleIs);
	if (optionsMenu != NULL) Mix_FreeChunk(optionsMenu);
	if (instructions != NULL) Mix_FreeChunk(instructions);
	if (advance13 != NULL) Mix_FreeChunk(advance13);
	if (advance2 != NULL) Mix_FreeChunk(advance2);
	if (HSvirtuo != NULL) Mix_FreeChunk(HSvirtuo);
	if (HSvirtuoR != NULL) Mix_FreeChunk(HSvirtuoR);
	if (VHSis != NULL) Mix_FreeChunk(VHSis);
	if (BHSis != NULL) Mix_FreeChunk(BHSis);
	if (VRHSis != NULL) Mix_FreeChunk(VRHSis);
	if (credits != NULL) Mix_FreeChunk(credits);
	if (selectBall != NULL) Mix_FreeChunk(selectBall);
	if (selectPaddle != NULL) Mix_FreeChunk(selectPaddle);
	if (selectGame != NULL) Mix_FreeChunk(selectGame);
	if (resetSpace != NULL) Mix_FreeChunk(resetSpace);
	if (rightArrow != NULL) Mix_FreeChunk(rightArrow);
	if (high != NULL) Mix_FreeChunk(high);
	if (low != NULL) Mix_FreeChunk(low);
	if (medium != NULL) Mix_FreeChunk(medium);
	if (returnToMain != NULL) Mix_FreeChunk(returnToMain);
	if (levelNum != NULL) Mix_FreeChunk(levelNum);
	if (one != NULL) Mix_FreeChunk(one);
	if (two != NULL) Mix_FreeChunk(two);
	if (three != NULL) Mix_FreeChunk(three);
	if (four != NULL) Mix_FreeChunk(four);
	if (five != NULL) Mix_FreeChunk(five);
	if (six != NULL) Mix_FreeChunk(six);
	if (seven != NULL) Mix_FreeChunk(seven);
	if (eight != NULL) Mix_FreeChunk(eight);
	if (nine != NULL) Mix_FreeChunk(nine);
	if (ten != NULL) Mix_FreeChunk(ten);
	if (eleven != NULL) Mix_FreeChunk(eleven);
	if (twelve != NULL) Mix_FreeChunk(twelve);
	if (thirteen != NULL) Mix_FreeChunk(thirteen);
	if (fourteen != NULL) Mix_FreeChunk(fourteen);
	if (fifteen != NULL) Mix_FreeChunk(fifteen);
	if (sixteen != NULL) Mix_FreeChunk(sixteen);
	if (seventeen != NULL) Mix_FreeChunk(seventeen);
	if (eighteen != NULL) Mix_FreeChunk(eighteen);
	if (ninteen != NULL) Mix_FreeChunk(ninteen);
	if (twenty != NULL) Mix_FreeChunk(twenty);
	if (highSC != NULL) Mix_FreeChunk(highSC);

	if ( noteA != NULL) Mix_FreeChunk(noteA);
	if ( noteB != NULL) Mix_FreeChunk(noteB);
	if ( noteC != NULL) Mix_FreeChunk(noteC);
	if ( noteD != NULL) Mix_FreeChunk(noteD);
	if ( noteE != NULL) Mix_FreeChunk(noteE);
	if ( noteF != NULL) Mix_FreeChunk(noteF);
	if ( noteG != NULL) Mix_FreeChunk(noteG);

	if (blockKick != NULL) Mix_FreeChunk(blockKick);

	if (wall1 != NULL) Mix_FreeChunk(wall1);
	if (wall2 != NULL) Mix_FreeChunk(wall2);
	if (wall3 != NULL) Mix_FreeChunk(wall3);
	if (wall4 != NULL) Mix_FreeChunk(wall4);
	if (wall5 != NULL) Mix_FreeChunk(wall5);

	if ( vBlock1 != NULL) Mix_FreeChunk(vBlock1);
	if ( vBlock2 != NULL) Mix_FreeChunk(vBlock2);

	if ( dockL != NULL) Mix_FreeChunk(dockL);
	if ( dockR != NULL) Mix_FreeChunk(dockR);

	if (paddleBounce != NULL) Mix_FreeChunk(paddleBounce);

	if (paddleLockA != NULL) Mix_FreeChunk(paddleLockA);
	if (paddleLockB != NULL) Mix_FreeChunk(paddleLockB);
	if (paddleLockC != NULL) Mix_FreeChunk(paddleLockC);
	if (paddleLockD != NULL) Mix_FreeChunk(paddleLockD);
	if (paddleLockE != NULL) Mix_FreeChunk(paddleLockE);
	if (paddleLockF != NULL) Mix_FreeChunk(paddleLockF);
	if (paddleLockG != NULL) Mix_FreeChunk(paddleLockG);

	if ( noteBlockA != NULL) Mix_FreeChunk(noteBlockA);
	if ( noteBlockB != NULL) Mix_FreeChunk(noteBlockB);
	if ( noteBlockC != NULL) Mix_FreeChunk(noteBlockC);
	if ( noteBlockD != NULL) Mix_FreeChunk(noteBlockD);
	if ( noteBlockE != NULL) Mix_FreeChunk(noteBlockE);
	if ( noteBlockF != NULL) Mix_FreeChunk(noteBlockD);
	if ( noteBlockB != NULL) Mix_FreeChunk(noteBlockE);

	if (medalSprites != NULL) SDL_FreeSurface(medalSprites);
	if (blockSprites != NULL) SDL_FreeSurface(blockSprites);

	Mix_CloseAudio(); 
	TTF_Quit(); 
	SDL_Quit();
}

int error(std::string error)
{
	std::ofstream file;
	file.open("error.txt", std::ios::out | std::ios::trunc);
	file << error;
	file << "Game Error.";
	file.close();
	close();
	return 6;
}
