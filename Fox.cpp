#include "Global.h"
#include "UTIL.h"
#include "Tile.h"
#include "Fox.h"
#include "Constants.h"
#include "LTexture.h"
#include "FireBall.h"
#include <vector>
Fox::Fox()
{
    // Fox box collision
    mBox.w = FOX_WIDTH - 30 ;
    mBox.h = FOX_HEIGHT - 31;

    // Initialize Fox Velocity
    mVelX = mVelY = 0;

    // Fox Status and frame
    facing = true;
    fireball_facing = true;
    IDLE = true;
    RUN = false;
    HURT = false;
    Idle_counter = Hurt_counter = Run_counter = 0;
    mInitialX = 0;
    mInitialY = 1000;
    Death_count = 0;
}
void Fox::SetPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
}
bool Fox::LoadCharacter()
{
    bool success = true;
    // Run
    if ( !g_FoxRunTexture.LoadImageFromFile("img/Character/fox_run.png"))
    {
        success = false;
    }
    else
    {
        for (int i = 0 ; i < 6 ; i++)
        {
            fox_frame_run_clip[i] = {i * 99, 0, 99, 96};
        }
    }
    // Idle
    if ( !g_FoxIdleTexture.LoadImageFromFile("img/Character/fox_idle.png") )
    {
        success = false;
    }
    else
    {
        for (int i = 0 ; i < 4 ; i++)
        {
            fox_frame_idle_clip[i] = {i * 99, 0, 99, 96};
        }
    }
    // Hurt
    if (!g_FoxHurtTexture.LoadImageFromFile("img/Character/fox_hurt.png"))
    {
        success = false;
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            fox_frame_hurt_clip[i] = {i * 99, 0, 99, 96};
        }
    }
    return success;
}
void Fox::HandleEvent(SDL_Event& event)
{
    // if a key was pressed
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        // adjust the speed
        switch (event.key.keysym.sym)
        {
        // Move up
        case SDLK_SPACE:
            if ( !is_jumping )
            {
                mVelY += FOX_JUMP_VEL;
                is_jumping = true;
            }
            break;
        // Move left
        case SDLK_a:
            facing = false;
            mVelX -= FOX_SPEED;
            break;
        // Move right
        case SDLK_d:
            facing = true;
            mVelX += FOX_SPEED;
            break;
        case SDLK_j:
            Mix_PlayChannel(-1, gFireBallWhoosh, 0);
            ShootFireBall();
            break;
        }
    }
    // if a key was release
    else if (event.type == SDL_KEYUP && event.key.repeat ==0)
    {
        // adjust the speed
        switch (event.key.keysym.sym)
        {
        // Move left
        case SDLK_a:
            mVelX += FOX_SPEED;
            break;
        // Move right
        case SDLK_d:
            mVelX -= FOX_SPEED;
            break;
        case SDLK_SPACE:
            break;

        }
    }
}
void Fox::Move(Tile* tiles[])
{
    // Fox move status
    if (mVelX == 0)
    {
        IDLE = true;
    }
    else
    {
        IDLE = false;
    }
    if (mVelX != 0)
    {
        RUN = true;
    }
    else
    {
        RUN = false;
    }

    // Fireball status
    if ((facing && IDLE) || (facing && RUN))
    {
        fireball_facing = true;
    }
    else if ((!facing && IDLE) || (!facing && RUN) )
    {
        fireball_facing = false;
    }
    // Check Collision of fox
    mBox.x += mVelX;
    if ((mBox.x < 0) || (TouchesWall(mBox, tiles)))
    {
        mBox.x -= mVelX;
    }
    mBox.y += mVelY;
    if ((mBox.y < 0) || (mBox.y + FOX_HEIGHT > LEVER_HEIGHT) || (TouchesWall(mBox, tiles)))
    {
        mBox.y -= mVelY;
        mVelY = 0;
        is_jumping = false;
    }
    // Apply gravity
    mVelY += GRAVITY;

    // Cap velocity
    if (mVelY > FOX_MAX_FALL_VEL)
    {
        mVelY = FOX_MAX_FALL_VEL;
    }
    // CheckCollision fox with monster at lever 1
    if (current_level == 1)
    {
        if (CheckCollision(mBox, Lever1_mPigs[0].GetMonsterBox()) || CheckCollision(mBox, Lever1_mPigs[1].GetMonsterBox()) || CheckCollision(mBox, Lever1_mPigs[2].GetMonsterBox()) ||
            CheckCollision(mBox, Lever1_mPigs[3].GetMonsterBox()) || CheckCollision(mBox, Lever1_mPigs[4].GetMonsterBox()) || CheckCollision(mBox, Lever1_mPigs[5].GetMonsterBox()) ||
            CheckCollision(mBox, Lever1_mEagles[0].GetMonsterBox()) || CheckCollision(mBox, Lever1_mEagles[1].GetMonsterBox()) || CheckCollision(mBox, Lever1_mEagles[2].GetMonsterBox()) ||
            CheckCollision(mBox, Lever1_mEagles[3].GetMonsterBox()) || CheckCollision(mBox, Lever1_mEagles[4].GetMonsterBox()) || CheckCollision(mBox, Lever1_mEagles[5].GetMonsterBox()))
        {
            HURT = true;
            RUN = IDLE = false;
            Health -= 1;
        }
        else
        {
            HURT = false;
        }
    }
    if (current_level == 2)
    {
        if (CheckCollision(mBox, Lever2_mEagles[0].GetMonsterBox()) || CheckCollision(mBox, Lever2_mEagles[1].GetMonsterBox())
            || CheckCollision(mBox, Lever2_mEagles[2].GetMonsterBox()) || CheckCollision(mBox, Lever2_mEagles[3].GetMonsterBox()))
        {
            HURT = true;
            RUN = IDLE = false;
            Health -= 1;
        }
        else
        {
            HURT = false;
        }
    }
    // Fox eat cherry handle
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        // Money and fireball bonus
        if (CheckCollision(mBox, tiles[i]->GetBox()))
        {
            if (tiles[i]->IsMoneyBlock(tiles[i]->GetTileType()))
            {
                Mix_PlayChannel(-1, gCoin, 0);
                Highscore += 100;
                tiles[i]->SetType(TILE_AIR_BLOCK); // fix lai
                if (Health <= FOX_MAX_HEALTH - 10)
                {
                    Health += 10;
                }
            }
            else if (tiles[i]->IsBlackMoneyBlock(tiles[i]->GetTileType()))
            {
                Mix_PlayChannel(-1, gCoin, 0);
                tiles[i]->SetType(TILE_BIG_LEFT_DIRT_2);
                Highscore += 100;
                if (Health <= FOX_MAX_HEALTH - 10)
                {
                    Health += 10;
                }
            }
            if (tiles[i]->GetTileType() == TILE_FIREBALL_BONUS)
            {
                Mix_PlayChannel(-1, gCoin, 0);
                FireballEnergy++;
                tiles[i]->SetType(TILE_AIR_BLOCK);
            }
        }
        // Spike
        if (CheckCollision(mBox, tiles[i]->GetBox()) && tiles[i]->IsSpikeBlock(tiles[i]->GetTileType()))
        {
            Mix_PlayChannel(-1, gFootStepOnGrass, 0);
            Respawn();
            break;
        }
    }
    // DEATH HANDLE
    // Respawn if fox is falling out of the lever
    if (IsFallingOff())
    {
        // Fox respawn
        Respawn();
    }

    // Check health
    if (HealthCheck())
    {
        Respawn();
    }

    // Fireball move
    for (auto& fireball : fireballs)
    {
        if (fireball->IsActive())
        {
            fireball->Move(tiles);
        }
    }
    // If player get 5 energy
    if (FireballEnergy >= 1)
    {
        NumFireBalls--;
        if (NumFireBalls <= 0)
        {
            NumFireBalls = 0;
        }
        FireballEnergy = 0;
    }
}
void Fox::SetCamera(SDL_Rect& camera)
{
    // center the camera over the dot
    camera.x = ( mBox.x + FOX_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + FOX_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    // Keep camera in bounds
    if ( camera.x < 0 )
    {
        camera.x = 0;
    }
    if ( camera.y < 0 )
    {
        camera.y = 0;
    }
    if ( camera.x > LEVER_WIDTH - camera.w )
    {
        camera.x = LEVER_WIDTH - camera.w;
    }
    if ( camera.y > LEVER_HEIGHT - camera.h)
    {
        camera.y = LEVER_HEIGHT - camera.h;
    }
}
void Fox::FoxRender(SDL_Rect& camera)
{
    // Fox movement render
    SDL_RendererFlip flip;
    if (facing)
    {
        flip = SDL_FLIP_NONE;
    }
    else
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    if (IDLE)
    {
        SDL_Rect* current_clip = &fox_frame_idle_clip[Idle_counter / 10];
        g_FoxIdleTexture.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
        Idle_counter++;
        if (Idle_counter / 6 >= 5)
        {
            Idle_counter = 0;
        }
    }
    if (RUN)
    {
        SDL_Rect* current_clip = &fox_frame_run_clip[Run_counter / 6];
        g_FoxRunTexture.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
        Run_counter++;
        if (Run_counter / 6 >= 6)
        {
            Run_counter = 0;
        }
    }
    if (HURT)
    {
        SDL_Rect* current_clip = &fox_frame_hurt_clip[Hurt_counter / 4];
        g_FoxHurtTexture.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip);
        Hurt_counter++;
        if (Hurt_counter / 4 >= 2)
        {
            Hurt_counter = 0;
        }
    }
    // Render fireball
    for (int i = 0; i < fireballs.size(); i++)
    {
        if (fireballs[i]->IsActive() == true)
        {
            if (fireball_facing)
            {
                fireballs[i]->RenderFireball(camera, SDL_FLIP_NONE);
            }
            if (!fireball_facing)
            {
                fireballs[i]->RenderFireball(camera, SDL_FLIP_HORIZONTAL);
            }
        }
        else
        {
            // Delete fireball if it' s disabled
            delete fireballs[i];
            fireballs.erase(fireballs.begin() + i);
            i--;
        }
    }
}
bool Fox::IsFallingOff()
{
    // Check if fox is below of screen
    if (mBox.y > LEVER_HEIGHT - 130)
    {
        return true;
    }
    return false;
}
void Fox::Respawn()
{
    // If fox is dead, Respawn it
    mBox.x = mInitialX;
    mBox.y = mInitialY;
    Death_count++;
}
void Fox::ShootFireBall()
{
    // static int NumFireBalls = 0;
    if (NumFireBalls < 5)
    {

        // Shoot the fireball
        FireBall* fireball = new FireBall();
        // Load fireballs texture
        fireball->LoadFireBall();

        int FireballX = mBox.x + ( mBox.w /2 ) - 16;
        int FireballY = mBox.y + ( mBox.h /2 ) - 16;
        fireball->SetPosition(FireballX, FireballY);

        if (!facing)
        {
            fireball->SetVelocity((FireBall::FIRE_SPEED) * -1, 0);
        }
        else
        {
            fireball->SetVelocity(FireBall::FIRE_SPEED, 0);
        }
        fireballs.push_back(fireball);
        NumFireBalls++;
    }
    // If player shoot more than the maximum number of fireballs, then stop firing
    if (NumFireBalls > MAXIMUM_NUMBER_OF_FIREBALL)
    {
        for (int i = 0; i < fireballs.size(); i++)
        {
            delete fireballs[i];
        }
        fireballs.clear();
    }
}

bool Fox::HealthCheck()
{
    // Check health is empty
    if (Health <= 0)
    {
        Health = 133;
        return true;
    }
    return false;
}
int Fox::GetDeathCount()
{
    // Get death count
    return Death_count;
}

void Fox::ResetDeathCount()
{
    // Reset death_count
    Death_count = 0;
}

void Fox::ResetSpeed()
{
    // Reset fox speed
    if (mVelX > 0 || mVelX < 0)
    {
        mVelX = 0;
    }
}

void Fox::NewLeverSpawn()
{
    // Set new lever spawn position
    mBox.x = mInitialX;
    mBox.y = mInitialY;
}
SDL_Rect Fox::GetBox()
{
    return mBox;
}


