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
extern LTexture gHighScoreText;

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

// Pig
extern Pig Lever1_mPigs[LEVER1_TOTAL_PIG];

// Eagle
extern Eagle Lever1_mEagles[LEVER1_TOTAL_EAGLE];

extern Eagle Lever2_mEagles[LEVER2_TOTAL_EAGLE];

// main loop flag
extern  bool quit;

// Game lever
extern int current_level;

// Game Status
extern int game_status;

// Score
extern int Highscore;

// Fireball bonus count
extern int FireballEnergy;

// Number of shooting fireball
extern int NumFireBalls ;

// GameOver Texture
extern LTexture game_over;

// Start button
extern Button gStartButton;

// Exit button
extern Button gExitButton;

// Yes and No button
extern Button gYesButton;

extern Button gNoButton;

extern bool playagain;

extern int FoxPosX, FoxPosY;

extern int Health;

extern LTexture StateBar;

extern LTexture Heart;

extern LTexture NumFireballInStateBar;

extern Mix_Chunk *gButtonClick;

extern Mix_Music *gSoundTrack;

extern Mix_Chunk *gFootStepOnGrass;

extern Mix_Chunk *gFireBallWhoosh;

extern Mix_Chunk *gExplosion;

extern Mix_Chunk *gCoin;


#endif // GLOBAL_H_
