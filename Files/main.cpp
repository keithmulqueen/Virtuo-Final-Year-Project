#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "resource.h"
#include "game.h"
#include "menu.h"
#include "options.h"
#include "level_select.h"
#include "string.h"
#include "level.h"

SDL_Surface *screen = NULL; 
SDL_Surface *medalSprites = NULL;
SDL_Surface *blockSprites = NULL;
SDL_Surface *message = NULL;
SDL_Surface *paddleSprites = NULL;
SDL_Surface *backgroundImg = NULL;

Mix_Chunk *noteA = NULL;
Mix_Chunk *noteB = NULL;
Mix_Chunk *noteC = NULL;
Mix_Chunk *noteD = NULL;
Mix_Chunk *noteE = NULL;
Mix_Chunk *noteF = NULL;
Mix_Chunk *noteG = NULL;

Mix_Chunk *blockKick = NULL;

Mix_Chunk *wall1 = NULL;
Mix_Chunk *wall2 = NULL;
Mix_Chunk *wall3 = NULL;
Mix_Chunk *wall4 = NULL;
Mix_Chunk *wall5 = NULL;

Mix_Chunk *vBlock1 = NULL;
Mix_Chunk *vBlock2 = NULL;


Mix_Chunk *dockL = NULL;
Mix_Chunk *dockR = NULL;

Mix_Chunk *paddleBounce = NULL;

Mix_Chunk *paddleLockA = NULL;
Mix_Chunk *paddleLockB = NULL;
Mix_Chunk *paddleLockC = NULL;
Mix_Chunk *paddleLockD = NULL;
Mix_Chunk *paddleLockE = NULL;
Mix_Chunk *paddleLockF = NULL;
Mix_Chunk *paddleLockG = NULL;

Mix_Chunk *noteBlockA = NULL;
Mix_Chunk *noteBlockB = NULL;
Mix_Chunk *noteBlockC = NULL;
Mix_Chunk *noteBlockD = NULL;
Mix_Chunk *noteBlockE = NULL;
Mix_Chunk *noteBlockF = NULL;
Mix_Chunk *noteBlockG = NULL;

Mix_Chunk *paddleA = NULL;
Mix_Chunk *paddleB = NULL;
Mix_Chunk *paddleC = NULL;
Mix_Chunk *paddleD = NULL;
Mix_Chunk *paddleE = NULL;

//VOICE NOTES
Mix_Chunk *welcome = NULL;
Mix_Chunk *playgame = NULL;
Mix_Chunk *breakout = NULL;
Mix_Chunk *virtuo = NULL;
Mix_Chunk *virtuoR = NULL;
Mix_Chunk *spaceForOption = NULL;
Mix_Chunk *spaceForEnter = NULL;
Mix_Chunk *downFoOption = NULL;
Mix_Chunk *levelselect = NULL;
Mix_Chunk *currentRuleIs = NULL;
Mix_Chunk *optionsMenu = NULL;
Mix_Chunk *instructions = NULL;
Mix_Chunk *advance13 = NULL;
Mix_Chunk *advance2 = NULL;
Mix_Chunk *HSvirtuo = NULL;
Mix_Chunk *HSvirtuoR = NULL;
Mix_Chunk *VHSis = NULL;
Mix_Chunk *BHSis = NULL;
Mix_Chunk *VRHSis = NULL;
Mix_Chunk *credits = NULL;
Mix_Chunk *selectBall = NULL;
Mix_Chunk *selectPaddle = NULL;
Mix_Chunk *selectGame = NULL;
Mix_Chunk *resetSpace = NULL;
Mix_Chunk *rightArrow = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *low = NULL;
Mix_Chunk *medium = NULL;
Mix_Chunk *returnToMain = NULL;
Mix_Chunk *levelNum = NULL;
Mix_Chunk *one = NULL;
Mix_Chunk *two = NULL;
Mix_Chunk *three = NULL;
Mix_Chunk *four = NULL;
Mix_Chunk *five = NULL;
Mix_Chunk *six = NULL;
Mix_Chunk *seven = NULL;
Mix_Chunk *eight = NULL;
Mix_Chunk *nine = NULL;
Mix_Chunk *ten = NULL;
Mix_Chunk *eleven = NULL;
Mix_Chunk *twelve = NULL;
Mix_Chunk *thirteen = NULL;
Mix_Chunk *fourteen = NULL;
Mix_Chunk *fifteen = NULL;
Mix_Chunk *sixteen = NULL;
Mix_Chunk *seventeen = NULL;
Mix_Chunk *eighteen = NULL;
Mix_Chunk *ninteen = NULL;
Mix_Chunk *twenty = NULL;
Mix_Chunk *highSC = NULL;

TTF_Font *font = NULL;

int score = 10;

bool medal20 = false;
bool medalHS = false;
bool medal3L = false;

bool storymode = true;

int main(int argc, char* args[])
{
	srand((unsigned)time(0));
	int bestScore[41];
	std::ifstream file;
	file.open("data/bestscores.txt", std::ios::in | std::ios::binary);

	if (!file)
	{
		for (int x = 0; x < 41; x++)	{	bestScore[x] = 0;	}
	}
	else
	{
		for (int x = 0; x < 41; x++)	{	file >> bestScore[x];	}
	}
	
	file.close();


	if (!init())
	{
		SDL_Quit();
		return 6;
	}

	int begin_lvl = 0;
	bool storymode = true;
	bool levelAssign = false;

	int paddleSpeed = 1;
	int ballSpeed = 1;
	int gameType = 1;

	bool quit = false;
	Uint32 time = SDL_GetTicks();
	int gameState = 0;

	medalSprites = loadImage("data/medals.png");
	blockSprites = loadImage("data/BlockSprites.png");
	backgroundImg = loadImage("data/GameBack.png");

	welcome = Mix_LoadWAV("data/audio/1Welcome.wav"); if (welcome == NULL){ return error("Error loading WAV file."); }
	playgame = Mix_LoadWAV("data/audio/2PlayGame.wav"); if (playgame == NULL){ return error("Error loading WAV file."); }
	breakout = Mix_LoadWAV("data/audio/BreakOut.wav"); if (breakout == NULL){ return error("Error loading WAV file."); }
	virtuo = Mix_LoadWAV("data/audio/Virtuo.wav"); if (virtuo == NULL){ return error("Error loading WAV file."); }
	virtuoR = Mix_LoadWAV("data/audio/VirtuoR.wav"); if (virtuoR == NULL){ return error("Error loading WAV file."); }
	spaceForOption = Mix_LoadWAV("data/audio/UseSpace4Option.wav"); if (spaceForOption == NULL){ return error("Error loading WAV file."); }
	spaceForEnter = Mix_LoadWAV("data/audio/UseSpace4Enter.wav"); if (spaceForEnter == NULL){ return error("Error loading WAV file."); }
	downFoOption = Mix_LoadWAV("data/audio/Down4Options.wav"); if (downFoOption == NULL){ return error("Error loading WAV file."); }
	levelselect = Mix_LoadWAV("data/audio/3LevelSelect.wav"); if (levelselect == NULL){ return error("Error loading WAV file."); }
	currentRuleIs = Mix_LoadWAV("data/audio/CurrentRulesetIs..wav"); if (currentRuleIs == NULL){ return error("Error loading WAV file."); }
	optionsMenu = Mix_LoadWAV("data/audio/4OptionsMenu.wav"); if (optionsMenu == NULL){ return error("Error loading WAV file."); }
	instructions = Mix_LoadWAV("data/audio/5Instructions.wav"); if (instructions == NULL){ return error("Error loading WAV file."); }
	advance13 = Mix_LoadWAV("data/audio/Advance13.wav"); if (advance13 == NULL){ return error("Error loading WAV file."); }
	advance2 = Mix_LoadWAV("data/audio/Advance2.wav"); if (advance2 == NULL){ return error("Error loading WAV file."); }
	HSvirtuo = Mix_LoadWAV("data/audio/HSpossibleV.wav"); if (HSvirtuo == NULL){ return error("Error loading WAV file."); }
	HSvirtuoR = Mix_LoadWAV("data/audio/HSpossibleVR.wav"); if (HSvirtuoR == NULL){ return error("Error loading WAV file."); }
	VHSis = Mix_LoadWAV("data/audio/VHSis.wav"); if (VHSis == NULL){ return error("Error loading WAV file."); }
	BHSis = Mix_LoadWAV("data/audio/BHSis.wav"); if (BHSis == NULL){ return error("Error loading WAV file."); }
	VRHSis = Mix_LoadWAV("data/audio/VRHSis.wav"); if (VRHSis == NULL){ return error("Error loading WAV file."); }
	credits = Mix_LoadWAV("data/audio/6Credits.wav"); if (credits == NULL){ return error("Error loading WAV file."); }
	selectBall = Mix_LoadWAV("data/audio/selectBS.wav"); if (selectBall == NULL){ return error("Error loading WAV file."); }
	selectPaddle = Mix_LoadWAV("data/audio/selectps.wav"); if (selectPaddle == NULL){ return error("Error loading WAV file."); }
	selectGame = Mix_LoadWAV("data/audio/selectgt.wav"); if (selectGame == NULL){ return error("Error loading WAV file."); }
	resetSpace = Mix_LoadWAV("data/audio/spacereseths.wav"); if (resetSpace == NULL){ return error("Error loading WAV file."); }
	rightArrow = Mix_LoadWAV("data/audio/rightArroechangevals.wav"); if (rightArrow == NULL){ return error("Error loading WAV file."); }
	high = Mix_LoadWAV("data/audio/High.wav"); if (high == NULL){ return error("Error loading WAV file."); }
	low = Mix_LoadWAV("data/audio/Low.wav"); if (low == NULL){ return error("Error loading WAV file."); }
	medium = Mix_LoadWAV("data/audio/Medium.wav"); if (medium == NULL){ return error("Error loading WAV file."); }
	returnToMain = Mix_LoadWAV("data/audio/mainreturn.wav"); if (returnToMain == NULL){ return error("Error loading WAV file."); }
	levelNum = Mix_LoadWAV("data/audio/level..wav"); if (levelNum == NULL){ return error("Error loading WAV file."); }
	one = Mix_LoadWAV("data/audio/one.wav"); if (one == NULL){ return error("Error loading WAV file."); }
	two = Mix_LoadWAV("data/audio/two.wav"); if (two == NULL){ return error("Error loading WAV file."); }
	three = Mix_LoadWAV("data/audio/three.wav"); if (three == NULL){ return error("Error loading WAV file."); }
	four = Mix_LoadWAV("data/audio/four.wav"); if (four == NULL){ return error("Error loading WAV file."); }
	five = Mix_LoadWAV("data/audio/five.wav"); if (five == NULL){ return error("Error loading WAV file."); }
	six = Mix_LoadWAV("data/audio/six.wav"); if (six == NULL){ return error("Error loading WAV file."); }
	seven = Mix_LoadWAV("data/audio/seven.wav"); if (seven == NULL){ return error("Error loading WAV file."); }
	eight = Mix_LoadWAV("data/audio/eight.wav"); if (eight == NULL){ return error("Error loading WAV file."); }
	nine = Mix_LoadWAV("data/audio/nine.wav"); if (nine == NULL){ return error("Error loading WAV file."); }
	ten = Mix_LoadWAV("data/audio/ten.wav"); if (ten == NULL){ return error("Error loading WAV file."); }
	eleven = Mix_LoadWAV("data/audio/eleven.wav"); if (eleven == NULL){ return error("Error loading WAV file."); }
	twelve = Mix_LoadWAV("data/audio/twelve.wav"); if (twelve == NULL){ return error("Error loading WAV file."); }
	thirteen = Mix_LoadWAV("data/audio/thirteen.wav"); if (thirteen == NULL){ return error("Error loading WAV file."); }
	fourteen = Mix_LoadWAV("data/audio/fourteen.wav"); if (fourteen == NULL){ return error("Error loading WAV file."); }
	fifteen = Mix_LoadWAV("data/audio/fifteen.wav"); if (fifteen == NULL){ return error("Error loading WAV file."); }
	sixteen = Mix_LoadWAV("data/audio/sisteen.wav"); if (sixteen == NULL){ return error("Error loading WAV file."); }
	seventeen = Mix_LoadWAV("data/audio/sevteen.wav"); if (seventeen == NULL){ return error("Error loading WAV file."); }
	eighteen = Mix_LoadWAV("data/audio/eighteen.wav"); if (eighteen == NULL){ return error("Error loading WAV file."); }
	ninteen = Mix_LoadWAV("data/audio/ninteen.wav"); if (ninteen == NULL){ return error("Error loading WAV file."); }
	twenty = Mix_LoadWAV("data/audio/twenty.wav"); if (twenty == NULL){ return error("Error loading WAV file."); }
	highSC = Mix_LoadWAV("data/audio/highsc.wav"); if (highSC == NULL){ return error("Error loading WAV file."); }

	//Note Loadings
	noteA = Mix_LoadWAV("data/audio/StringNoteA.wav"); if (noteA == NULL){ return error("Error loading WAV file. [note_A]"); }
	noteB = Mix_LoadWAV("data/audio/StringNoteB.wav"); if (noteB == NULL){ return error("Error loading WAV file. [note_B]"); }
	noteC = Mix_LoadWAV("data/audio/StringNoteC.wav"); if (noteC == NULL){ return error("Error loading WAV file. [note_C]"); }
	noteD = Mix_LoadWAV("data/audio/StringNoteD.wav"); if (noteD == NULL){ return error("Error loading WAV file. [note_D]"); }
	noteE = Mix_LoadWAV("data/audio/StringNoteE.wav"); if (noteE == NULL){ return error("Error loading WAV file. [note_E]"); }
	noteF = Mix_LoadWAV("data/audio/StringNoteF.wav"); if (noteF == NULL){ return error("Error loading WAV file. [note_F]"); }
	noteG = Mix_LoadWAV("data/audio/StringNoteG.wav"); if (noteG == NULL){ return error("Error loading WAV file. [note_G]"); }
	
	wall1 = Mix_LoadWAV("data/audio/WallBipE.wav"); if (wall1 == NULL){ return error("Error loading WAV file. [wall_1]"); }
	wall2 = Mix_LoadWAV("data/audio/WallBipFL.wav"); if (wall2 == NULL){ return error("Error loading WAV file. [wall_2]"); }
	wall3 = Mix_LoadWAV("data/audio/WallBipFR.wav"); if (wall3 == NULL){ return error("Error loading WAV file. [wall_3]"); }
	wall4 = Mix_LoadWAV("data/audio/WallBipCL.wav"); if (wall4 == NULL){ return error("Error loading WAV file. [wall_4]"); }
	wall5 = Mix_LoadWAV("data/audio/WallBipCR.wav"); if (wall5 == NULL){ return error("Error loading WAV file. [wall_5]"); }

	blockKick = Mix_LoadWAV("data/audio/BlockKick.wav"); if (blockKick == NULL){ return error("Error loading WAV file. [block_Kick]"); }

	vBlock1 = Mix_LoadWAV("data/audio/VirtuoBang1.wav"); if (vBlock1 == NULL){ return error("Error loading WAV file. [vBlock_1]"); }
	vBlock2 = Mix_LoadWAV("data/audio/VirtuoBang2.wav"); if (vBlock2 == NULL){ return error("Error loading WAV file. [vBlock_2]"); }

	dockL = Mix_LoadWAV("data/audio/LDock.wav"); if (dockL == NULL){ return error("Error loading WAV file. [dock_L]"); }
	dockR = Mix_LoadWAV("data/audio/RDock.wav"); if (dockR == NULL){ return error("Error loading WAV file. [dock_R]"); }
	
	paddleBounce = Mix_LoadWAV("data/audio/Paddle_Bounce.wav"); if (paddleBounce == NULL){ return error("Error loading WAV file. [Paddle_Bounce]"); }

	paddleLockA = Mix_LoadWAV("data/audio/PaddleA.wav"); if (paddleLockA == NULL){ return error("Error loading WAV file. [paddleA]"); }
	paddleLockB = Mix_LoadWAV("data/audio/PaddleB.wav"); if (paddleLockB == NULL){ return error("Error loading WAV file. [paddleB]"); }
	paddleLockC = Mix_LoadWAV("data/audio/PaddleC.wav"); if (paddleLockC == NULL){ return error("Error loading WAV file. [paddleC]"); }
	paddleLockD = Mix_LoadWAV("data/audio/PaddleD.wav"); if (paddleLockD == NULL){ return error("Error loading WAV file. [paddleD]"); }
	paddleLockE = Mix_LoadWAV("data/audio/PaddleE.wav"); if (paddleLockE == NULL){ return error("Error loading WAV file. [paddleE]"); }
	paddleLockF = Mix_LoadWAV("data/audio/PaddleF.wav"); if (paddleLockF == NULL){ return error("Error loading WAV file. [paddleF]"); }
	paddleLockG = Mix_LoadWAV("data/audio/PaddleG.wav"); if (paddleLockG == NULL){ return error("Error loading WAV file. [paddleG]"); }

	noteBlockA = Mix_LoadWAV("data/audio/NoteblockA.wav"); if (noteBlockA == NULL){ return error("Error loading WAV file. [noteBlock_A]"); }
	noteBlockB = Mix_LoadWAV("data/audio/NoteblockB.wav"); if (noteBlockB == NULL){ return error("Error loading WAV file. [noteBlock_B]"); }
	noteBlockC = Mix_LoadWAV("data/audio/NoteblockC.wav"); if (noteBlockC == NULL){ return error("Error loading WAV file. [noteBlock_C]"); }
	noteBlockD = Mix_LoadWAV("data/audio/NoteblockD.wav"); if (noteBlockD == NULL){ return error("Error loading WAV file. [noteBlock_D]"); }
	noteBlockE = Mix_LoadWAV("data/audio/NoteblockE.wav"); if (noteBlockE == NULL){ return error("Error loading WAV file. [noteBlock_E]"); }
	noteBlockF = Mix_LoadWAV("data/audio/NoteblockF.wav"); if (noteBlockF == NULL){ return error("Error loading WAV file. [noteBlock_F]"); }
	noteBlockG = Mix_LoadWAV("data/audio/NoteblockG.wav"); if (noteBlockG == NULL){ return error("Error loading WAV file. [noteBlock_G]"); }

	menu mainMenu;
	game thisGame(bestScore);
	level_select seLev;
	options optionMenu;
	
	while (!quit)
	{
		time = SDL_GetTicks();
		SDL_ShowCursor(SDL_DISABLE);

		if (gameState == 0)//Menu
		{
			gameState = mainMenu.show(gameType, storymode);

			if (gameType == 1)
			{
				score = 10;
			}
			else
			{
				score = 0;
			}
		}

		else if (gameState == 1)//Play
		{	
			gameState = thisGame.gameLoop(begin_lvl, storymode, paddleSpeed, ballSpeed, gameType, bestScore, medalHS, medal3L, medal20, levelAssign);
		}

		else if (gameState == 2)//Level Select Menu
		{
			gameState = seLev.show(begin_lvl, storymode, bestScore);
			
			if (gameType == 1)
			{
				score = 10;
			}
			else
			{
				score = 0;
			}
		}

		else if (gameState == 3)//Options Menu
		{
			gameState = optionMenu.show(paddleSpeed, ballSpeed, gameType, bestScore);
		}
		
		else if (gameState == 4)//Instructions
		{
			gameState = 0;
		}

		else if (gameState == 5)//Credits
		{
			gameState = 0;
		}

		else if (gameState == 6)//Quit
		{
			quit = true;
		}
		
		
		if ((SDL_GetTicks() - time) < 1000 / 60)
		{
			SDL_Delay((1000 / 60) - (SDL_GetTicks() - time));
		}
	}

	close();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}