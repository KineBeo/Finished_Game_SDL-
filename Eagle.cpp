#include "Global.h"
#include "Eagle.h"
#include "UTIL.h"
#include "Constants.h"
Eagle::Eagle()
{
    mBox.w = EAGLE_WIDTH;
    mBox.h = EAGLE_HEIGHT;
    mVelX = mVelY = 0;
    Fly = true;
    Fly_counter = 0;
}
void Eagle::SetPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
    mInitalizeX = x;
    mInitalizeY = y;
    mStartY = y;
}
bool Eagle::LoadMonster()
{
    if (!LTexture::LoadImageFromFile("img/Character/Eagle.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Eagle_fly_clip[i] = {i * EAGLE_WIDTH, 0, EAGLE_WIDTH, EAGLE_HEIGHT};
        }
    }
    return true;
}
void Eagle::AutoMove()
{
    srand(time(NULL));
    int action = rand() % 2;
    switch (action)
    {
    case 0:
        mVelY = EAGLE_SPEED_Y;
        break;
    case 1:
        mVelY = -EAGLE_SPEED_Y;
        break;
    }
}

void Eagle::MonsterMove(Tile* tiles[])
{
    AutoMove();
    mBox.y += mVelY;
    if (mBox.y < 0 || mStartY - mBox.y > TILE_WIDTH * 4 || TouchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
        mVelY = 0;
    }
}

void Eagle::RenderMonster(SDL_Rect& camera)
{
    SDL_Rect* current_clip = &Eagle_fly_clip[Fly_counter / 5];
    if (Fly)
    {
        Render(mBox.x - camera.x, mBox.y - camera.y, current_clip);
    }
    Fly_counter++;
    if (Fly_counter / 5 >= 4)
    {
        Fly_counter = 0;
    }
}
SDL_Rect Eagle::GetMonsterBox()
{
    return mBox;
}
void Eagle::Respawn()
{
    mBox.x = mInitalizeX;
    mBox.y = mInitalizeY;
}
void Eagle::Die()
{
    mBox.x = mBox.y = -100;
}
