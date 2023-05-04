#include "Global.h"
#include "UTIL.h"
#include "LTexture.h"
#include "Constants.h"
#include "Boss.h"
#include "Pig.h"
Boss::Boss()
{
    // Set boss box
    mBox.w = BOSS_WIDTH - 30;
    mBox.h = BOSS_HEIGHT - 31;

    // Initialize velocity, health, status
    mVelX = mVelY = 0;
    BossHealth = 386;
    Idle_counter = Run_counter = 0;
    facing = RUN = DIE = false;
    IDLE = true;

}

void Boss::SetPosition(int x, int y)
{
    // Set boss first position and respawn position
    mBox.x = x;
    mBox.y = y;
    mInitalizeX = x;
    mInitalizeY = y;
}

bool Boss::LoadMonster()
{
    // Load boss animation texture
    if (!LBossIdle.LoadImageFromFile("Img/Character/FoxBossIdle.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Boss_idle_clip[i] = {i * BOSS_WIDTH, 0, BOSS_WIDTH, BOSS_HEIGHT};
        }
    }
    if (!LBossRun.LoadImageFromFile("Img/Character/FoxBossRun.png"))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            Boss_run_clip[i] = {i * BOSS_WIDTH, 0, BOSS_WIDTH, BOSS_HEIGHT};
        }
    }
    return true;
}
void Boss::SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY)
{
    // Simple auto move
    if (PlayerPosX - mBox.x > 0 && PlayerPosX - mBox.x < TILE_WIDTH * 7)
    {
        mVelX = BOSS_SPEED;
        facing = false;
        RUN = true;
        IDLE = false;
    }
    else if (PlayerPosX - mBox.x < 0 && PlayerPosX - mBox.x > -TILE_WIDTH * 7)
    {
        mVelX = -BOSS_SPEED;
        facing = true;
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
    if (mBox.x < 0 || mBox.x + BOSS_WIDTH > LEVER_WIDTH || TouchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
        mVelX = -mVelX;
    }
}
void Boss::MonsterMove(Tile* tiles[], SDL_Rect& camera)
{
    // Boss move
    SimpleAI(tiles, FoxPosX, FoxPosY);
    mBox.y += mVelY;
    if (mBox.y < 0 || mBox.y + BOSS_HEIGHT > LEVER_HEIGHT || TouchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
    }
    mVelY += GRAVITY;
    if (mVelY > MONSTER_MAX_VEL_FALL)
    {
        mVelY = MONSTER_MAX_VEL_FALL;
    }
    // Multiple Phases
    // Phase 1
    if (BossHealth <= 386 && BossHealth >= 300)
    {
        SpawnTimer++;
        if (SpawnTimer >= 70)
        {
            ShootFireBall();
            SpawnTimer = 0;
        }
    }
    // Phase 2
    if (BossHealth <= 290 && BossHealth >= 200)
    {
        SpawnSlimeOfBoss();
    }
    // Teleport to the end of map
    if (BossHealth == 186)
    {
        mBox.x = 375 * 64;
        mBox.y = 24 * 64;
        BossHealth -= 1;
    }
    if (BossHealth == 185)
    {
        stringstream BossPhase3_string;
        SDL_Color Bossphase3Color = {255, 255, 255, 255};
        BossPhase3_string.str("");
        BossPhase3_string << "Boss has teleported to the end of the map, go there to kill him";
        BossPhase3Text.LoadFromRenderedText(BossPhase3_string.str().c_str(), Bossphase3Color);
        BossPhase3Text.Render((SCREEN_WIDTH - BossPhase3Text.GetWidth()) / 2, 110, NULL);
    }
    // Phase 3
    if (BossHealth <= 185 && BossHealth >= 100)
    {
        FireBallPhase3SpawnTime++;
        if (FireBallPhase3SpawnTime >= 100)
        {
            ShootFireBall();
            FireBallPhase3SpawnTime = 0;
        }
    }
    // Phase 4
    if (BossHealth <= 90 && BossHealth >= 10)
    {
        SpawnDogOfBoss();
        SpawnPigOfBoss();
    }
    // Die
    else if (BossHealth <= 0)
    {
        BossDie();
        BossHealth = 0;
    }
    // Pig of Boss move
    for (auto& pig : mPigsOfBoss)
    {
        pig->MonsterMove(tiles);
    }
    // Slime of Boss move
    for (auto& slime : mSlimesOfBoss)
    {
        slime->MonsterMove(tiles);
    }
    for (auto& dog : mDogOfBoss)
    {
        dog->MonsterMove(tiles);
    }
    // Fireballs of boss move
    for (auto& fireball : BossFireBalls)
    {
        if (fireball->IsActive())
        {
            fireball->Move(tiles);
        }
    }
    // Checkcollision fireball of boss with fox
    for (auto& fireball : BossFireBalls)
    {
        if (CheckCollision(fireball->GetBoxFireball(), fox.GetBox()))
        {
            Mix_PlayChannel(-1, gExplosion, 0);
            FoxHealth -= 20;
            fireball->Disable();
        }
    }
}

void Boss::RenderMonster(SDL_Rect& camera)
{
    // Render boss
    SDL_RendererFlip flip;
    if (facing)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (!facing)
    {
        flip = SDL_FLIP_NONE;
    }
    if (IDLE)
    {
        SDL_Rect* current_clip = &Boss_idle_clip[Idle_counter / 7];
        LBossIdle.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
        Idle_counter++;
        if (Idle_counter / 6 >= 4)
        {
            Idle_counter = 0;
        }
    }
    if (RUN)
    {
        SDL_Rect *current_clip = &Boss_run_clip[Run_counter / 6];
        LBossRun.Render(mBox.x - camera.x, mBox.y - camera.y, current_clip, 0.0, NULL, flip);
        Run_counter++;
        if (Run_counter / 6 >=  6)
        {
            Run_counter = 0;
        }
    }
    // Render pig of boss
    for (int i = 0; i < mPigsOfBoss.size(); i++)
    {
        mPigsOfBoss[i]->RenderMonster(camera);
        if (mPigsOfBoss[i]->IsDie())
        {
            delete mPigsOfBoss[i];
            mPigsOfBoss.erase(mPigsOfBoss.begin() + i);
            i--;
        }
    }

    // Render slime of boss
    for (int i = 0; i < mSlimesOfBoss.size(); i++)
    {
        mSlimesOfBoss[i]->RenderMonster(camera);
        if (mSlimesOfBoss[i]->IsDie())
        {
            delete mSlimesOfBoss[i];
            mSlimesOfBoss.erase(mSlimesOfBoss.begin() + i);
            i--;
        }
    }

    // Render dog of boss
    for (int i = 0; i < mDogOfBoss.size(); i++)
    {
        mDogOfBoss[i]->RenderMonster(camera);
        if (mDogOfBoss[i]->IsDie())
        {
            delete mDogOfBoss[i];
            mDogOfBoss.erase(mDogOfBoss.begin() + i);
            i--;
        }
    }
    // Render fireball of boss
    for (int i = 0; i < BossFireBalls.size(); i++)
    {
        if (BossFireBalls[i]->IsActive() == true)
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
            BossFireBalls[i]->RenderFireball(camera, flip);
        }
        else
        {
            delete BossFireBalls[i];
            BossFireBalls.erase(BossFireBalls.begin() + i);
            i--;
        }
    }
}

void Boss::Respawn()
{
    // Respawn
    mBox.x = mInitalizeX;
    mBox.y = mInitalizeY;
}

void Boss::TakeDamage()
{
    // Boss take damage from fox
    BossHealth -= 20;
}

void Boss::ShootFireBall()
{
    // Shoot fireball
    FireBall* fireball = new FireBall();
    fireball->LoadFireBall();

    int FireballX = mBox.x + mBox.w / 2 - 16;
    int FireballY = mBox.y + mBox.h / 2 - 16;
    fireball->SetPosition(FireballX, FireballY);
    if (facing)
    {
        fireball->SetVelocity((FireBall::FIRE_SPEED) * -1, 0);
    }
    else
    {
        fireball->SetVelocity((FireBall::FIRE_SPEED), 0);
    }
    BossFireBalls.push_back(fireball);
}

void Boss::BossDie()
{
    // Die
    mBox.x = mBox.y = -100;
    DIE = true;
}

bool Boss::IsDie()
{
    // Die flag
    return DIE;
}
void Boss::SpawnPigOfBoss()
{
    // Spawn pig
    PigSpawnTimer++;
    if (PigSpawnTimer >= 600)
    {
        Pig* pig = new Pig();
        pig->LoadMonster();
        int PigX = mBox.x + (rand() % BOSS_WIDTH) * 7 - Pig::PIG_WIDTH;
        int PigY = mBox.y - BOSS_HEIGHT;
        pig->SetPosition(PigX, PigY);
        mPigsOfBoss.push_back(pig);
        PigSpawnTimer = 0;
    }
}

void Boss::SpawnSlimeOfBoss()
{
    // Spawn slime
    SlimeSpawnTimer++;
    if (SlimeSpawnTimer >= 400)
    {
        Slime* slime = new Slime();
        slime->LoadMonster();
        int SlimeX = fox.GetBox().x - TILE_WIDTH * 2 + (rand() % BOSS_WIDTH) * 6 - Slime::SLIME_WIDTH;
        int SlimeY = fox.GetBox().y - Slime::SLIME_HEIGHT;
        slime->SetPosition(SlimeX, SlimeY);
        mSlimesOfBoss.push_back(slime);
        SlimeSpawnTimer = 0;
    }
}

void Boss::SpawnDogOfBoss()
{
    // Spawn dog
    DogSpawnTimer++;
    if (DogSpawnTimer >= 500)
    {
        CreepyDog* dog = new CreepyDog();
        dog->LoadMonster();
        int DogX = fox.GetBox().x - TILE_WIDTH * 2 + (rand() % BOSS_WIDTH) * 4 - CreepyDog::CREEPY_DOG_WIDTH;
        int DogY = fox.GetBox().y - 30;
        dog->SetPosition(DogX, DogY);
        mDogOfBoss.push_back(dog);
        DogSpawnTimer = 0;
    }
}
SDL_Rect Boss::GetBox()
{
    // Get boss box
    return mBox;
}
