//resource.h - contains resouces for init, clean, loadImage, blit
#ifndef RESOURCE_H
#define RESOURCE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>

extern SDL_Surface *medalSprites;
extern SDL_Surface *blockSprites;
extern SDL_Surface *screen;
extern SDL_Surface *backgroundImg;
extern SDL_Surface *message;

//Voice clips
extern Mix_Chunk *welcome;
extern Mix_Chunk *playgame;
extern Mix_Chunk *breakout;
extern Mix_Chunk *virtuo;
extern Mix_Chunk *virtuoR;
extern Mix_Chunk *spaceForOption;
extern Mix_Chunk *spaceForEnter;
extern Mix_Chunk *downFoOption;
extern Mix_Chunk *levelselect;
extern Mix_Chunk *currentRuleIs;
extern Mix_Chunk *optionsMenu;
extern Mix_Chunk *instructions;
extern Mix_Chunk *advance13;
extern Mix_Chunk *advance2;
extern Mix_Chunk *HSvirtuo;
extern Mix_Chunk *HSvirtuoR;
extern Mix_Chunk *VHSis;
extern Mix_Chunk *BHSis;
extern Mix_Chunk *VRHSis;
extern Mix_Chunk *credits;
extern Mix_Chunk *selectBall;
extern Mix_Chunk *selectPaddle;
extern Mix_Chunk *selectGame;
extern Mix_Chunk *resetSpace;
extern Mix_Chunk *rightArrow;
extern Mix_Chunk *high;
extern Mix_Chunk *low;
extern Mix_Chunk *medium;
extern Mix_Chunk *returnToMain;
extern Mix_Chunk *levelNum;
extern Mix_Chunk *one;
extern Mix_Chunk *two;
extern Mix_Chunk *three;
extern Mix_Chunk *four;
extern Mix_Chunk *five;
extern Mix_Chunk *six;
extern Mix_Chunk *seven;
extern Mix_Chunk *eight;
extern Mix_Chunk *nine;
extern Mix_Chunk *ten;
extern Mix_Chunk *eleven;
extern Mix_Chunk *twelve;
extern Mix_Chunk *thirteen;
extern Mix_Chunk *fourteen;
extern Mix_Chunk *fifteen;
extern Mix_Chunk *sixteen;
extern Mix_Chunk *seventeen;
extern Mix_Chunk *eighteen;
extern Mix_Chunk *ninteen;
extern Mix_Chunk *twenty;
extern Mix_Chunk *highSC;

extern Mix_Chunk *noteA;
extern Mix_Chunk *noteB;
extern Mix_Chunk *noteC;
extern Mix_Chunk *noteD;
extern Mix_Chunk *noteE;
extern Mix_Chunk *noteF;
extern Mix_Chunk *noteG;

extern Mix_Chunk *wall1;
extern Mix_Chunk *wall2;
extern Mix_Chunk *wall3;
extern Mix_Chunk *wall4;
extern Mix_Chunk *wall5;

extern Mix_Chunk *blockKick;

extern Mix_Chunk *vBlock1;
extern Mix_Chunk *vBlock2;

extern Mix_Chunk *dockL;
extern Mix_Chunk *dockR;

extern Mix_Chunk *paddleBounce;

extern Mix_Chunk *paddleLockA;
extern Mix_Chunk *paddleLockB;
extern Mix_Chunk *paddleLockC;
extern Mix_Chunk *paddleLockD;
extern Mix_Chunk *paddleLockE;
extern Mix_Chunk *paddleLockF;
extern Mix_Chunk *paddleLockG;

extern Mix_Chunk *noteBlockA;
extern Mix_Chunk *noteBlockB;
extern Mix_Chunk *noteBlockC;
extern Mix_Chunk *noteBlockD;
extern Mix_Chunk *noteBlockE;
extern Mix_Chunk *noteBlockF;
extern Mix_Chunk *noteBlockG;

extern TTF_Font *font;

extern int score;

SDL_Surface *loadImage(std::string filename);
void blit(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
void printText(int x, int y, std::string words, int r, int g, int b);
bool init();
void close();
int error(std::string error);

#endif