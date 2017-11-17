#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "SDL.h"

#include "level.h"

class game
{
public:
	game(int(&bestScore)[41]);
	~game();

	int gameLoop(int &beginLevel, bool story, int paddleSpeed, int ballSpeed, int gameType, int (&bestScore)[41], bool &medalHS, bool &medal3L, bool &medal20, bool &levelAssign);
	void setHighScore(int gameType, int beginLevel, int(&bestScore)[41], bool &medalHS);

private:
	void gameOver(int gameType, int beginLevel, int(&bestScore)[41], bool &medalHS, bool &medal3L, bool &medal20);


	SDL_Event event;
	std::vector<level> levels;

	SDL_Rect livesClip;
	SDL_Rect ballSIcon;
	SDL_Rect paddleSIcon;
	SDL_Rect gameTIcon;
	SDL_Rect rect[3];
	SDL_Rect medalClip[3];
	SDL_Rect medalRect[3];

	int lives;
	int paddleSpeed;
	int ballSpeed;
};

#endif
