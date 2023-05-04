#ifndef CREEPY_DOG_H_
#define CREEPY_DOG_H_
#include "BaseMonster.h"
class CreepyDog : public BaseMonster
{
public:
    // Dog dimensions and speed
    static const int CREEPY_DOG_WIDTH = 132;
    static const int CREEPY_DOG_HEIGHT = 104;
    static const int CREEPY_DOG_SPEED = 3;

    // Initialize dog
    CreepyDog();

    // Set position
    void SetPosition(int x, int y);

    // Load dog texture
    bool LoadMonster() override;

    // Dog Move
    void MonsterMove(Tile* tiles[]) override;

    // Render Dog
    void RenderMonster(SDL_Rect& camera) override;

    // Get dog box
    SDL_Rect GetMonsterBox() override;

    // Slime status
    void SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY);

    // Respawn
    void Respawn() override;

    // Dog die
    void Die() override;

    // Die flag
    bool IsDie();

private:
    // Dog animation clip
    SDL_Rect CreepyDog_run_clip[4];
    SDL_Rect CreepyDog_idle_clip[6];

    // Dog status handle
    bool facing;
    bool RUN, IDLE, DIE;
    int Run_counter, Idle_counter;

    // Dog animation texture
    LTexture LCreepyDogRun;
    LTexture LCreepyDogIdle;
};
#endif // CREEPY_DOG_H_
