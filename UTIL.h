#ifndef UTIL_H_
#define UTIL_H_
#include "Tile.h"
#include "Button.h"
// Initialize SDL, image, mixer, ttf
bool Init();

// Load media
bool LoadBackGround();

// Load map
bool LoadMap(Tile* tiles[], int& current_lever);

// Load Font
bool LoadFont();

// Load Music
bool LoadMusic();

// Load Fox, enemy
void LoadAllCharacter();

void SetEnemyPosition();

void RenderEnemy(SDL_Rect& camera);

void CharacterMove(Tile* tileset[]);

// Close SDL, free image
void Close(Tile* tiles[]);

// Box collision detector
bool CheckCollision(SDL_Rect a, SDL_Rect b);

// Check collision of object with block
bool TouchesWall(SDL_Rect box, Tile* tiles[]);

// Set tile from tile map
bool SetTiles(Tile* tiles[], string path);

// Render Background for game
void RenderBackGround();

// Respawn pig object
void PigRespawn();

// Respawn Eagle object
void EagleRespawn();

// GameStart Background
void RenderGameStart();

// GameOver Background
void RenderGameOver();

// Reset Gameplay
void ResetGamePlay();

#endif // UTIL_H_
