#ifndef EAGLE_H_
#define EAGLE_H_
class Eagle : public BaseMonster
{
public:
    const int EAGLE_WIDTH = 123;
    const int EAGLE_HEIGHT = 128;
    const int EAGLE_SPEED_Y = -5;
    Eagle();

    bool LoadMonster() override;

    void SetPosition(int x, int y);

    void RenderMonster(SDL_Rect& camera) override;

    void AutoMove();

    void MonsterMove(Tile* tiles[]) override;

    SDL_Rect GetMonsterBox() override;

    void Respawn() override;
    void Die() override;
private:
    SDL_Rect Eagle_fly_clip[4];
    bool Fly;
    int Fly_counter;
    int mStartY;
};
#endif // EAGLE_H_
