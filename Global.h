#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "LTexture.h"
#include "Tile.h"
#include "Fox.h"
#include "FireBall.h"
#include "Pig.h"
#include "Eagle.h"
#include "Button.h"
#include "UTIL.h"
#include "Boss.h"
#include "Slime.h"
#include "CreepyDog.h"
// The window we'll rendering to
extern SDL_Window* g_window;

// The renderer
extern SDL_Renderer* g_screen;

// Global used font
extern TTF_Font* gFont;

// Death count
extern LTexture g_Death_count;

// PlayAgain Text
extern LTexture PlayAgain;

// Highscore Text
extern LTexture gScoreText;

// Tutorial Text
extern LTexture gTutorialText;

extern LTexture gTutorialText2;

extern LTexture gTutorialText3;

extern LTexture gObjectiveText;

// Press Enter Texture
extern LTexture PressEnter;

// The background texture
extern LTexture g_background;

// The middle background texture
extern LTexture g_middle_background;

// Tutorial background
extern LTexture g_tutorial;

// The TileSet texture
extern LTexture g_TileTexure;

// The tile clips
extern SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

// Fox Texture
extern Fox fox;
// Fox run texture

// Fox Run texture
extern LTexture g_FoxRunTexture ;

// Fox idle texture
extern LTexture g_FoxIdleTexture;

// Fox hurt texture
extern LTexture g_FoxHurtTexture;

// Fox jump texture
extern LTexture g_FoxJumpTexture;

// Fireball
extern FireBall fireball;

// Game monster
// Pig
extern Pig Lever1_mPigs[LEVER1_TOTAL_PIG];

// Eagle
extern Eagle Lever1_mEagles[LEVER1_TOTAL_EAGLE];

extern Eagle Lever2_mEagles[LEVER2_TOTAL_EAGLE];

extern CreepyDog Lever2_mDog[LEVER2_TOTAL_EAGLE];
// main loop flag
extern  bool quit;

// Game lever
extern int current_level;

// Game Status
extern int game_status;

// Score
extern int Score;

// Fireball bonus count
extern int FireballEnergy;

// Number of shooting fireball
extern int NumFireBalls ;

// GameOver Texture
extern LTexture game_over;

// Game button
extern Button gStartButton;

extern Button gExitButton;

extern Button gYesButton;

extern Button gNoButton;

extern Button gResumeButton;

extern Button gPauseButton;

extern Button gHomeButton;

extern Button gRestartButton;

extern bool playagain;

// Fox current position
extern int FoxPosX, FoxPosY;

// Fox state bar
extern int FoxHealth;

extern LTexture StateBar;

extern LTexture Heart;

extern LTexture NumFireballInStateBar;

// Game Sound
extern Mix_Chunk *gButtonClick;

extern Mix_Music *gSoundTrack;

extern Mix_Chunk *gFootStepOnGrass;

extern Mix_Chunk *gFireBallWhoosh;

extern Mix_Chunk *gExplosion;

extern Mix_Chunk *gCoin;

// Boss
extern Boss mBoss;

// The background scrolling of set ( Độ lệch của background )
extern double scrollingOfSet;

extern bool GamePause;

extern LTexture PauseBar;

// Monster of boss
extern std::vector <Pig*> mPigsOfBoss;

extern std::vector <Slime*> mSlimesOfBoss;

extern std::vector <CreepyDog*> mDogOfBoss;

extern int NumPigOfBossDie;

extern int NumPigofBossSpawn;

extern int SpawnTimer;

extern int PigSpawnTimer;

extern int SlimeSpawnTimer;

extern int DogSpawnTimer;

extern int TeleportTimer;

extern LTexture gBossFireball;

extern LTexture gBossHealthBar;

extern int BossHealth;

extern int FoxCurrentHeart;

extern int FireBallPhase3SpawnTime;

extern LTexture BossDieMessageToPlayer_Text;

extern LTexture VictoryMessage_Text;

extern LTexture BossPhase3Text;




#endif // GLOBAL_H_
