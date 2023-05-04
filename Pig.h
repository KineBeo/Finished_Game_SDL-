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

    // Initialize pig
    Pig();

    // Set position
    void SetPosition(int x, int y);

    // Load pig texture
    bool LoadMonster() override;

    // Pig move
    void MonsterMove(Tile* tiles[]) override;

    // Render pig
    void RenderMonster(SDL_Rect& camera) override;

    // Get pig box
    SDL_Rect GetMonsterBox() override;

    // Pig status
    void SimpleAI(Tile* tiles[], int PlayerPosX, int PlayerPosY);

    // Respawn
    void Respawn() override;

    // Pig falling check
    bool IsFallingOff() override;

    // Pig die
    void Die() override;

    // Die flag
    bool IsDie();
private:
    // Pig animation clip
    SDL_Rect Pig_run_clip[4];

    // status handle
    bool facing;
    bool RUN;
    int Run_counter;
    bool Is_Die;
};
#endif // PIG_H
