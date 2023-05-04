#include "Global.h"
#include "UTIL.h"
#include "Pig.h"
#include "Constants.h"
#include "LTexture.h"
#include "cstdlib"
#include "ctime"
Pig::Pig()
{
    mBox.w = PIG_WIDTH - 15;
    mBox.h = PIG_HEIGHT - 2;

    mVelX = mVelY = 0;
    IsJumping = false;
    facing = false;
    RUN = true;
    Run_counter = 0;
    Is_Die = false;
}

void Pig::SetPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
    mInitalizeX = x;
    mInitalizeY = y;
}
bool Pig::LoadMonster()
{
    if ( !LTexture::LoadImageFromFile("img/Character/Pig.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Pig_run_clip[i] = {i * PIG_WIDTH, 0, PIG_WIDTH, PIG_HEIGHT};
        }
    }
    return true;
}
void Pig::SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY)
{
    // if player is right of pig (7 block)
    if (PlayerPosX - mBox.x > 0 && PlayerPosX - mBox.x <= TILE_WIDTH * 9)
    {
        mVelX = PIG_SPEED;
        facing = true;
    }
    // if player is left of pig (7 block)
    else if (PlayerPosX - mBox.x < 0 && PlayerPosX - mBox.x >= - TILE_WIDTH * 9)
    {
        mVelX = -PIG_SPEED;
        facing = false;
    }
    else
    {
        mVelX = 0;
    }
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + PIG_WIDTH > LEVER_WIDTH) || TouchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
        mVelX = -mVelX;
    }
}
void Pig::MonsterMove(Tile* tiles[])
{
    // AI pig move
    SimpleAI(tiles, FoxPosX, FoxPosY);
    if (mVelX != 0)
    {
        RUN = true;
    }
    mBox.y += mVelY;
    if ((mBox.y < 0) || (mBox.y + PIG_HEIGHT > LEVER_HEIGHT) || TouchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
        mVelY = 0;
        IsJumping = false;
    }
    mVelY += GRAVITY;
    if (mVelY > MONSTER_MAX_VEL_FALL)
    {
        mVelY = MONSTER_MAX_VEL_FALL;
    }
    if (IsFallingOff())
    {
        Respawn();
    }
}

void Pig::RenderMonster(SDL_Rect& camera)
{
    if (CheckCollision(camera, mBox))
    {
        SDL_Rect* current_clip = &Pig_run_clip[Run_counter / 7];
        if (facing && RUN)
        {
            Render(mBox.x - camera.x, mBox.y - camera.y, current_clip);
        }
        else if (!facing && RUN)
        {
            Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        Run_counter++;
        if (Run_counter / 5 >= 4)
        {
            Run_counter = 0;
        }
    }
}

SDL_Rect Pig::GetMonsterBox()
{
    return mBox;
}
bool Pig::IsFallingOff()
{
    if (mBox.y > LEVER_HEIGHT - 150)
    {
        return true;
    }
    else if (mBox.x < -PIG_WIDTH)
    {
        return true;
    }
    else if (mBox.x > LEVER_WIDTH)
    {
        return true;
    }
    return false;
}

void Pig::Respawn()
{
    mBox.x = mInitalizeX;
    mBox.y = mInitalizeY;
}

void Pig::Die()
{
    mBox.x = -100;
    mBox.y = -100;
    Is_Die = true;
}

bool Pig::IsDie()
{
    return Is_Die;
}
