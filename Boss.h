#ifndef BOSS_H_
#define BOSS_H_
#include <vector>
#include "LTexture.h"
#include "Constants.h"
#include "BaseMonster.h"
#include "Tile.h"
#include "Global.h"
#include "FireBall.h"
class Boss : public BaseMonster
{
public:
    // Boss dimensions and speed
    const int BOSS_WIDTH = 99;
    const int BOSS_HEIGHT = 96;
    const int BOSS_SPEED = 4;

    // Initialize boss
    Boss();

    // Set position
    void SetPosition(int x, int y);

    // Load boss textures
    bool LoadMonster() override;

    // Render boss
    void RenderMonster(SDL_Rect& camera);

    // Simple AI of boss
    void SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY);

    // Boss move
    void MonsterMove(Tile* tiles[], SDL_Rect& camera);

    // Boss respawn
    void Respawn() override;

    // Shoot the fireball
    void ShootFireBall();

    // Boss take damage from fox
    void TakeDamage();

    // Boss die
    void BossDie();

    // Die flag
    bool IsDie();

    // Spawn pig
    void SpawnPigOfBoss();

    // Spawn slime
    void SpawnSlimeOfBoss();

    // Spawn dog
    void SpawnDogOfBoss();

    // Get boss box
    SDL_Rect GetBox();

private:
    // Fireball of boss vector
    std::vector <FireBall*> BossFireBalls;

    // Boss animation clip
    SDL_Rect Boss_idle_clip[6];
    SDL_Rect Boss_run_clip[12];
    SDL_Rect Boss_attack_clip[15];

    // Boss move animation texture
    LTexture LBossIdle;
    LTexture LBossRun;
    LTexture LBossAttack;

    // Boss status handle
    bool facing;
    bool IDLE, RUN, ATTACK, JUMP, DIE;
    int Idle_counter, Run_counter, Attack_counter;

};
#endif // BOSS_H_
