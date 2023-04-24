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

    Fox();

    void SetPosition(int x, int y);

    bool LoadCharacter();

    void HandleEvent(SDL_Event &event);

    void Move(Tile* tiles[]);

    void SetCamera(SDL_Rect& camera);

    void FoxRender(SDL_Rect& camera);

    bool IsFallingOff();

    void Respawn();

    void ShootFireBall();

    bool HealthCheck();

    int GetDeathCount();

    void ResetDeathCount();

    void ResetSpeed();

    void NewLeverSpawn();

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
    bool IDLE, RUN, HURT;
    bool is_jumping;

    // Fox MoveType Clips
    SDL_Rect fox_frame_run_clip[6];
    SDL_Rect fox_frame_idle_clip[4];
    SDL_Rect fox_frame_climb_clip[3];
    SDL_Rect fox_frame_hurt_clip[2];

    // Respawn Position
    int mInitialX;
    int mInitialY;

    // Death count
    int Death_count;

};
#endif // FOX_H_
