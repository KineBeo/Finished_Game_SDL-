#ifndef BASE_MONSTER_H
#define BASE_MONSTER_H
#include "LTexture.h"
#include "Constants.h"
#include "Global.h"
#include "Tile.h"
class BaseMonster : public LTexture
{
public:
    // Monster gravity and max fall velocity
    static const int GRAVITY = 1;
    static const int MONSTER_MAX_VEL_FALL = 7;
    BaseMonster();
    virtual ~BaseMonster();

    // Load, Handle Event, Move, Render
    virtual bool LoadMonster();

    virtual void HandleEvent(SDL_Event& event);

    virtual void MonsterMove(Tile* tiles[]);

    virtual void RenderMonster(SDL_Rect& camera);

    virtual void SetCamera(SDL_Rect& camera);

    virtual SDL_Rect GetMonsterBox();

    // Monster status
    virtual bool IsFallingOff();

    virtual void Respawn();

    virtual void Attack();

    virtual void Die();
public:
    // Collision box of monster
    SDL_Rect mBox;

    // Monster velocity
    int mVelX, mVelY;

    // Move status
    int mMoveStatus;
    int mFrameMove;
    int mFrameIdle;
    int mWidthFrame, mHeightFrame;

    bool IsJumping;
    int mInitalizeX, mInitalizeY;
};
#endif // BASE_MONSTER_H
