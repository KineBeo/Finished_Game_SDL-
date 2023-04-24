#include "Global.h"
#include "UTIL.h"
#include "FireBall.h"
#include "Constants.h"
#include "LTexture.h"

FireBall::FireBall()
{
    // Initialize variables
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = FIRE_WIDTH;
    mBox.h = FIRE_HEIGHT;
    mVelX = 0;
    mActive = false;
    Fireball_frame = 0;
}
bool FireBall::LoadFireBall()
{
    // Load fireball texture
    bool success = LTexture::LoadImageFromFile("img/fire-ball.png");
    if ( !success )
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            Fireball_clip[i] = {i * 76, 0, 76, 64};
        }
    }
    mBox.w = FIRE_WIDTH;
    mBox.h = FIRE_HEIGHT;
    mActive = true;
    return true;
}
void FireBall::SetPosition(int x, int y)
{
    // Set position
    mBox.x = x;
    mBox.y = y;
    mStartX = x;
    mStartY = y;
}
void FireBall::SetVelocity(int velX, int velY)
{
    // Set speed for fireball
    mVelX = velX;
    mVelY = velY;
}
void FireBall::SetActive(bool active)
{
    // Set fireball active
    mActive = active;
}
bool FireBall::IsActive()
{
    // Get fireball status
    return mActive;
}
void FireBall::Disable()
{
    // Set disable status
    mActive = false;
}
void FireBall::RenderFireball(SDL_Rect& camera, SDL_RendererFlip flip)
{
    // Render fireball animation
    if (mActive)
    {
        SDL_Rect* current_clip = &Fireball_clip[Fireball_frame / 4];
        Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
    }
    Fireball_frame++;
    if (Fireball_frame / 4 >= 3)
    {
        Fireball_frame = 0;
    }
}
void FireBall::Move(Tile* tiles[])
{
    // Move the fireballs
    mBox.x += mVelX;
    mBox.y += mVelY;

    // Max distance of fireballs movement
    int MAX_MOVEMENT = TILE_WIDTH * 6;
    // If fireball went to far of screen
    if ( mBox.x < 0 || mBox.x > LEVER_WIDTH || mBox.y < 0 || mBox.y > LEVER_HEIGHT ||
            abs(mBox.x - mStartX) > MAX_MOVEMENT || abs(mBox.y - mStartY) > MAX_MOVEMENT )
    {
        mActive = false;
    }

    // If fireball hits the enemy, kill enemy and clear fireball
    for (int i = 0; i < 6; i++)
    {
        if (CheckCollision(mBox, Lever1_mPigs[i].GetMonsterBox()))
        {
            Mix_PlayChannel(-1, gExplosion, 0);
            Lever1_mPigs[i].Die();
            Highscore += 200;
            mActive = false;
        }
        if (CheckCollision(mBox, Lever1_mEagles[i].GetMonsterBox()))
        {
            Mix_PlayChannel(-1, gExplosion, 0);
            Lever1_mEagles[i].Die();
            Highscore += 200;
            mActive = false;
        }
    }
    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
    {
        if (CheckCollision(mBox, Lever2_mEagles[i].GetMonsterBox()))
        {
            Mix_PlayChannel(-1, gExplosion, 0);
            Lever2_mEagles[i].Die();
            Highscore += 200;
            mActive = false;
        }
    }
}
SDL_Rect FireBall::GetBoxFireball()
{
    // Get fireball collision box
    return mBox;
}
