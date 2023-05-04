#include "Global.h"
#include "UTIL.h"
#include "CreepyDog.h"
#include "Constants.h"
#include "LTexture.h"
CreepyDog::CreepyDog()
{
    mBox.w = CREEPY_DOG_WIDTH - 10;
    mBox.h = CREEPY_DOG_HEIGHT - 5;

    mVelX = mVelY = 0;
    facing = false;
    RUN = true;
    IDLE = true;
    DIE  = false;
    Run_counter = Idle_counter = 0;
}
void CreepyDog::SetPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
    mInitalizeX = x;
    mInitalizeY = y;
}
bool CreepyDog::LoadMonster()
{
    if (!LCreepyDogRun.LoadImageFromFile("img/Character/DogRun.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            CreepyDog_run_clip[i] = {i * CREEPY_DOG_WIDTH, 0, CREEPY_DOG_WIDTH, CREEPY_DOG_HEIGHT};
        }
    }
    if (!LCreepyDogIdle.LoadImageFromFile("img/Character/DogIdle.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            CreepyDog_idle_clip[i] = {i * CREEPY_DOG_WIDTH, 0, CREEPY_DOG_WIDTH, CREEPY_DOG_HEIGHT};
        }
    }
    return true;
}
void CreepyDog::SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY)
{
    // if player is right of CreepyDog (5 block)
    if (PlayerPosX - mBox.x > 0 && PlayerPosX - mBox.x <= TILE_WIDTH * 7)
    {
        mVelX = CREEPY_DOG_SPEED;
        facing = true;
        RUN = true;
        IDLE = false;
    }
    // if player is left of CreepyDog (5 block)
    else if (PlayerPosX - mBox.x < 0 && PlayerPosX - mBox.x >= -TILE_WIDTH * 7)
    {
        mVelX = -CREEPY_DOG_SPEED;
        facing = false;
        RUN = true;
        IDLE = false;
    }
    else
    {
        mVelX = 0;
        RUN = false;
        IDLE = true;
    }
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + CREEPY_DOG_WIDTH > LEVER_WIDTH) || TouchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
    }
}
void CreepyDog::MonsterMove(Tile* tiles[])
{
    // AI CreepyDog move
    SimpleAI(tiles, FoxPosX, FoxPosY);
    mBox.y += mVelY;
    if (mBox.y < 0 || mBox.y + CREEPY_DOG_HEIGHT > LEVER_HEIGHT || TouchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
    }
    mVelY += GRAVITY;
    if (mVelY > MONSTER_MAX_VEL_FALL)
    {
        mVelY = MONSTER_MAX_VEL_FALL;
    }
}
void CreepyDog::RenderMonster(SDL_Rect& camera)
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
            SDL_Rect* current_clip = &CreepyDog_idle_clip[Idle_counter / 6];
            LCreepyDogIdle.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
            Idle_counter++;
            if (Idle_counter / 6 >= 6)
            {
                Idle_counter = 0;
            }
        }
        if (RUN)
        {
            SDL_Rect* current_clip = &CreepyDog_run_clip[Run_counter / 5];
            LCreepyDogRun.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
            Run_counter++;
            if (Run_counter / 5 >= 4)
            {
                Run_counter = 0;
            }
        }
    }
}

SDL_Rect CreepyDog::GetMonsterBox()
{
    return mBox;
}

void CreepyDog::Respawn()
{
    mBox.x = mInitalizeX;
    mBox.y = mInitalizeY;
}

void CreepyDog::Die()
{
    mBox.x = mBox.y = -100;
    DIE = true;
}

bool CreepyDog::IsDie()
{
    return DIE;
}



