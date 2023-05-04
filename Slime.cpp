#include "Global.h"
#include "UTIL.h"
#include "Slime.h"
#include "Constants.h"
#include "LTexture.h"
Slime::Slime()
{
    mBox.w = SLIME_WIDTH - 10;
    mBox.h = SLIME_HEIGHT - 2;

    mVelX = mVelY = 0;
    facing = false;
    JUMP = true;
    IDLE = true;
    DIE  = false;
    Jump_counter = Idle_counter = 0;
}

void Slime::SetPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
    mInitalizeX = x;
    mInitalizeY = y;
}

bool Slime::LoadMonster()
{
    if (!LSlimeIdle.LoadImageFromFile("img/Character/SlimeIdle.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            Slime_idle_clip[i] = {i * SLIME_WIDTH, 0, SLIME_WIDTH, SLIME_HEIGHT};
        }
    }

    if (!LSlimeJump.LoadImageFromFile("img/Character/SlimeJump.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            Slime_jump_clip[i] = {i * SLIME_WIDTH, 0, SLIME_WIDTH, SLIME_HEIGHT};
        }
    }
    return true;
}

void Slime::SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY)
{
    // if player is right of slime (5 block)
    if (PlayerPosX - mBox.x > 0 && PlayerPosX - mBox.x <= TILE_WIDTH * 5)
    {
        mVelX = SLIME_SPEED;
        facing = true;
        JUMP = true;
        IDLE = false;
    }
    // if player is left of slime (5 block)
    else if (PlayerPosX - mBox.x < 0 && PlayerPosX - mBox.x >= -TILE_WIDTH * 5)
    {
        mVelX = -SLIME_SPEED;
        facing = false;
        JUMP = true;
        IDLE = false;
    }
    else
    {
        mVelX = 0;
        JUMP = false;
        IDLE = true;
    }
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + SLIME_WIDTH > LEVER_WIDTH) || TouchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
    }
}
void Slime::MonsterMove(Tile* tiles[])
{
    // AI Slime move
    SimpleAI(tiles, FoxPosX, FoxPosY);
    mBox.y += mVelY;
    if (mBox.y < 0 || mBox.y + SLIME_HEIGHT > LEVER_HEIGHT || TouchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
    }
    mVelY += GRAVITY;
    if (mVelY > MONSTER_MAX_VEL_FALL)
    {
        mVelY = MONSTER_MAX_VEL_FALL;
    }
}
void Slime::RenderMonster(SDL_Rect& camera)
{
    SDL_RendererFlip flip;
    if (facing)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }
    if (CheckCollision(camera, mBox))
    {
        if (IDLE)
        {
            SDL_Rect* current_clip = &Slime_idle_clip[Idle_counter / 9];
            LSlimeIdle.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
            Idle_counter++;
            if (Idle_counter / 9 >= 8)
            {
                Idle_counter = 0;
            }
        }
        if (JUMP)
        {
            SDL_Rect* current_clip = &Slime_jump_clip[Jump_counter / 8];
            LSlimeJump.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
            Jump_counter++;
            if (Jump_counter / 8 >= 7)
            {
                Jump_counter = 0;
            }
        }
    }
}

SDL_Rect Slime::GetMonsterBox()
{
    return mBox;
}

void Slime::Respawn()
{
    SetPosition(mInitalizeX, mInitalizeY);
}

void Slime::Die()
{
    SetPosition(-100, -100);
    DIE = true;
}

bool Slime::IsDie()
{
    return DIE;
}


