#ifndef SLIME_H_
#define SLIME_H_
#include "BaseMonster.h"
class Slime : public BaseMonster
{
public:
    // Slime dimensions and speed
    static const int SLIME_WIDTH = 82;
    static const int SLIME_HEIGHT = 76;
    static const int SLIME_SPEED = 3;

    // Initialize slime
    Slime();

    // Set position
    void SetPosition(int x, int y);

    // Load slime textures
    bool LoadMonster() override;

    // Slime moves
    void MonsterMove(Tile* tiles[]) override;

    // Render slime
    void RenderMonster(SDL_Rect& camera) override;

    // Get slime box
    SDL_Rect GetMonsterBox() override;

    // Slime status
    void SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY);

    // Respawn
    void Respawn() override;

    // Die
    void Die() override;

    // Die flag
    bool IsDie();

private:
    // Slime animation clip
    SDL_Rect Slime_jump_clip[7];
    SDL_Rect Slime_idle_clip[8];

    // Slime status handle
    bool facing;
    bool JUMP, IDLE, DIE;
    int Jump_counter, Idle_counter;

    // Slime animation texture
    LTexture LSlimeJump;
    LTexture LSlimeIdle;

};
#endif // SLIME_H_
