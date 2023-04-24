#include "Global.h"

SDL_Window* g_window = NULL;

SDL_Renderer* g_screen = NULL;

TTF_Font* gFont = NULL;

LTexture g_Death_count;

LTexture PlayAgain;

LTexture gHighScoreText;

LTexture gTutorialText;

LTexture gTutorialText2;

LTexture gTutorialText3;

LTexture gObjectiveText;

LTexture PressEnter;

LTexture g_background;

LTexture g_middle_background;

LTexture g_tutorial;

LTexture g_TileTexure;

SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

Fox fox;

LTexture g_FoxRunTexture;

LTexture g_FoxIdleTexture;

LTexture g_FoxHurtTexture;

LTexture g_FoxJumpTexture;

FireBall fireball;

Pig Lever1_mPigs[LEVER1_TOTAL_PIG];

Eagle Lever1_mEagles[LEVER1_TOTAL_EAGLE];

Eagle Lever2_mEagles[LEVER2_TOTAL_EAGLE];

int current_level;

int game_status;

int Highscore;

int FireballEnergy = 0;

int NumFireBalls = 0;

bool quit = false;

LTexture game_over;

Button gStartButton;

Button gExitButton;

Button gYesButton;

Button gNoButton;

bool playagain = false;

int FoxPosX, FoxPosY;

int Health;

LTexture StateBar;

LTexture Heart;

LTexture NumFireballInStateBar;

Mix_Chunk *gButtonClick = NULL;

Mix_Music *gSoundTrack = NULL;

Mix_Chunk *gFootStepOnGrass = NULL;

Mix_Chunk *gFireBallWhoosh = NULL;

Mix_Chunk *gExplosion = NULL;

Mix_Chunk *gCoin = NULL;




