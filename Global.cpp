#include "Global.h"

SDL_Window* g_window = NULL;

SDL_Renderer* g_screen = NULL;

TTF_Font* gFont = NULL;

LTexture g_Death_count;

LTexture PlayAgain;

LTexture gScoreText;

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

int Score;

int FireballEnergy = 0;

int NumFireBalls = 0;

bool quit = false;

LTexture game_over;

Button gStartButton;

Button gExitButton;

Button gYesButton;

Button gNoButton;

Button gResumeButton;

Button gPauseButton;

Button gHomeButton;

Button gRestartButton;

bool playagain = false;

int FoxPosX, FoxPosY;

int FoxHealth;

LTexture StateBar;

LTexture Heart;

LTexture NumFireballInStateBar;

Mix_Chunk *gButtonClick = NULL;

Mix_Music *gSoundTrack = NULL;

Mix_Chunk *gFootStepOnGrass = NULL;

Mix_Chunk *gFireBallWhoosh = NULL;

Mix_Chunk *gExplosion = NULL;

Mix_Chunk *gCoin = NULL;

Boss mBoss;

double scrollingOfSet = 0;

bool GamePause = false;

LTexture PauseBar;

std::vector <Pig*> mPigsOfBoss;

std::vector <Slime*> mSlimesOfBoss;

std::vector <CreepyDog*> mDogOfBoss;

int NumPigOfBossDie = 0;

int NumPigofBossSpawn = 0;

int SpawnTimer = 0;

int PigSpawnTimer = 0;

int SlimeSpawnTimer = 0;

int DogSpawnTimer = 0;


LTexture gBossFireball;

LTexture gBossHealthBar;

int BossHealth;

int FoxCurrentHeart;

int FireBallPhase3SpawnTime = 0;

int TeleportTimer = 0;

LTexture BossDieMessageToPlayer_Text;

LTexture VictoryMessage_Text;;

LTexture BossPhase3Text;

CreepyDog Lever2_mDog[LEVER2_TOTAL_EAGLE];
