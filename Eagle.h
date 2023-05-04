#ifndef EAGLE_H_
#define EAGLE_H_
class Eagle : public BaseMonster
{
public:
    // Eagle dimensions and speed
    static const int EAGLE_WIDTH = 123;
    static const int EAGLE_HEIGHT = 128;
    static const int EAGLE_SPEED_Y = -5;

    // Initialize eagle
    Eagle();

    // Load eagle textures
    bool LoadMonster() override;

    // Set position
    void SetPosition(int x, int y);

    // Render eagle
    void RenderMonster(SDL_Rect& camera) override;

    // Eagle auto move
    void AutoMove();

    // Eagle move
    void MonsterMove(Tile* tiles[]) override;

    // Get box
    SDL_Rect GetMonsterBox() override;

    // Respawn
    void Respawn() override;

    // Die
    void Die() override;
private:
    // Eagle fly animation clip
    SDL_Rect Eagle_fly_clip[4];

    // Status handle
    bool Fly;
    int Fly_counter;
    int mStartY;
};
#endif // EAGLE_H_
