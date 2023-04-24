#ifndef PIG_H
#define PIG_H
#include "BaseMonster.h"
class Pig : public BaseMonster
{
public:
    // Pig size and speed
    static const int PIG_WIDTH = 174;
    static const int PIG_HEIGHT = 96;
    static const int PIG_SPEED = 6;

    // Pig
    Pig();
    void SetPosition(int x, int y);
    bool LoadMonster() override;
    void MonsterMove(Tile* tiles[]) override;
    void RenderMonster(SDL_Rect& camera) override;
    SDL_Rect GetMonsterBox() override;
    // Pig status
    void SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY);
    void Respawn() override;
    bool IsFallingOff() override;
    void Attack() override;
    void Die() override;
private:
    SDL_Rect Pig_run_clip[4];
    bool facing;
    bool RUN;
    int Run_counter;
};
#endif // PIG_H
