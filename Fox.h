#ifndef FOX_H_
#define FOX_H_
#include <vector>
#include "LTexture.h"
#include "Constants.h"
#include "Tile.h"
#include "Global.h"
#include "FireBall.h"
class Fox : public LTexture
{
public:
    // Fox size and speed
    static const int FOX_WIDTH = 99;
    static const int FOX_HEIGHT = 96;
    static const int FOX_SPEED = 10;

    // Fox gravity
    static const int GRAVITY = 1;

    // Fox jump velocity
    static const int FOX_JUMP_VEL = -21;

    // Fox max fall velocity
    static const int FOX_MAX_FALL_VEL  = 11;

    // Initialize fox
    Fox();

    // Set position
    void SetPosition(int x, int y);

    // Load fox textures
    bool LoadCharacter();

    // Handle event
    void HandleEvent(SDL_Event &event);

    // Fox move
    void Move(Tile* tiles[]);

    // Set game camera
    void SetCamera(SDL_Rect& camera);

    // Render fox
    void FoxRender(SDL_Rect& camera);

    // Fox falling check
    bool IsFallingOff();

    // Respawn
    void Respawn();

    // Shoot fireball
    void ShootFireBall();

    // Health check of fox
    bool HealthCheck();

    // Get deathcount
    int GetDeathCount();

    // Reset deathcount = 0
    void ResetDeathCount();

    // Reset speed of fox
    void ResetSpeed();

    // New lever spawn
    void NewLeverSpawn();

    // Get fox box
    SDL_Rect GetBox();

private:
    std :: vector <FireBall*> fireballs;
    // Collision box of fox
    SDL_Rect mBox;

    // fox velocity
    int mVelX, mVelY;

    // Run, idle, hurt, jump flag and counter
    bool facing;
    bool fireball_facing;
    int Idle_counter, Run_counter, Hurt_counter;
    bool IDLE, RUN, HURT, JUMP;

    // Fox MoveType Clips

    SDL_Rect fox_frame_run_clip[6];
    SDL_Rect fox_frame_idle_clip[4];
    SDL_Rect fox_frame_hurt_clip[2];

    // Respawn Position
    int mInitialX;
    int mInitialY;

    // Death count
    int Death_count;

};
#endif // FOX_H_
