#include "Global.h"
#include "UTIL.h"
#include "BaseMonster.h"
#include "Constants.h"
#include "LTexture.h"

BaseMonster::BaseMonster()
{
    // Initialize variables
    mVelX = mVelY = 0;
    mFrameIdle = 0;
    mFrameMove = 0;
    mWidthFrame = 0;
    mHeightFrame = 0;
    IsJumping = false;
    mInitalizeX = mInitalizeY = 0;
}

BaseMonster::~BaseMonster()
{

}
bool BaseMonster::LoadMonster()
{
    // override
}
void BaseMonster::HandleEvent(SDL_Event& event)
{
    // override
}
void BaseMonster::MonsterMove(Tile* tiles[])
{
    // override
}
void BaseMonster::RenderMonster(SDL_Rect& camera)
{
    // override
}
void BaseMonster::SetCamera(SDL_Rect& camera)
{
    // override
}
SDL_Rect BaseMonster::GetMonsterBox()
{
    // override
}
bool BaseMonster::IsFallingOff()
{
    // override
}
void BaseMonster::Respawn()
{
    // override
}
void BaseMonster::Attack()
{
    // override
}
void BaseMonster::Die()
{
    // override
}
